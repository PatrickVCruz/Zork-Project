#ifndef ITEMS_H
#define ITEMS_H

#include <string>
#include "QGraphicsPixmapItem"

using namespace std;

class items: public QGraphicsPixmapItem
{
public:
    items();
    int itemValue;
    string description;
    string name;
    void setItemValue(int value);
    string getDescription() const;
    void setDescription(const string &value);
    string getName() const;
    void setName(const string &value);
};

class battery: public items {
public :
    battery();
    int BatteryPower = 50;

    int getBatteryPower() const;
};

class healthPack: public items {
public:
    healthPack();
    int healthPower = 50;

    int getHealthPower() const;
};

class antiStressPack: public items {
public:
    antiStressPack();
    int relieveStressPower = 50;
    int getRelieveStressPower() const;
};

class flashlight: public items {
public:
    flashlight();
    int batteryLevel;
    void rechargeBattery(items *battery);
    void decreaseBattery();
    void attackMonster();

    int getBatteryLevel() const;
};

class roomKey: public items {
public:
    roomKey();
};

#endif // ITEMS_H
