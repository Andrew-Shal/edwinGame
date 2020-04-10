#include "player.h"
#include <QDebug>
#include "bullet.h"
#include "enemy.h"
#include <QGraphicsScene>


Player::Player(QGraphicsItem *parent) : QGraphicsPixmapItem(parent)
{
    bulletsound = new QMediaPlayer();
    bulletsound->setMedia(QUrl("qrc:/sounds/sounds/bullet.wav"));

    // set graphic
    setPixmap(QPixmap(":/images/images/player.png"));
}

void Player::keyPressEvent(QKeyEvent *event)
{
    //qDebug()<<"MyRect knows that you pressed a key";
    if(event->key() == Qt::Key_Left){
        if(pos().x() > 0)
            setPos(x() - 10, y());
    }
    else if(event->key() == Qt::Key_Right){
        if(pos().x() + 100 < 800)
            setPos(x() + 10, y());
    }
    else if(event->key() == Qt::Key_Space)
    {
        //create a bullet object
        Bullet *bullet = new Bullet();
        bullet->setPos(x(), y()); // uses x and y coordinates our rectangle
        scene()->addItem(bullet);

        //play bullet sound
        if(bulletsound->state() == QMediaPlayer::PlayingState){
            bulletsound->setPosition(0);
        }
        else if(bulletsound->state() == QMediaPlayer::StoppedState){
            bulletsound->play();
        }
    }
}

void Player::spawn()
{
    //create a new enemy
    Enemy *enemy = new Enemy();

    //add newly created enemy to the same scene as the player
    scene()->addItem(enemy);
}
