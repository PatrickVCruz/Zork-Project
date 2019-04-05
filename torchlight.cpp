
#include "torchlight.h"
#include "hauntedhouse.h"

extern hauntedHouse * w;

int torchLight::getHit() const
{
    return hit;
}

void torchLight::setHit(int value)
{
    hit = value;
}

torchLight::torchLight(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent) {
    setPixmap(QPixmap(":/imgs/resources/Items/6_number_one.png"));
    setTransformOriginPoint(27/2,70/2);
    setRotation(270);

    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(25);
    w->waitForAttack(0);
}

void torchLight::move() {
    setPos(x()+10,y());
    QList<QGraphicsItem *> hitMonsters = collidingItems();
    for(int i = 0, n = hitMonsters.size(); i < n;i++) {
        if (typeid(*hitMonsters[i]) == typeid(GraphicsEnemy)) {
            scene()->removeItem(this);
            setHit(1);
            if(w->room->getGEnemy()->getHealth() == 0) {
                w->enterText("You have defeated " + QString::fromStdString(w->room->getGEnemy()->getMonsterName()));
                w->scene->removeItem(w->room->getGEnemy());
                w->monsterInTheWay = 0;
                w->room->setMonsterInRoom(0);

            }
            else {
                w->room->getGEnemy()->loseHealth(w->player->getAttackPower());
                w->room->getGEnemy()->attackPlayer();
                w->tracker->setBatterLevel(w->player->getFlashlightLevel());
            }
        }
    }
}


monsterHit::monsterHit(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/imgs/resources/Items/114_moms_knife.png"));
    setRotation(270);
    QTimer * timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(25);
}

void monsterHit::move() {
    setPos(x()-10,y());
    QList<QGraphicsItem *> hitPlayer = collidingItems();
    for(int i = 0, n = hitPlayer.size(); i < n;i++) {
        if (typeid(*hitPlayer[i]) == typeid(GraphicsPlayer)) {
            w->player->hitByMonster(w->room->getGEnemy()->getAttackPower());
            w->tracker->setPlayerHealth(w->player->getHealth());
            w->tracker->setPlayerStress(w->player->getStress());
            scene()->removeItem(this);
            w->enterText("You have lost " + QString::number(w->room->getGEnemy()->getAttackPower())
                                        +" health");
            w->waitForAttack(1);
        }
    }
}
