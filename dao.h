#ifndef DAO_H
#define DAO_H

#include "database.h"
#include "user_schema.h"
#include "score_schema.h"

class dao
{
public:
    dao();    
    // you could separate this into two classes,
    // one for user dao and another for score
    // then you could create a unit of work class
    // that gives access to dao methods.
    // in that case, you wouldn't execute the query in each of these methods
    // but just save a sql string and whenever you are ready to execute the query
    // call an executeWorkItem method in the unit of work class which runs the db->exec for the
    // respective dao. This way, you'll abstract the user_schema and score schema therefore game class
    // will only know unit of work.

    // TODO: check on the return types for the methods, not sure if you should return pointers of obj
    // once that's fixed, you might have to modify the params on operator override debug<< in schema classes

    int insertUser(user_schema user);
    user_schema getUser(int userID);
    QList<user_schema> * getAllUsers();
    void removeUser(int u_id);
    void removeAllUsers();
    user_schema findUserbyNameandPwd(QString u_name,QString pwd);

    void insertUserScore(score_schema u_score);
    QList<score_schema> * getAllScores(QString sortBy = "DESC");
    QList<score_schema> * getScoresBelongingTo(int u_id);
    QList<score_schema> * getTopScoresBelongingTo(int u_id, int limit, QString sortBy = "DESC");
    QList<score_schema> * getTopScores(int limit, QString sortBy = "DESC");
    void removeScore(int s_id);
    void removeAllScores();
    void removeAllScoresBelongingTo(int u_id);

    score_schema getTopScore();

private:
    Database * _db;
};

#endif // DAO_H
