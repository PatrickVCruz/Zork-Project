#ifndef GRAPHICSENEMY_H
#define GRAPHICSENEMY_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "player.h"
#include "character.h"
#include <torchlight.h>

class GraphicsEnemy : public QGraphicsPixmapItem, public Character {
public:
    GraphicsEnemy();
    void attackPlayer();

    string typesOfMonster[4] = {"Ghost","Zombie","Werewolf","Vampire"};
    string monsterName;
    int enemyType;
    void hitPlayer(GraphicsPlayer * mc);
    void shunWithAFlashlight(int playerAttack);
    string getMonsterName() const;
    void setMonsterName(const string &value);
    void setEnemy(int i);
private:
};

#endif // GRAPHICSENEMY_H
