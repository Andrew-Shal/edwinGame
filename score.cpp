#include "score.h"
#include <QFont>

Score::Score(QGraphicsItem *parent)
{
    //initialize score to zero
    score = 0;

    //draw the score
    setPlainText(QString("Score: ") + QString::number(score));

    //change text color
    setDefaultTextColor(Qt::white);

    //change text font
    setFont(QFont("times", 16));

}

void Score::increase()
{
    score++;
    setPlainText( QString("Score: ") + QString::number(score) );
}

int Score::getScore()
{
    return score;
}
