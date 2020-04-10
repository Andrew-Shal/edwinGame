#ifndef SCORE_DB_SCHEMA_H
#define SCORE_DB_SCHEMA_H

#include<QString>
#include "user_schema.h"

class score_schema
{
public:
    score_schema();
    score_schema(int id, int score, user_schema user);
    int scoreID();
    int score();

    void scoreID(int id);
    void score(int score);
    void userRefID(int u_id);
    int userRefID();
    QString dateCreated(); // gets set by db
    void dateCreated(QString created);
    QString dateRemoved();
    int isRemoved();
    void isRemoved(int removed);
    void dateRemoved(QString date);
    user_schema getReferencedUser();
    void setReferencedUser(user_schema user);
    score_schema& operator = (const score_schema &t);

    friend QDebug operator <<(QDebug debug, const score_schema& u);

private:
    int _scoreId;
    int _score;
    int _userRefID;
    QString _dateCreated;
    QString _dateRemoved;
    int _isRemoved;
    user_schema _user;

};

#endif // SCORE_DB_SCHEMA_H
