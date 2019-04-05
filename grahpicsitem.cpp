#include "graphicsitem.h"
#include <QTimer>

grahpicsItem::grahpicsItem()
{
    setRect(50,50,50,10);

        // connect
        QTimer * timer = new QTimer();
        connect(timer,SIGNAL(timeout()),this,SLOT(move()));

        timer->start(50);
}

void grahpicsItem::move()
{
    setPos(x(),y()-10);
}
