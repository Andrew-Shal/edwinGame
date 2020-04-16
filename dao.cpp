#include "dao.h"

dao::dao()
{
    QString dbName = "spaceInvaderDb.dat";
   _db = new Database(dbName);
}

int dao::insertUser(user_schema user)
{
    int retVal = -1;
    if(_db->openConnection()){
        QSqlQuery query =_db->execTransaction("INSERT INTO users (username, password) VALUES ('"+ user.userName() +"', '"+user.password()+"'); SELECT last_insert_rowid()");
        // Q = _db->execQuery("SELECT userID FROM users ORDER BY userID DESC LIMIT 1").value(0).toInt();
        while(query.next()){
            retVal = query.value(0).toInt();
        }
    }
    return retVal;
}

user_schema dao::getUser(int userID)
{
    QString sql = "SELECT userID, username, dateCreated, dateRemoved, isRemoved FROM users WHERE userID = '" + QString::number(userID) + "' AND isRemoved != '1'";
    user_schema user = user_schema();

    if(_db->openConnection()){
        QSqlQuery query = _db->execQuery(sql);

        while(query.next()){
            user.userID(query.value(0).toInt());
            user.userName(query.value(1).toString());
            user.dateCreated(query.value(2).toString());
            user.dateRemoved(query.value(3).toString());
            user.isRemoved(query.value(4).toInt());
            qDebug()<<"curr user: "<<user;
        }
    }
    return user;
}

QList<user_schema> * dao::getAllUsers()
{
    QString sql = "SELECT userID, username, dateCreated, dateRemoved, isRemoved FROM users WHERE isRemoved != '1'";
    QList<user_schema> * users = new QList<user_schema>();

    if(_db->openConnection()){
        QSqlQuery query = _db->execQuery(sql);

        while(query.next()){
            user_schema user = user_schema();
            user.userID(query.value(0).toInt());
            user.userName(query.value(1).toString());
            user.dateCreated(query.value(2).toString());
            user.dateRemoved(query.value(3).toString());
            user.isRemoved(query.value(4).toInt());
            users->push_back(user);
            qDebug()<<"curr user: "<<user;
        }
    }
    return users;
}

void dao::removeUser(int u_id)
{
    QString sql = "UPDATE users SET isRemoved = '1', dateRemoved = CURRENT_TIMESTAMP WHERE userID = '"+QString::number(u_id)+"'; ";

    sql += "UPDATE scores SET isRemoved = '1', dateRemoved = CURRENT_TIMESTAMP WHERE userIDfk = '"+QString::number(u_id)+"'";

    if(_db->openConnection()){
        _db->execTransaction(sql);
    }
}

score_schema dao::getTopScore(){
    QString sql = "SELECT TOP 1 scoreID, userIDfk, score, dateCreated, dateRemoved, isRemoved FROM scores ORDER BY scores DESC";
    score_schema topScore = score_schema();
    if(_db->openConnection()){
        QSqlQuery query =_db->execQuery(sql);
        while(query.next()){
            topScore.scoreID(query.value(0).toInt());
            topScore.userRefID(query.value(0).toInt());
            topScore.score(query.value(0).toInt());
            topScore.dateCreated(query.value(0).toString());
            topScore.dateRemoved(query.value(0).toString());
            topScore.isRemoved(query.value(0).toInt());
        }
    }
    return topScore;
}

void dao::removeAllUsers()  // removes all scores and user records in tables
{
    QString sql = "DELETE FROM scores; DELETE FROM users";

    if(_db->openConnection()){
        _db->execTransaction(sql);
    }
}

user_schema dao::findUserbyNameandPwd(QString u_name, QString pwd)
{
     QString sql = "SELECT userID, username FROM users WHERE username = '"+u_name+"' AND password = '"+pwd+"' AND isRemoved != 1";
     user_schema user =  user_schema();

     if(_db->openConnection()){
         QSqlQuery query = _db->execQuery(sql);
         while(query.next()){
             user.userID(query.value(0).toInt());
             user.userName(query.value(1).toString());
         }
     }
     return user;
}

void dao::insertUserScore(score_schema u_score)
{
    QString sql = "INSERT INTO scores (userIDfk, score) "
                  "SELECT '"+QString::number(u_score.userRefID())+"', '"+QString::number(u_score.score())+"' "
                  "WHERE NOT EXISTS(SELECT 1 FROM scores WHERE userIDfk = '"+QString::number(u_score.userRefID())+"' AND score = '"+QString::number(u_score.score())+"')";

    if(_db->openConnection()){
        _db->execTransaction(sql);
    }
}

QList<score_schema> * dao::getAllScores(QString sortBy){
    QString sql = "SELECT scores.scoreID, scores.userIDfk, scores.score, scores.dateCreated, scores.dateRemoved, scores.isRemoved, users.userID, users.username, users.dateCreated, users.dateRemoved, users.isRemoved FROM scores INNER JOIN users ON scores.userIDfk = users.userID AND users.isRemoved != '1' AND scores.isRemoved != '1' ORDER BY scores.score "+ sortBy +"";
    QList<score_schema> * u_scores = new QList<score_schema>();

    if(_db->openConnection()){
        QSqlQuery query = _db->execQuery(sql);
        while(query.next()){
            score_schema u_score = score_schema();
            u_score.scoreID(query.value(0).toInt());
            u_score.userRefID(query.value(1).toInt());
            u_score.score(query.value(2).toInt());

            u_score.dateCreated(query.value(3).toString());
            u_score.dateRemoved(query.value(4).toString());
            u_score.isRemoved(query.value(5).toInt());

            user_schema refUser = u_score.getReferencedUser();
            refUser.userID(query.value(6).toInt());
            refUser.userName(query.value(7).toString());

            refUser.dateCreated(query.value(8).toString());
            refUser.dateRemoved(query.value(9).toString());
            refUser.isRemoved(query.value(10).toInt());

            u_score.setReferencedUser(refUser);
            qDebug()<<"curr score: "<<u_score;
            u_scores->push_back(u_score);
        }
    }
    return u_scores;
}

QList<score_schema> * dao::getScoresBelongingTo(int u_id){
    QString sql = "SELECT scoreID, userIDfk, score, dateCreated, dateRemoved, isRemoved FROM scores WHERE userIDfk = '"+QString::number(u_id)+"' AND isRemoved != '1'";
    QList<score_schema> * u_scores = new QList<score_schema>();

    if(_db->openConnection()){
        QSqlQuery query = _db->execQuery(sql);
        while(query.next()){
            score_schema u_score = score_schema();
            u_score.scoreID(query.value(0).toInt());
            u_score.userRefID(query.value(1).toInt());
            u_score.score(query.value(2).toInt());

            u_score.dateCreated(query.value(3).toString());
            u_score.dateRemoved(query.value(4).toString());
            u_score.isRemoved(query.value(5).toInt());
            qDebug()<<"curr score: "<<u_score;
            u_scores->push_back(u_score);
        }
    }
    return u_scores;
}

QList<score_schema> *dao::getTopScoresBelongingTo(int u_id, int limit, QString sortBy)  // might have to change sortBy since we are relying on a string(not the best way to handle this).
{
    QString sql = "SELECT scoreID, userIDfk, score, dateCreated, dateRemoved, isRemoved FROM scores WHERE isRemoved != '1' AND userIDfk = '"+QString::number(u_id)+"' ORDER BY score DESC LIMIT "+QString::number(limit)+"";
    QList<score_schema> * u_scores = new QList<score_schema>();

    if(_db->openConnection()){
        QSqlQuery query = _db->execQuery(sql);
        while(query.next()){
            score_schema u_score = score_schema();
            u_score.scoreID(query.value(0).toInt());
            u_score.userRefID(query.value(1).toInt());
            u_score.score(query.value(2).toInt());

            u_score.dateCreated(query.value(3).toString());
            u_score.dateRemoved(query.value(4).toString());
            u_score.isRemoved(query.value(5).toInt());
            qDebug()<<"curr score: "<<u_score;

            // not the best way to handle, since we cant gurantee sring is "desc" or "asc"
            if(sortBy == "DESC"){
                u_scores->push_back(u_score);
            }else if(sortBy == "ASC"){
                u_scores->push_front(u_score);
            }

        }
    }
    return u_scores;
}

QList<score_schema> *dao::getTopScores(int limit, QString sortBy)
{
    QString sql = "SELECT scoreID, userIDfk, score, dateCreated, dateRemoved, isRemoved FROM scores WHERE isRemoved != '1' ORDER BY score DESC LIMIT "+QString::number(limit)+"";
    QList<score_schema> * u_scores = new QList<score_schema>();

    if(_db->openConnection()){
        QSqlQuery query = _db->execQuery(sql);
        while(query.next()){
            score_schema u_score = score_schema();
            u_score.scoreID(query.value(0).toInt());
            u_score.userRefID(query.value(1).toInt());
            u_score.score(query.value(2).toInt());

            u_score.dateCreated(query.value(3).toString());
            u_score.dateRemoved(query.value(4).toString());
            u_score.isRemoved(query.value(5).toInt());
            qDebug()<<"curr score: "<<u_score;

            // not the best way to handle, since we cant gurantee sring is "desc" or "asc"
            if(sortBy == "DESC"){
                u_scores->push_back(u_score);
            }else if(sortBy == "ASC"){
                u_scores->push_front(u_score);
            }
        }
    }
    return u_scores;
}

void dao::removeScore(int s_id)
{
    QString sql = "UPDATE scores SET isRemoved = '1', dateRemoved = CURRENT_TIMESTAMP WHERE scoreID = '"+QString::number(s_id)+"'";

    if(_db->openConnection()){
        _db->execQuery(sql);
    }
}

void dao::removeAllScores() // this clears the table, you could always just set isremoved to true on all current records
{
    QString sql = "DELETE FROM scores";

    if(_db->openConnection()){
        _db->execQuery(sql);
    }
}

void dao::removeAllScoresBelongingTo(int u_id)
{
    QString sql = "UPDATE scores SET isRemoved = '1', dateRemoved = CURRENT_TIMESTAMP WHERE userIDfk = '"+QString::number(u_id)+"'";

    if(_db->openConnection()){
        _db->execQuery(sql);
    }
}


