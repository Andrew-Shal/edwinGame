#include "enemy.h"
#include <QGraphicsScene>
#include <QTimer>
#include <QList>
#include <QDebug>
#include "game.h"

using std::srand;
using std::rand;

extern Game * game; //says there is an external Game object pointer, game, that we will access

Enemy::Enemy(QGraphicsItem *parent): QObject(), QGraphicsPixmapItem(parent)
{
    //700 ensures enemies are created within our screen’s 800 width because the rand num will be a value
    //in the range of 0 and 699. However, we must take into account that the width of the enemy is 100
    int random_x = rand() % 700;
    setPos(random_x, 0);

    //draw Enemy rect/image the same size as our player rect
    setPixmap(QPixmap(":/images/images/enemy.png"));
//    setTransformOriginPoint(50,50);
//    setRotation(180);

    QTimer *timer = new QTimer(this);

    //connect
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50); //repeat countdown clock to emit timeout() signal every 50 milliseconds

}

void Enemy::move()
{
    setPos(x(), y()+5); //enemy is moving down so we increase the y value. We inclrease by 5 to be slower than the bullet
    if(pos().y() > 600){
        //decrease the health
        game->health->decrease();

        scene()->removeItem(this);
        delete this;
        //qdebug()<<"Enemy deleted";
    }

}
