#include "hauntedhouse.h"
#include "hauntedhouse.h"
#include "ui_hauntedhouse.h"

#include <QBrush>
#include <QImage>

hauntedHouse::hauntedHouse(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::hauntedHouse)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->gameGraphics->setBackgroundBrush(QBrush(QImage(":/imgs/resources/Bonus/Loading_screen_Crypts.png")));
    scene->setBackgroundBrush(QBrush(QImage(":/imgs/resources/Bonus/Loading_screen_Crypts.png")));
    ui->gameGraphics->setScene(scene);
    ui->gameGraphics->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameGraphics->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->gameGraphics->setFixedSize(740,270);
    ui->playAgain->setPalette(QPalette(Qt::transparent, Qt::transparent, Qt::transparent,
                                       Qt::transparent, Qt::transparent, Qt::transparent,
                                       Qt::transparent, Qt::transparent, Qt::transparent));

    ui->gameConsoleBox->setFont(QFont("Times",14));
    playGame();
}

hauntedHouse::~hauntedHouse()
{
    delete ui;
}

void hauntedHouse::playGame() {


    createRooms();
    player = new GraphicsPlayer("Pat");
    tracker = new UiTracker();
    tracker->setPlayerHealth(player->getHealth());
    tracker->setPlayerStress(player->getStress());

    scene->addItem(player);
    scene->addItem(tracker);
    scene->setSceneRect(0,0,740,270);
    player->setPos(50,ui->gameGraphics->height()/2);
    room = mapOfRooms->at(0);
    ui->gameConsoleBox->setText(QString::fromStdString(room->getDescription()));
    if(room->getRoomNumber()==1)
        ui->FlashlightButton->setEnabled(1);
    else
        ui->FlashlightButton->setEnabled(0);

}

void hauntedHouse::on_goToNextTab_clicked()
{
    ui->gameWindow->setCurrentIndex(1);
}

void hauntedHouse::on_gamePageBut_clicked()
{
    ui->gameWindow->setCurrentIndex(0);
}

void hauntedHouse::on_quitButton_clicked()
{
    this->close();
}

void hauntedHouse::on_FlashlightButton_clicked() {
    if(player->getFlashlightLevel() <= 0) {
        ui->gameConsoleBox->setText("You cannot use your flashlight, you need to recharge it");
    }
    else{
        player->useFlashLight();
        player->shineFlashlight();
        player->batteryDown();
    }
}


void hauntedHouse::on_RightButton_clicked()
{
    ui->RightButton->setEnabled(false);
    ui->LeftButton->setEnabled(false);
    if(room->getMonsterInRoom() == 1) {
        ui->gameConsoleBox->setText("There is a monster in the way, you cannot is go any further");
    }
    else {
        player->move(1);
        monsterInTheWay = 0;
    }
}

void hauntedHouse::on_LeftButton_clicked()
{
    player->move(0);
    ui->RightButton->setEnabled(false);
    ui->LeftButton->setEnabled(false);
}

void hauntedHouse::on_itemButton_clicked()
{
    player->useItem();
}

void hauntedHouse::createRooms() {
    mapOfRooms = new vector<Room *>;
    keyRoom = (rand() % 9)+ 6;
    noOfRooms = (rand() % 10) + 7;
    room = new Room();
    mapOfRooms->push_back(room);
    room = new Room(3);
    mapOfRooms->push_back(room);
}


void hauntedHouse::on_UpButton_clicked()
{
    if(player->pos().x() >= 500) {
        if(room->getRoomNumber()==0) {
            player->addInventory(room->checkRoom());
            scene->removeItem(room->checkRoom());
        }

        if(room->getRoomNumber()==3) {
            gameOver();
        }

        if(monsterInTheWay)
            ui->gameConsoleBox->setText("You must go to the end of the room to go to the next room");
        else {
            if(roomNumber <= noOfRooms)
                roomNumber++;
            else if(roomNumber == noOfRooms && player->getHasKey()) {
                ui->gameConsoleBox->setText("Final Room");
            }
            else
                ui->UpButton->setEnabled(0);

            if(room->getRoomNumber() == 1) {
                scene->removeItem(room->getGEnemy());
                delete room->getGEnemy();
            }
            goUpRoom();
        }
    }
    else
        ui->gameConsoleBox->setText(QString::fromStdString("You must go to the end of the room to go to the next room"));
}

void hauntedHouse::goUpRoom() {
    player->moveLeft();
    srand(time(0));
    changeSetting(rand()%5);
    int outcome = (rand() % 3);
    if(roomNumber == keyRoom) {
        room = new Room(4);
    }
    else if(roomNumber == noOfRooms)
        room = mapOfRooms->at(1);
    else
        room = new Room(outcome);

    if(room->getRoomNumber()== 1) {
        monsterInTheWay = 1;
        ui->FlashlightButton->setEnabled(1);
        scene->addItem(room->getGEnemy());
    }
    else if(room->getRoomNumber()== 0 || room->getRoomNumber()== 4) {
        scene->addItem(room->checkRoom());
    }
    else {
        ui->FlashlightButton->setEnabled(0);
    }
    monsterInTheWay = 1;
    ui->gameConsoleBox->setText(QString::fromStdString(room->getDescription()));
    mapOfRooms->push_back(room);
}

void hauntedHouse::waitForAttack(int x) {
    ui->FlashlightButton->setEnabled(x);
}
void hauntedHouse::gameOver() {
    ui->gameWindow->setCurrentIndex(2);
    player->stopTimer();
}

void hauntedHouse::enableMovement(int i) {
    if(i)
        ui->RightButton->setEnabled(1);
    else
        ui->LeftButton->setEnabled(1);
}

void hauntedHouse::changeSetting(int i) {
    switch(i) {
    case 0:
        ui->gameGraphics->setBackgroundBrush(QBrush(QImage(":/imgs/resources/Bonus/Loading_screen_Crypts.png")));
        break;
    case 1:
        ui->gameGraphics->setBackgroundBrush(QBrush(QImage(":/imgs/resources/chapel.png")));
        break;
    case 2:
        ui->gameGraphics->setBackgroundBrush(QBrush(QImage(":/imgs/resources/library.png")));
        break;
    case 3:
        ui->gameGraphics->setBackgroundBrush(QBrush(QImage(":/imgs/resources/stone_corridor.png")));
        break;
    case 4:
        ui->gameGraphics->setBackgroundBrush(QBrush(QImage(":/imgs/resources/stone_corridor_2.png")));
        break;
    case 5:
        ui->gameGraphics->setBackgroundBrush(QBrush(QImage(":/imgs/resources/warrens.png")));
        break;
    }
}

void hauntedHouse::on_DownButton_clicked() {
    if(player->pos().x() < 200) {
        if(roomNumber > 0) {
            changeSetting(rand()%5);
            roomNumber--;
            if (room->getRoomNumber() == 1)
                scene->removeItem(room->getGEnemy());
            else if(room->getRoomNumber() == 0)
                scene->removeItem(room->checkRoom());
            player->moveRight();
            room = mapOfRooms->at(roomNumber);
            if(room->getRoomNumber() == 0) {
                scene->addItem(room->checkRoom());
            }
            else if(room->getRoomNumber() == 1)
                scene->addItem(room->getGEnemy());
            monsterInTheWay = 0;
            ui->gameConsoleBox->setText(QString::fromStdString(room->getDescription()));
        }
    }
    else
        ui->gameConsoleBox->setText(QString::fromStdString("You must go to the start of the room to go to the previous room"));

}

void hauntedHouse::enterText(QString text) {
    ui->gameConsoleBox->setText(text);
}

void hauntedHouse::goDownRoom(){

}

void hauntedHouse::on_playAgain_clicked()
{
    scene = new QGraphicsScene(this);
    ui->gameGraphics->setBackgroundBrush(QBrush(QImage(":/imgs/resources/Bonus/Loading_screen_Crypts.png")));
    scene->setBackgroundBrush(QBrush(QImage(":/imgs/resources/Bonus/Loading_screen_Crypts.png")));
    ui->gameGraphics->setScene(scene);
    ui->gameWindow->setCurrentIndex(0);
    playGame();
}
