
#include "Character.h"
#include <graphicsplayer.h>

int Character::getAttackPower() const
{
    return attackValue;
}

int Character::getHealth() const
{
    return health;
}

void Character::setHealth(int value)
{
    health =  health +value;
    if(health > 100)
        health = 100;
}

void Character::loseHealth(int value) {
    health =  health - value;
}


items *Character::getInventory() const
{
    return inventory;
}
