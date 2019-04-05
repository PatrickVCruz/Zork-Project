#ifndef GRAPHICSPLAYER_H
#define GRAPHICSPLAYER_H

#include "character.h"
#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include <QList>


using namespace std;

class torchLight;

class GraphicsPlayer : public QObject, public QGraphicsPixmapItem, public Character {
    Q_OBJECT
public:
    GraphicsPlayer();
    GraphicsPlayer(string name, QGraphicsItem * parent=0);

    void shineFlashlight();
    int lightHit();
    int getFlashlightLevel() const;
    void setFlashlightLevel(int value);
    int getStress() const;
    void setStress(int value);
    void isStressed();
    void stressSickness();
    void useItem();
    void relieveStress(int stressToRelieve);
    void hitByMonster(int healthLost);
    string getPlayerName() const;
    void setPlayerName(const string &value);
    void useFlashLight();
    void move(int i);
    void batteryDown();
    int getHasKey() const;
    void stopTimer();
public slots:
    void moveLeft();
    void moveRight();
    void becomeStressed();
    void walkRight();
    void walkLeft();
private:
    torchLight * torch;
    string playerName;
    int hasKey = 0;
    int playerCondition;
    string stressAffliction;
    string playerStressSickness[4] = {"Brave","Hopeless","Paranoid","Fearful"};
    int stress = 0;
    int playerStressed = 0;
    int healthLostbyStressed;
    int flashlightLevel = 100;
    int stressValue = 0;
    void rechargeFlashlight(battery *battery);
    flashlight flashlight;
    QTimer * moveTimer;
    QTimer * timer;

    void pickUpItem();
};

#endif // GRAPHICSPLAYER_H
