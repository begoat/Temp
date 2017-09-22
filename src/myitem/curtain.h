#include <QtQuick/QQuickPaintedItem>
#include <QtCore>
#include <QtGui>
#include <QtQuick>
#include "../log/logger.h"

class Curtain : public QQuickPaintedItem{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)

public:
    Curtain(QQuickItem *parent = 0);

    QString name() const;
    void setName(const QString &name);
    QColor color() const;
    void setColor(const QColor &color);

    Q_INVOKABLE void clearlog();
    Q_INVOKABLE void hidelog();
    void paint(QPainter *painter);

public slots:
    void appendToLog(int type, const QString &msg, const QUrl &url = QUrl(), int line = -1, int column = -1);

signals:
    void logcleared();
    void loghidden();

private:
    QString text;
    QString my_name;
    QColor my_color;
    QMutex m_mutex;
    Logger* m_logger;
    QRect rectangle;
};
