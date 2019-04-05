#include "room.h"

int Room::getRoomNumber() const
{
    return roomNumber;
}

void Room::setRoomNumber(int value)
{
    roomNumber = value;
}

string Room::getDescription() const
{
    return description;
}

void Room::setDescription(const string &value)
{
    description = value;
}

void Room::updateDescription(string value) {
    description = description + "\n" +value;
}

Room::Room()
{
    updateDescription("This is the starting room");
    setRoomNumber(5);
}

Room::Room(int outcome) {

    srand(time(NULL));
    int typeOfLoot = (rand() % 3)+1;

    switch (outcome)
    {
    case 0: // Item
        if(typeOfLoot == 1)
            itemsInRoom = new battery;
        else if(typeOfLoot == 2)
            itemsInRoom = new healthPack;
        else if(typeOfLoot == 3)
            itemsInRoom = new antiStressPack;
        setDescription("There is a " + itemsInRoom->getName()+ " in this room");
        setRoomNumber(outcome);
        break;
    case 1: // Monster
        gEnemy = new GraphicsEnemy();
        setDescription("There is a "+gEnemy->getMonsterName());
        monsterInRoom = 1;
        setRoomNumber(outcome);
        break;
    case 2: // Nothing
        setDescription("There is nothing found in this room");
        setRoomNumber(outcome);
        break;
    case 3:
        setDescription("This is the final room");
        lastRoom = 1;
        setRoomNumber(outcome);
        break;
    case 4:
        setDescription("There is a key in this room");
        itemsInRoom = new roomKey();
        setRoomNumber(outcome);
        break;
    }
}

void Room::setMonsterInRoom(int value)
{
    monsterInRoom = value;
}

int Room::getMonsterInRoom() const
{
    return monsterInRoom;
}

items* Room::checkRoom() {
    return itemsInRoom;
}

GraphicsEnemy *Room::getGEnemy() const
{
    return gEnemy;
}
