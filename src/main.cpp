#include <QDebug>
#include <QFileSystemWatcher>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "utils.h"
#ifdef DEVELOP_MODE
#include "watchreload/watchreload.h"
#include "logconsole/logger.h"
#endif

class SingletonTypeExample : public QObject
{
    Q_OBJECT
    Q_PROPERTY (int someProperty READ someProperty WRITE setSomeProperty NOTIFY somePropertyChanged)

public:
    SingletonTypeExample(QObject* parent = 0)
        : QObject(parent), m_someProperty(0)
    {
    }

    ~SingletonTypeExample() {}

    Q_INVOKABLE int doSomething() { setSomeProperty(5);

                                    qDebug() << "Do SOMETHING";
                                    return m_someProperty; }

    int someProperty() const { return m_someProperty; }
    void setSomeProperty(int val) { m_someProperty = val; emit somePropertyChanged(val); }

signals:
    void somePropertyChanged(int newValue);

private:
    int m_someProperty;
};

static QObject *example_qobject_singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    qDebug() << "example called";
    SingletonTypeExample *example = new SingletonTypeExample();
    return example;
}

static QObject *singletonlog(QQmlEngine *engine, QJSEngine *scriptEngine){
    Q_UNUSED(engine)
    Q_UNUSED(scriptEngine)
    qDebug() << "instance called";
    return Logger::instance();
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
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

//    Logger *log;
//    log = log->instance();
    qmlRegisterSingletonType<Logger>("qmllive.logger", 1, 0, "Logger", singletonlog);
    qmlRegisterSingletonType<SingletonTypeExample>("Qt.example.qobjectSingleton", 1, 0, "MyApi", example_qobject_singletontype_provider);


    engine.load(QUrl(mainQmlPath));
    // a function as a slot to receive and react to the signal
    WatchReload reloader(&engine);
    QObject::connect(&filewatcher,&QFileSystemWatcher::directoryChanged,&reloader,&WatchReload::reload);
#else
    qDebug() << "DEVELOP_MODE=OFF";
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));
#endif

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

#include "main.moc"
