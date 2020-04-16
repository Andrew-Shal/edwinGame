  #ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QWidget>
#include <QGraphicsScene>
#include "player.h"
#include "score.h"
#include "health.h"

#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QLabel>

#include "dao.h"
#include "user_schema.h"

class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(QWidget *parent = 0);
    QGraphicsScene *gamePlayScene;
    QGraphicsScene *playNowScene;
    QGraphicsScene *highscoreScene;
    QGraphicsScene *createAccountScene;
    QGraphicsScene *loginScene;
    QGraphicsScene *gameOverScene;

    QGraphicsTextItem *Level = nullptr;

    void buildPlayNowScene();
    void buildLoginScene();
    void buildGamePlayScene();
    void buildHighScoresScene();
    void buildCreateAccountScene();
    void buildGameOverScene();
    void dataAccessTesting();

    bool gameStarted = false;
    int levels = 1;

    //playnow scene actions
    void enablePlayButton(QString text);
    void onPlayButtonTriggered();

    // highscores scene actions
    void onGoBackBtnTriggered();
    void onClearBtnTriggered();
    void onHighScoreBtnTriggered();
    void populateScoresTable();

    // game over scene actions
    void onPlayAgainBtnTriggered();
    void onMainMenuBtnTriggered();

    // login scene actions
    void onLoginBtnTriggered();
    void onSignupBtnTriggered();
    void enableLoginButton(QString text);

    // create account scene actions
    void onCreateAccountBtnTriggered();
    void enableCreateAccountButton(QString text);

    void saveUserScore();

    Player *player;
    Score *score;
    Health *health;
public slots:
    void increaseLevel();
    void playerHasDied();

protected:
    void closeEvent(QCloseEvent *e);
private:

    // create account scene controls
    QPushButton *createAccountBtn;
    QLineEdit *create_usernameInput;
    QLineEdit *create_passwordInput;

    // game over scene
    QPushButton *playAgainBtn;
    QPushButton *mainMenuBtn;
    QGraphicsTextItem *gameOverText;

    // login scene controls
    QPushButton *loginBtn;
    QPushButton *signUpBtn;
    QLineEdit *login_usernameInput;
    QLineEdit *login_passwordInput;

    //playnow scene controls
    QPushButton *playNowBtn;
    QPushButton *highScoresBtn;
    QPushButton *optionsBtn;

    // highscores scene controls
    QPushButton *goBackButton;
    QPushButton *clearMyScores;
    QPushButton *clearAllScores;

    // can change these buttons to a dropdown
    QPushButton *viewAllScores;
    QPushButton *viewMyScores;
    QPushButton *viewTopScores;

    QTableWidget *scoresTable;

    dao * DAO;
    user_schema _user;
    score_schema _score;
};

#endif // GAME_H
