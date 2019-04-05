#include "items.h"

items::items() {

}

string items::getName() const
{
    return name;
}

void items::setName(const string &value)
{
    name = value;
}

string items::getDescription() const
{
    return description;
}

void items::setDescription(const string &value)
{
    description = value;
}

void items::setItemValue(int value)
{
    itemValue = value;
}

battery::battery() {
    setItemValue(0);
    setDescription("This is a battery that will recharge your flashlight");
    setName("Batery");
    setPixmap(QPixmap(":/imgs/resources/Items/63_the_battery"));
    setPos(400,(270/2)+ 50);
}

int battery::getBatteryPower() const
{
    return BatteryPower;
}

healthPack::healthPack() {
    setItemValue(1);
    setName("Health Pack");
    setDescription("This is a healthpack that will heal 50 points of health");
    setPixmap(QPixmap(":/imgs/resources/Items/13_the_virus.png"));
    setPos(400,(270/2)+ 50);
}

int healthPack::getHealthPower() const
{
    return healthPower;
}


flashlight::flashlight(){
    setItemValue(4);
    setDescription("This is used to keep stress away and fight monsters");
}

int flashlight::getBatteryLevel() const
{
    return batteryLevel;
}

void flashlight::rechargeBattery(items *battery) {
    batteryLevel = 100;
}

void flashlight::decreaseBattery() {
    batteryLevel = batteryLevel - 1;
}

void flashlight::attackMonster()
{
    batteryLevel = batteryLevel - 25;
}

roomKey::roomKey() {
   setItemValue(3);
   setName("Key");
   setDescription("This is used to open the door to the last room");
   setPixmap(QPixmap(":/imgs/resources/Items/175_dads_key.png"));
   setScale(0.75);
   setPos(400,(270/2)+ 50);
}

antiStressPack::antiStressPack()
{
    setItemValue(2);
    setName("Pill");
    setDescription("This is an item that will relieve stress");
    setPixmap(QPixmap(":/imgs/resources/Items/102_moms_bottle_of_pills.png"));
    setPos(400,(270/2)+ 50);
    setScale(0.75);
}

int antiStressPack::getRelieveStressPower() const
{
    return relieveStressPower;
}
