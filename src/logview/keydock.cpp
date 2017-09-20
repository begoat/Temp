#include "keydock.h"

KeyDock::KeyDock(const QString &title): QDockWidget(title){
    qDebug() << "111111";
    LogView *m_log = new LogView(true);
    this->setObjectName("log");
    this->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    this->setFeatures(QDockWidget::AllDockWidgetFeatures);
    this->setWidget(m_log);
    event = new QKeyEvent(QEvent::KeyPress,Qt::Key_F3,Qt::NoModifier);
}

void KeyDock::keyPressEvent(QKeyEvent *event){
    if (event->type() == QEvent::KeyPress){
        QKeyEvent *kevent = (QKeyEvent *)event;
        if (kevent->key() == Qt::Key_F3){
            qDebug() << "!!!!!";
        }
    }
}
