#include <QDockWidget>
#include "logview.h"

class KeyDock : public QDockWidget
{
    Q_OBJECT

public:
    KeyDock(const QString &title);
protected:
    virtual void keyPressEvent(QKeyEvent *event);
    QKeyEvent *event;
};
