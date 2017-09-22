#include <QtQuick>

class Curtain : public QQuickItem{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)

public:
    Curtain(QQuickItem *parent = 0);

    QString name() const;
    void setName(const QString &name);

private:
    QString my_name;
};
