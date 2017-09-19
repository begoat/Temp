#include <QDebug>
#include <QFileSystemWatcher>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QtWidgets>

#include "utils.h"

#ifdef DEVELOP_MODE
#include "logview/logview.h"
#include "watchreload/watchreload.h"
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

    // get pointer to ApplicationWindow
    QWindow *qmlWindow = qobject_cast<QWindow*>(engine.rootObjects().first());

    // create window container
    QWidget *container = QWidget::createWindowContainer(qmlWindow);
    qDebug() << container;
    container->setMinimumSize(qmlWindow->size().width(), qmlWindow->size().height());

    QWidget *widget = new QWidget();
    // create a layout
    QGridLayout *grid = new QGridLayout(widget);
    grid->addWidget(container,0,0);

    QDockWidget *m_logDock = new QDockWidget("Log Output");
    m_logDock->setObjectName("log");
    m_logDock->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    m_logDock->setFeatures(QDockWidget::AllDockWidgetFeatures);
    LogView *m_log = new LogView(true); // This is embeded widget
    m_logDock->setWidget(m_log);
    grid->addWidget(m_logDock,1,0); // place the widget to the top of the widget
    widget->show();

#else
    qDebug() << "DEVELOP_MODE=OFF";
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
#endif

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
