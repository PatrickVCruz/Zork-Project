#ifndef CHARACTER_H
#define CHARACTER_H
#include "items.h"

#include <string>
#include <ctime>

using namespace std;

class Character
{
protected:
    string description;
    items *inventory;
    int health;
    int attackValue;

public:
    Character() {

    }
    string getDescription() const
    {
        return description;
    }
    void setDescription(const string &value)
    {
        description = value;
    }
    void addInventory(items * item) {
        inventory = item;
    }
    void useItem(items item);
    int getHealth() const;
    void setHealth(int value);
    void loseHealth(int value);
    items *getInventory() const;
    int getAttackPower() const;
};


#endif // CHARACTER_H
