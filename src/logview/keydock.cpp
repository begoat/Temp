#include "keydock.h"

KeyDock::KeyDock(const QString &title): QDockWidget(title){
    qDebug() << "111111";
    LogView *m_log = new LogView(true);
    this->setObjectName("log");
    this->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
    this->setFeatures(QDockWidget::AllDockWidgetFeatures);
    this->setWidget(m_log);
}

