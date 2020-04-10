#include "health.h"
#include <QFont>

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

}

int Health::getHealth()
{
    return health;
}



