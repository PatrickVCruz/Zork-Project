#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"
#include "items.h"
#include "torchlight.h"
#include <GraphicsPlayer.h>

using namespace std;

class GraphicsPlayer;

class Player: public Character {
private:
    string playerName;
    int playerCondition;
    string playerStressSickness[4] = {"Player is fine","Hopeless","Paranoid","Fearful"};
    int stress;
    int playerStressed = 0;
    int healthLostbyStressed;
    int flashlightLevel = 100;
    void rechargeFlashlight(battery *battery);
    flashlight flashlight;

public:
    Player();
    int getFlashlightLevel() const;
    void setFlashlightLevel(int value);
    int getStress() const;
    void setStress(int value);
    Player(string name);
    void isStressed();
    void stressSickness();
    void useItem();
    void relieveStress(int stressToRelieve);
    void hitByMonster(int healthLost);
    string getPlayerName() const;
    void setPlayerName(const string &value);
    void useFlashLight();
};

class Enemy: public Character
{
public:
    Enemy();
    string typesOfMonster[4] = {"Ghost","Zombie","Werewolf","Vampire"};
    string monsterName;
    void hitPlayer(GraphicsPlayer * mc);
    void shunWithAFlashlight(int playerAttack);
    string getMonsterName() const;
    void setMonsterName(const string &value);

protected:
    int enemyType;
};


#endif // PLAYER_H
