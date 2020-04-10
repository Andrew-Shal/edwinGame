#include "score_schema.h"

score_schema::score_schema()
{
   _scoreId = -1;
   _score = 0;
   _user = user_schema();
   _userRefID = _user.userID();
   _dateCreated = "";
   _isRemoved = 0;
   _dateRemoved = "";
}

score_schema::score_schema(int id, int score, user_schema user)
{
    _scoreId = id;
    _score = score;
    _userRefID = user.userID();
    _user = user;

    _dateCreated = "";
    _isRemoved = 0;
    _dateRemoved = "";
}

int score_schema::scoreID()
{
    return _scoreId;
}

int score_schema::score()
{
    return _score;
}

void score_schema::scoreID(int id)
{
    _scoreId = id;
}

void score_schema::score(int score)
{
    _score = score;
}

int score_schema::userRefID()
{
    return _userRefID;
}

QString score_schema::dateCreated()
{
    return _dateCreated;
}

void score_schema::dateCreated(QString created)
{
    _dateCreated = created;
}

QString score_schema::dateRemoved()
{
    return _dateRemoved;
}

int score_schema::isRemoved()
{
    return _isRemoved;
}

void score_schema::isRemoved(int removed)
{
    _isRemoved = removed;
}

void score_schema::dateRemoved(QString date)
{
    _dateRemoved = date;
}

void score_schema::userRefID(int u_id)
{
    _userRefID = u_id;
}

user_schema score_schema::getReferencedUser()
{
    return _user;
}

void score_schema::setReferencedUser(user_schema user)
{
    _user = user;
}

// copy ctor
score_schema &score_schema::operator =(const score_schema &t)
{
    _user = t._user;
    _score = t._score;
    _scoreId = t._scoreId;

    _userRefID = t._userRefID;
    _dateCreated = t._dateCreated;
    _isRemoved = t._isRemoved;
    _dateRemoved = t._dateRemoved;
    return *this;
}

QDebug operator<<(QDebug debug, const score_schema &s)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "score: (" << s._scoreId << ", " << s._userRefID << ", " << s._score << ", " << s._dateCreated << ", " << s._dateRemoved << ", " << s._isRemoved << ", " << s._user << ')';

    return debug;
}
