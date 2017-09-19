#include <QQmlApplicationEngine>

class WatchReload : public QObject
{
    Q_OBJECT

public:
    WatchReload(QQmlApplicationEngine *engine);

public slots:
    void reload();

private:
    QQmlApplicationEngine *engine;
    QObject *headerObj;
    QObject *contentObj;
};
