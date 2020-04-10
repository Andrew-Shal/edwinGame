#include "user_schema.h"

user_schema::user_schema(int u_id, QString u_name)
{
    _userID = u_id;
    _userName = u_name;

    _dateCreated = "";
    _isRemoved = 0;
    _dateRemoved = "";
}

user_schema::user_schema()
{
    _userID = -1;
    _userName = "";

    _dateCreated = "";
    _isRemoved = 0;
    _dateRemoved = "";
}

int user_schema::userID()
{
    return _userID;
}

QString user_schema::userName()
{
    return _userName;
}

QString user_schema::password()
{
    return _password;
}

void user_schema::userID(int u_id)
{
    _userID = u_id;
}

void user_schema::userName(QString u_name)
{
    _userName = u_name;
}

void user_schema::password(QString password)
{
    _password = password;
}

QString user_schema::dateCreated()
{
    return _dateCreated;
}

void user_schema::dateCreated(QString date)
{
    _dateCreated = date;
}

QString user_schema::dateRemoved()
{
    return _dateRemoved;
}

int user_schema::isRemoved()
{
    return _isRemoved;
}

void user_schema::isRemoved(int removed)
{
    _isRemoved = removed;
}

void user_schema::dateRemoved(QString date)
{
    _dateRemoved = date;
}

// copy ctor
user_schema &user_schema::operator =(const user_schema &t)
{
    _userID = t._userID;
    _userName = t._userName;
    _password = t._password;
    _isRemoved = t._isRemoved;
    _dateCreated = t._dateCreated;
    _dateRemoved = t._dateRemoved;
    return *this;
}

QDebug operator<<(QDebug debug, const user_schema &u)
{
    QDebugStateSaver saver(debug);
    debug.nospace() << "user: (" << u._userID << ", " << u._userName <<", "<< u._dateCreated << ", " << u._dateRemoved << ", " << u._isRemoved << ')';

    return debug;
}
