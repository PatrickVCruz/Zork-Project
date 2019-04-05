#include "hauntedhouse.h"
#include <QApplication>
#include <character.h>
#include <player.h>
#include <iostream>
#include <sstream>
#include <QDebug>

using namespace std;

hauntedHouse * w;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    w = new hauntedHouse();
    w->show();

    return a.exec();


}

//void doEvent(Player *player) // pointer to player
//{
//    int rand = qrand() % 3;
//    switch (rand)
//    {
//        case 0: // Item
//            Item item = randomItem();
//            player->addItem(item);
//            cout << item.name << " added to inventory";

//            break;
//        case 1: // Monster

//            break;
//        case 2: // Nothing
//            // Do nothing
//            break;
//    }
//}
