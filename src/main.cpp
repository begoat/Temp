#include <QDebug>
#include <QFileSystemWatcher>
#include <QQmlApplicationEngine>
#include <QtWidgets>

#include "utils.h"

#ifdef DEVELOP_MODE
#include "watchreload/watchreload.h"
#include "logview/mainwidget.h"
#include "logview/logview.h"
#endif

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

#if defined(DEVELOP_MODE)
    qDebug() << "DEVELOP_MODE=ON";
    // monitor the resource dir and output the dirname
    QFileSystemWatcher filewatcher;
    QString watchPath = WATCH_DIR_PATH; // use Cmakelist.txt to pass a macro to this file
    if (!filewatcher.addPath(watchPath) ){
        qDebug() << "Target path not found";
    }
    else {
        QStringList dirList = filewatcher.directories();
        qDebug() << "Watching dir list: "<< dirList[0].toUtf8().constData();
    }
    // disable QML cache to prevent the associated bugs from manifesting
    qputenv("QML_DISABLE_DISK_CACHE", "1");

    QString confFilePath = WATCH_DIR_PATH;
    QString mainQmlPath = WATCH_DIR_PATH;
    confFilePath.append("/qtquickcontrols2.conf");
    mainQmlPath.append("/main.qml");
    qputenv("QT_QUICK_CONTROLS_CONF", (confFilePath).toUtf8());
    engine.load(QUrl(mainQmlPath));
    // a function as a slot to receive and react to the signal
    WatchReload reloader(&engine);
    QObject::connect(&filewatcher,&QFileSystemWatcher::directoryChanged,&reloader,&WatchReload::reload);

    // ================================

    // get pointer to ApplicationWindow
    QObject *rootObject = engine.rootObjects().first();
    rootObject->setProperty("visible",false); //only in this way can the window be shown correctly
    QWindow *qmlWindow = qobject_cast<QWindow*>(rootObject);

    /* not a good idea to affect the key events in qml application window
    QObject *testtest = rootObject->findChild<QObject*>("test");
    qDebug() << testtest;
    testtest->setProperty("onActivated",'');
    */

    // create window container
    QWidget *container = QWidget::createWindowContainer(qmlWindow);
    qDebug() << container;
    container->setMinimumSize(qmlWindow->size().width(), qmlWindow->size().height());

    // new mainwindow widget
    MainWidget *mainwidget = new MainWidget();

    // a DockWidget wrap a log widget got from qmllive-qt
    QDockWidget *console = new QDockWidget("Application Output");
    LogView *app_log = new LogView(true);
    console->setObjectName("log");
    console->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    console->setFeatures(QDockWidget::AllDockWidgetFeatures);
    console->setWidget(app_log);

    // create a layout
    QSplitter *splitter = new QSplitter;
    splitter->addWidget(container);
    splitter->addWidget(console);
    splitter->setOrientation(Qt::Vertical);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(splitter);
    mainwidget->setLayout(layout);
    mainwidget->show();

#else
    qDebug() << "DEVELOP_MODE=OFF";
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
#endif

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
