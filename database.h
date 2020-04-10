#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QtSql>

class Database{
public:
    Database(QString databaseName);
    void createConnection();
    void setDbFileName(QString db_name);
    void prepareTables();
    QSqlQuery execQuery(QString sql);
    QString getDbFileName();
    void closeConnection();
    bool openConnection();
    QSqlQuery execTransaction(QString sql);
private:
    QString _dbFileName;
    QSqlDatabase _db;
};

#endif // DATABASE_H



