#include "database.h"
#include <QDebug>

Database::Database(QString dbName){
    _dbFileName = dbName; // set filename

    createConnection();

    bool dbFileExists = QFile::exists( _dbFileName ); // test if db file exist

    // if db file doesn't exist,
    // we create empty db tables
    if(!dbFileExists){
        qDebug()<<"creating empty db tables";

        // attempt to open db connection
        if(openConnection()){
           prepareTables();
        }
    }else{
        qDebug()<<"db file exists";
    }
}

// access sql lite db file
void Database::createConnection(){
    _db = QSqlDatabase::addDatabase("QSQLITE");
    _db.setDatabaseName(_dbFileName);
}

// opens db connection
bool Database::openConnection(){
    if(!_db.open()){
        qDebug()<<"Database Error:"<<_db.lastError().text();
        return false;
    }
    qDebug()<<"database opened";
    return true;
}

QSqlQuery Database::execTransaction(QString sqls)
{
    _db.transaction();

    bool sql_ok = true;
    QSqlQuery q;
    QStringList sqlQueries = sqls.split(";", QString::SkipEmptyParts);

    for(int i = 0; i < sqlQueries.count() && sql_ok; i++){
        qDebug()<<"current query: "<<sqlQueries[i];
        sql_ok = q.exec(sqlQueries[i]);
    }
    //q.clear();
    if(sql_ok){
        sql_ok = _db.commit();
        qDebug()<<"commit Successful!";
    }
    if(!sql_ok){
        qDebug()<<"ERROR: "<< q.lastError().text();
        _db.rollback();
        // should throw error here
    }
    return q;
}

// close db connection
void Database::closeConnection(){
    qDebug()<<"database closed";
    _db.close();
}

void Database::prepareTables(){
    // enable pragma
    QString sql = "PRAGMA foreign_keys = 1; ";

    // user table
    sql += "CREATE TABLE IF NOT EXISTS users ("
                   "userID      INTEGER         NOT NULL    PRIMARY KEY AUTOINCREMENT, "
                   "username    VARCHAR(60)     NOT NULL, "
                   "password    VARCHAR(60)     NOT NULL, "
                   "dateCreated TEXT            DEFAULT CURRENT_TIMESTAMP , "
                   "dateRemoved TEXT            DEFAULT NULL, "
                   "isRemoved   INTEGER         DEFAULT 0); ";

    // score table
    sql +="CREATE TABLE IF NOT EXISTS scores ("
               "scoreID     INTEGER         NOT NULL PRIMARY KEY AUTOINCREMENT, "
               "userIDfk    INTEGER         NOT NULL, "
               "score       INTEGER         NOT NULL, "
               "dateCreated TEXT            DEFAULT CURRENT_TIMESTAMP, "
               "dateRemoved TEXT            DEFAULT NULL, "
               "isRemoved   INTEGER         DEFAULT 0, "
               "FOREIGN KEY(userIDfk) "
               "REFERENCES users(userID))";

    if(openConnection()){
        execTransaction(sql);
    }
}

// create sql lite empty db tables
QSqlQuery Database::execQuery(QString sql){
    qDebug()<<"query: "<<sql;

    bool sql_ok = true;

    QSqlQuery query;
    sql_ok = query.exec(sql);

    if(!sql_ok){
        qDebug()<<"ERROR: "<<query.lastError().text();
    }else{
        qDebug()<<"QUERY successful!";
    }
    return  query;
}
