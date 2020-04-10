#ifndef USER_DB_SCHEMA_H
#define USER_DB_SCHEMA_H

#include <QString>
#include <QDebug>

class user_schema
{
public:
    user_schema(int u_id, QString u_name);
    user_schema();
    int userID();
    QString userName();
    QString password();

    void userID(int u_id);
    void userName(QString u_name);
    void password(QString password);
    QString dateCreated();
    void dateCreated(QString date);
    QString dateRemoved();
    int isRemoved();
    void isRemoved(int removed);
    void dateRemoved(QString date);
    user_schema & operator =(const user_schema &t);

    friend QDebug operator <<(QDebug debug, const user_schema& u);

private:
    int _userID;
    QString _userName;
    QString _password;
    QString _dateCreated;
    QString _dateRemoved;
    int _isRemoved;
};

#endif // USER_DB_SCHEMA_H
