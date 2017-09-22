#include "curtain.h"
#include <qDebug>
#include <QPainter>

Curtain::Curtain(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    qDebug() << "Created now";
    text = "";
    m_logger = new Logger(this);
    connect(m_logger, SIGNAL(message(int,QString)), this, SLOT(appendToLog(int,QString)));
}

QString Curtain::name() const{
    return this->my_name;
}

void Curtain::setName(const QString &name){
    this->my_name = name;
}

QColor Curtain::color() const{
    return this->my_color;
}

void Curtain::setColor(const QColor &color){
    this->my_color = color;
}

void Curtain::paint(QPainter *painter){
    rectangle = QRect(0, 0, this->width(), this->height());
    QRect boundingRect;
    QPen pen(my_color,2);
    painter->setPen(pen);
    painter->drawText(rectangle, 0, text, &boundingRect);
}

void Curtain::appendToLog(int type, const QString &msg, const QUrl &url, int line, int column){
    QMutexLocker l(&m_mutex);
    this->text.append("\n").append(QString::fromLatin1("%1").arg(msg));
    Curtain::update();
}

void Curtain::clearlog(){
    QMutexLocker l(&m_mutex);
    text = "";
    Curtain::update();
    emit logcleared();
}

void Curtain::hidelog(){
    this->setVisible(!this->isVisible());
    emit loghidden();
}
