#include "bullet.h"
#include "enemy.h"
#include <QDebug>
#include <QTimer>
#include <QGraphicsScene>
#include <QList>
#include "game.h"

extern Game * game; //place this at the very top of your file

Bullet::Bullet(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    //build a bullet
    setPixmap(QPixmap(":/images/images/bullet.png"));
    //connect
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50); //emits timeout() signal every 50 milliseconds
}

void Bullet::move()
{
    //if bullet collides with enemy, destroy both
    QList<QGraphicsItem *>colliding_items_list = collidingItems();
    int listCount = colliding_items_list.size();
    for(int i = 0; i < listCount; i++){
        if(typeid (*(colliding_items_list[i])) == typeid (Enemy)){
            //increase the score
            game->score->increase();
            //remove them both
            scene()->removeItem(colliding_items_list[i]); //remove current enemy
            scene()->removeItem(this); //remove the current bullet

            //release memory for removed bullet and enemy
            delete colliding_items_list[i];
            delete this;
            return;//once a bullet is removed and destroyed, leave the function to prevent code from moving bullet below
        }
    }// end for

    //move bullet up
    setPos(x(), y() - 10);
    if((pos().y()+pixmap().height()) < 0){
        scene()->removeItem(this);
        delete this;
        //qDebug()<<"Bullet Deleted";
    }
}
