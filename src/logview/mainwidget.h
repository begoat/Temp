#include <QWidget>
#include <QDockWidget>

class MainWidget: public QWidget{
    Q_OBJECT

protected:
    virtual void keyPressEvent(QKeyEvent *event);
    QDockWidget *dock;
};
