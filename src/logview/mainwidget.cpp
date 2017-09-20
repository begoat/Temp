#include "mainwidget.h"
#include <QDebug>
#include <QKeyEvent>

void MainWidget::keyPressEvent(QKeyEvent *event){
    if (event->type() == QEvent::KeyPress){
        QKeyEvent *kevent = (QKeyEvent *)event;
        if (kevent->key() == Qt::Key_F3){
            qDebug() << "F3 pressed once";
            if (!dock){
                dock = this->findChild<QDockWidget *>("logoutput");
            }
            qDebug() << dock;
            dock->setVisible(dock->isHidden());
        }
    }
}
