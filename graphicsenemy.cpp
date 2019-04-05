#include "graphicsenemy.h"

GraphicsEnemy::GraphicsEnemy() {
    setPos(600,270/2);
    health = 100;
    srand(time(NULL));
    enemyType = (rand() % 4);
    setDescription("Monster type: " + typesOfMonster[enemyType]);
    setEnemy(enemyType);
    setMonsterName(typesOfMonster[enemyType]);
    attackValue = 10;
}

void GraphicsEnemy::setEnemy(int i) {
    switch(i) {
    case 0:
        setPixmap(QPixmap(":/imgs/resources/Characters/Isaac.png"));
        break;
    case 1:
        setPixmap(QPixmap(":/imgs/resources/Characters/Dead_Baby.png"));
        break;
    case 2:
        setPixmap(QPixmap(":/imgs/resources/Characters/Guppy.png"));
        break;
    case 3:
        setPixmap(QPixmap(":/imgs/resources/Characters/Vampire.png"));
        break;
    }
}

void GraphicsEnemy::attackPlayer() {
    monsterHit * spookyBullet = new monsterHit();
    spookyBullet->setPos(x(),y()+(y()/2));
    scene()->addItem(spookyBullet);
}

string GraphicsEnemy::getMonsterName() const
{
    return monsterName;
}

void GraphicsEnemy::setMonsterName(const string &value)
{
    monsterName = value;
}

void GraphicsEnemy::hitPlayer(GraphicsPlayer *mc){
    mc->hitByMonster(attackValue);
}

void GraphicsEnemy::shunWithAFlashlight(int playerAttack)
{
    health = health - playerAttack;
}
