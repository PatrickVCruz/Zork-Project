#ifndef UITRACKER_H
#define UITRACKER_H

#include <QGraphicsTextItem>
#include <QObject>

class UiTracker: public QGraphicsTextItem
{
public:
    UiTracker(QGraphicsTextItem * parent=0);

    void setPlayerHealth(int value);
    void setPlayerStress(int value);
    void setBatterLevel(int value);

private:
    int playerHealth;
    int playerStress;
    int batterLevel;
};

#endif // UITRACKER_H
