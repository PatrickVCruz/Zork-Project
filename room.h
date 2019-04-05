#ifndef ROOM_H
#define ROOM_H
#include "player.h"
#include "graphicsenemy.h"
#include <string>
#include <items.h>
#include <character.h>
#include <objectarray.h>
#include <graphicsplayer.h>
#include <graphicsenemy.h>
#include <torchlight.h>

using namespace std;

class GraphicsEnemy;

class Room
{
public:
    Room();
    Room(int outcome);
    string description;
    int roomNumber;
    int firstRoom;
    int lastRoom;
    items *itemsInRoom;
    int lootInRoom = 0;
    int monsterInRoom = 0;
    int getRoomNumber() const;
    void setRoomNumber(int value);
    string getDescription() const;
    void setDescription(const string &value);
    void updateDescription(string value);

    GraphicsEnemy *getGEnemy() const;

    int getMonsterInRoom() const;
    items *checkRoom();

    void setMonsterInRoom(int value);

protected:
private:
    GraphicsEnemy * gEnemy;
};

#endif // ROOM_H
