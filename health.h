#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>


class Health : public QGraphicsTextItem
{
    Q_OBJECT
signals:
    void died();
public:
    Health(QGraphicsItem *parent = 0);
    void decrease();
    int getHealth();
private:
    int health;
};

#endif // HEALTH_H
