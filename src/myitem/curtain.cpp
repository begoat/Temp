#include "curtain.h"
#include <qDebug>

Curtain::Curtain(QQuickItem *parent)
    : QQuickItem(parent){
    qDebug() << "Created now";
}

QString Curtain::name() const{
    return this->my_name;
}

void Curtain::setName(const QString &name){
    this->my_name = name;
}
