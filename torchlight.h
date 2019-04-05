#ifndef GRAPHICSITEM_H
#define GRAPHICSITEM_H

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <QList>

#include <graphicsplayer.h>

using namespace std;

class torchLight: public QObject,public QGraphicsPixmapItem {
    Q_OBJECT
public:
    torchLight(QGraphicsItem * parent=0);
    int hit = 0;
    int getHit() const;
    void setHit(int value);
public slots:
    void move();
};

class monsterHit: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    monsterHit(QGraphicsItem * parent=0);
public slots:
    void move();
};

#endif // GRAPHICSITEM_H
