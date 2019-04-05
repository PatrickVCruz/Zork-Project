#include "graphicsplayer.h"

#include "hauntedhouse.h"

extern hauntedHouse * w;

GraphicsPlayer::GraphicsPlayer() {
    health = 100;
    stress = 0;
    setPixmap(QPixmap(":/imgs/resources/Characters/Issac.png"));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(becomeStressed()));
    timer->start(2000);
}

GraphicsPlayer::GraphicsPlayer(string name, QGraphicsItem *parent)
{
    health = 100;
    setPlayerName(name);
    setDescription("Player: "+ playerName);
    attackValue = 25;
    setPixmap(QPixmap(":/imgs/resources/Characters/Cain.png"));
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    setTransformOriginPoint(116/2,132/2);
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(becomeStressed()));
    timer->start(2000);
}

void GraphicsPlayer::stopTimer() {
    timer->stop();
}

void GraphicsPlayer::moveLeft()
{
    if(pos().x() - 550 > 0)
        setPos(x() - 550,y());
}

void GraphicsPlayer::moveRight()
{
    if(pos().x() + 500 < 740)
        setPos(x() + 550,y());
}

void GraphicsPlayer::shineFlashlight()
{
    torch = new torchLight();
    torch->setPos(x()+120,y()+60);
    scene()->addItem(torch);
}

void GraphicsPlayer::hitByMonster(int healthLost) {
    loseHealth(healthLost);
    setStress(5);
}

int GraphicsPlayer::getStress() const
{
    return stress;
}

void GraphicsPlayer::setStress(int value)
{
    stress = stress + value + stressValue;
}


void GraphicsPlayer::relieveStress(int stressToRelieve) {
    stress = stress - stressToRelieve;
    if(stress < 0)
        stress = 0;
}

int GraphicsPlayer::getFlashlightLevel() const
{
    return flashlightLevel;
}

void GraphicsPlayer::setFlashlightLevel(int value)
{
    flashlightLevel = value + flashlightLevel;
    if(flashlightLevel > 100)
        flashlightLevel = 100;
}

string GraphicsPlayer::getPlayerName() const
{
    return playerName;
}

void GraphicsPlayer::setPlayerName(const string &value)
{
    playerName = value;
}

void GraphicsPlayer::useFlashLight()
{
    flashlight.attackMonster();

}

void GraphicsPlayer::batteryDown() {
    flashlightLevel = flashlightLevel - 5;
    if(stressAffliction == playerStressSickness[3])
        flashlightLevel = flashlightLevel - 5;
}

void GraphicsPlayer::move(int i)
{
    moveTimer = new QTimer();
    if(i) {
        connect(moveTimer,SIGNAL(timeout()),this,SLOT(walkRight()));
    }
    else {
        connect(moveTimer,SIGNAL(timeout()),this,SLOT(walkLeft()));
    }
    moveTimer->start(50);
}

void GraphicsPlayer::walkRight() {
    if(pos().x() < 570) {
        setPos(x()+10,y());
        pickUpItem();
    }
    else {
        moveTimer->stop();
        w->enableMovement(1);
        w->enableMovement(0);
    }
}

void GraphicsPlayer::walkLeft() {
    setTransform(QTransform::fromScale(-1, 1));
    if(pos().x() > 125) {
        setPos(x()-10,y());
        pickUpItem();
    }
    else {
        moveTimer->stop();
        w->enableMovement(0);
        w->enableMovement(1);
        setTransform(QTransform::fromScale(1,1));
    }
}

void GraphicsPlayer::pickUpItem() {
    QList<QGraphicsItem *> foundItem = collidingItems();
    for(int i = 0, n = foundItem.size(); i < n;i++) {
        if (typeid(*foundItem[i]) == typeid(battery)
                || typeid(*foundItem[i]) == typeid(roomKey)
                || typeid(*foundItem[i]) == typeid(antiStressPack)
                || typeid(*foundItem[i]) == typeid(healthPack)) {
            scene()->removeItem(foundItem[i]);
            if(typeid(*foundItem[i]) == typeid(roomKey)) {
                hasKey =1;
                w->enterText(QString::fromStdString("You have picked up the key for the final room"));
            }
            else if(typeid(*foundItem[i]) == typeid(battery)) {
                rechargeFlashlight(new battery);
                w->enterText(QString::fromStdString("You have picked up the a battery and recharged your torch"));
            }
            else if(typeid(*foundItem[i]) == typeid(antiStressPack)) {
                antiStressPack pill;
                relieveStress(pill.getRelieveStressPower());
                w->enterText(QString::fromStdString("You have picked up pills and been relieved of some stress"));
            }
            else if(typeid(*foundItem[i]) == typeid(healthPack)) {
                healthPack hp;
                setHealth(hp.healthPower);
                w->enterText(QString::fromStdString("You have picked up health and restored some health"));
            }
        }
    }
}

int GraphicsPlayer::getHasKey() const {
    return hasKey;
}

void GraphicsPlayer::becomeStressed() {
    if(flashlightLevel > 75) {
        setStress(0);
    }
    else if (flashlightLevel < 75 && flashlightLevel > 50) {
        setStress(0);
    }
    else if(flashlightLevel < 50 && flashlightLevel > 25){
        setStress(2);
    }
    else if(flashlightLevel < 25 && flashlightLevel > 0){
        setStress(5);
    }
    else {
        setDescription("You can no longer use your torch");
    }
    isStressed();
    w->tracker->setPlayerHealth(w->player->getHealth());
    w->tracker->setPlayerStress(w->player->getStress());
    w->tracker->setBatterLevel(w->player->getFlashlightLevel());
    if(getStress() == 100 || getHealth() == 0)
        w->gameOver();
}

void GraphicsPlayer::rechargeFlashlight(battery *battery)
{
    flashlight.rechargeBattery(battery);
    setFlashlightLevel(battery->getBatteryPower());
}

void GraphicsPlayer::isStressed() {
    srand(time(NULL));
    if(stress > 25) {
        playerStressed = 1;
        healthLostbyStressed = 0;
    }
    else if(stress < 50 && stress > 25) {
        playerStressed = 1;
        healthLostbyStressed = 5;
    }
    else if(stress < 75 && stress > 50) {
        playerStressed = 0;
        healthLostbyStressed = 10;
        playerCondition = (rand() % 4);
        stressSickness();
    }
    else if(stress < 100 && stress > 75) {
        playerStressed = 0;
        healthLostbyStressed = 15;
    }
    else if (stress == 100){
        playerStressed = 0;
        healthLostbyStressed = 20;
    }
}

void GraphicsPlayer::stressSickness() {
    w->enterText(QString::fromStdString("You have caught an affliction"));
    stressAffliction = playerStressSickness[playerCondition];
    if(playerCondition == 0) {
        //Player is fine
        health = 100;
        stress = 0;
        w->enterText(QString::fromStdString("You have been "+ stressAffliction
                                            +" your health has been restored and no longer stressed"));
    }
    else if(playerCondition == 1) {
        stressValue = 2;
        w->enterText(QString::fromStdString("You have become "+ stressAffliction
                                            +"\n you will get more stressed"));
        //{Player will get more stress
    }
    else if(playerCondition == 2) {
        attackValue = 20;
        w->enterText(QString::fromStdString("You have become "+ stressAffliction
                                            +"\n you will deal less damage"));
        //Player will do less damage with flashlight
    }
    else if(playerCondition == 3) {
        //Player's flashlight will use more battery
        w->enterText(QString::fromStdString("You have become "+ stressAffliction
                                            +"\n you will use up more of your battery"));
    }
}

void GraphicsPlayer::useItem() {
    if(inventory != 0) {
        if(inventory->itemValue == 0) {
            battery * bat = static_cast<battery*>(inventory);
            rechargeFlashlight(bat);
        }
        else if(inventory->itemValue == 1) {
            healthPack * healthRecovered = static_cast<healthPack*>(inventory);
            setHealth(healthRecovered->healthPower);
        }
        else if(inventory->itemValue == 2) {
            antiStressPack* pill= static_cast<antiStressPack*>(inventory);
            relieveStress(pill->getRelieveStressPower());
        }
    }
}

