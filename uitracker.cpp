#include "uitracker.h"
#include <QFont>
#include <string>

UiTracker::UiTracker(QGraphicsTextItem *parent)
{
    playerHealth = 100;
    playerStress = 0;
    batterLevel = 100;
    setPlainText(QString("Health " + QString::number(playerHealth))
                         +"\nStress " + QString::number(playerStress));
    setDefaultTextColor(Qt::white);
    setFont(QFont("times",12));
}

void UiTracker::setPlayerHealth(int value) {
    playerHealth = value;
    setPlainText(QString("Health " + QString::number(playerHealth))
                 +"\nStress " + QString::number(playerStress)
                 +"\nBattery " + QString::number(batterLevel));
}


void UiTracker::setPlayerStress(int value)
{
    playerStress = value;
    setPlainText(QString("Health " + QString::number(playerHealth))
                 +"\nStress " + QString::number(playerStress)
                 +"\nBattery " + QString::number(batterLevel));
}

void UiTracker::setBatterLevel(int value)
{
    batterLevel = value;
    setPlainText(QString("Health " + QString::number(playerHealth))
                 +"\nStress " + QString::number(playerStress)
                 +"\nBattery " + QString::number(batterLevel));
}

