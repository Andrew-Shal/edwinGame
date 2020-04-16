#include "health.h"
#include <QMessageBox>
#include <QFont>
#include <QGraphicsScene>
#include <QMessageBox>
#include <QApplication>

Health::Health(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    //initialize the health to 3
    health = 3;

    //draw the text
    setPlainText(QString("Health: ") + QString::number(health)); //Health: 3
    setDefaultTextColor(Qt::red);
    setFont(QFont("times", 16));
}

void Health::decrease()
{
    health--;
    setPlainText(QString("Health: ") + QString::number(health));

    if(health == 0){
        emit died();
    }
}

int Health::getHealth()
{
    return health;
}



