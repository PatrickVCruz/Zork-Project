#ifndef HAUNTEDHOUSE_H
#define HAUNTEDHOUSE_H

#include <QMainWindow>
#include <stdlib.h>
#include <items.h>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtCore>
#include <QtGui>
#include <vector>
#include <uitracker.h>
#include <graphicsplayer.h>
#include <graphicsenemy.h>

#include "room.h"
#include "character.h"

using namespace std;

class Room;

namespace Ui {
class hauntedHouse;
}

class hauntedHouse : public QMainWindow
{
    Q_OBJECT

public:
    explicit hauntedHouse(QWidget *parent = 0);
    ~hauntedHouse();
    string name;
    Room * room;
    GraphicsPlayer * player;
    UiTracker * tracker;
    GraphicsEnemy * gEnemy;
    void goUpRoom();
    void waitForAttack(int x);
    QGraphicsScene * scene;
    int monsterInTheWay = 1;
    void gameOver();
    void enableMovement(int i);
    void changeSetting(int i);
    void goDownRoom();
    void enterText(QString text);
private slots:

    void on_goToNextTab_clicked();

    void on_gamePageBut_clicked();

    void on_quitButton_clicked();

    void on_FlashlightButton_clicked();

    void on_itemButton_clicked();

    void on_RightButton_clicked();
    void on_LeftButton_clicked();

    void on_UpButton_clicked();

    void on_DownButton_clicked();

    void on_playAgain_clicked();

private:
    int roomNumber = 0;
    int keyRoom ;
    Ui::hauntedHouse *ui;
    QGraphicsEllipseItem * ellipseItem;
    QGraphicsEllipseItem * ellipseItem1;
    QGraphicsRectItem * rect;
    QGraphicsItem * moveItem;

    int noOfRooms;
    vector<Room *> * mapOfRooms;
    void createRooms();

    void playGame();
};

#endif // HAUNTEDHOUSE_H
