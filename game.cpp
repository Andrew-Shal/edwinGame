#include "game.h"
#include <QTimer>
#include <QMediaPlayer>

#include <QHeaderView>

Game::Game(QWidget *)
{
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFixedSize(800,600);

    // create data access object
    DAO = new dao();

    _user = user_schema();
    _score = score_schema();

    playNowScene = nullptr;
    gamePlayScene = nullptr;
    highscoreScene = nullptr;
    loginScene = nullptr;
    createAccountScene = nullptr;

    buildLoginScene();

    show(); // show the view
}

// play now scene
void Game::buildPlayNowScene()
{
    // if not initialized
    if(playNowScene == nullptr){
        playNowScene = new QGraphicsScene();

        playNowScene->setSceneRect(0,0,800,600); // make the scene 800x600 instead of infinity by infinity (default)

        playNowBtn = new QPushButton();
        playNowBtn->setStyleSheet("QPushButton{background-color:black;color:white;}"
                                  "QPushButton:hover{background-color:white;color:black;}");
        playNowBtn->setGeometry(((800/2)-50),((600/2)-65),100,60);
        playNowBtn->setText("Play Now");
        playNowScene->addWidget(playNowBtn);

        optionsBtn = new QPushButton();
        optionsBtn->setStyleSheet("QPushButton{background-color:black;color:white;}"
                                     "QPushButton:hover{background-color:white;color:black;}");
        optionsBtn->setGeometry(((800/2)-50),((600/2)+60),100,60);
        optionsBtn->setText("Options");
        playNowScene->addWidget(optionsBtn);

        highScoresBtn = new QPushButton();
        highScoresBtn->setStyleSheet("QPushButton{background-color:black;color:white;}"
                                     "QPushButton:hover{background-color:white;color:black;}");
        highScoresBtn->setGeometry(((800/2)-50),((600/2)),100,60);
        highScoresBtn->setText("HighScores");
        playNowScene->addWidget(highScoresBtn);

        connect(playNowBtn,&QPushButton::clicked,this,&Game::onPlayButtonTriggered);
        connect(highScoresBtn,&QPushButton::clicked,this,&Game::onHighScoreBtnTriggered);
    }
    setBackgroundBrush(QBrush(QImage(":/images/images/playNow_Bg.png")));
    setScene(playNowScene);
}

void Game::buildLoginScene()
{
    loginScene = new QGraphicsScene();
    loginScene->setSceneRect(0,0,800,600);

    loginBtn = new QPushButton();
    loginBtn->setStyleSheet("QPushButton{background-color:black;color:white;}"
                              "QPushButton:hover{background-color:white;color:black;}");
    loginBtn->setGeometry(((800/2)-50),((600/2)-10),100,60);
    loginBtn->setText("login");
    loginBtn->setEnabled(false);
    loginScene->addWidget(loginBtn);

    login_usernameInput = new QLineEdit();
    login_usernameInput->setPlaceholderText("name");
    login_usernameInput->setGeometry(((800/2)-75),((600/2)-130),150,30);
    login_usernameInput->setStyleSheet("QLineEdit{color:#14890E;"
                                            "border-style:solid;"
                                            "border-width:3px;"
                                            "border-radius:10px;"
                                            "font-weight:bold;"
                                            "background-color:black;"
                                            "border-color:#14890E;}");
    loginScene->addWidget(login_usernameInput);

    signUpBtn = new QPushButton();
    signUpBtn->setStyleSheet("QPushButton{background-color:black;color:white;}"
                              "QPushButton:hover{background-color:white;color:black;}");
    signUpBtn->setGeometry(((800/2)+75+25),((600/2)-130),60,30);
    signUpBtn->setText("signup");
    loginScene->addWidget(signUpBtn);

    login_usernameInput = new QLineEdit();
    login_usernameInput->setPlaceholderText("name");
    login_usernameInput->setGeometry(((800/2)-75),((600/2)-130),150,30);
    login_usernameInput->setStyleSheet("QLineEdit{color:#14890E;"
                                            "border-style:solid;"
                                            "border-width:3px;"
                                            "border-radius:10px;"
                                            "font-weight:bold;"
                                            "background-color:black;"
                                            "border-color:#14890E;}");
    loginScene->addWidget(login_usernameInput);

    login_passwordInput = new QLineEdit();
    login_passwordInput->setPlaceholderText("password");
    login_passwordInput->setGeometry(((800/2)-75),((600/2)-65),150,30);
    login_passwordInput->setStyleSheet("QLineEdit{color:#14890E;"
                                            "border-style:solid;"
                                            "border-width:3px;"
                                            "border-radius:10px;"
                                            "font-weight:bold;"
                                            "background-color:black;"
                                            "border-color:#14890E;}");
    loginScene->addWidget(login_passwordInput);

    setBackgroundBrush(QBrush(QImage(":/images/images/playNow_Bg.png")));
    setScene(loginScene);

    connect(login_usernameInput,&QLineEdit::textChanged,this,&Game::enableLoginButton);
    connect(login_passwordInput,&QLineEdit::textChanged,this,&Game::enableLoginButton);
    connect(signUpBtn,&QPushButton::clicked,this,&Game::onSignupBtnTriggered);
    connect(loginBtn,&QPushButton::clicked,this,&Game::onLoginBtnTriggered);
}

void Game::enablePlayButton(QString text){
    playNowBtn->setEnabled(!text.isEmpty());
}

// game play scene
void Game::buildGamePlayScene()
{
    if(gamePlayScene != nullptr){
        delete gamePlayScene;
        gamePlayScene = nullptr;
    }

    gamePlayScene = new QGraphicsScene();

    setBackgroundBrush(QBrush(QImage(":/images/images/bg.png")));

    // visualize the newly initialized scene
    setScene(gamePlayScene); // since class Game inherits from class QGraphicsView, it can directly visualize a scene

    // create the player
    player = new Player();
    player->setPos(400,500); //generalize to always be in the middle bottom of screen

    // make the player focusable and set it to be the current focus
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();

    // add the player to the scene
    gamePlayScene->addItem(player);

    // create the score
    score = new Score();
    gamePlayScene->addItem(score);
    health = new Health();
    health->setPos(health->x(),health->y()+25);
    gamePlayScene->addItem(health);

    // spawn enemies
    QTimer * timer = new QTimer();
    QObject::connect(timer,SIGNAL(timeout()),player,SLOT(spawn()));
    timer->start(2000);

    //play background music
    QMediaPlayer *music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/sounds/bgsound.mp3"));
    music->play();
}
void Game::onPlayButtonTriggered(){
    buildGamePlayScene();
}

void Game::onHighScoreBtnTriggered(){
    buildHighScoresScene();
}

void Game::onLoginBtnTriggered()
{
    user_schema user = DAO->findUserbyNameandPwd(login_usernameInput->text(),login_passwordInput->text());
    if(user.userID() != -1){
        // found user
        _user = user;

        buildPlayNowScene();
        return;
    }
    //show message, user not found.
    login_usernameInput->setFocus();
    login_passwordInput->clear();
}

void Game::onSignupBtnTriggered()
{
    buildCreateAccountScene();
}

void Game::enableLoginButton(QString text)
{
    bool state = (!login_usernameInput->text().isEmpty() && !login_passwordInput->text().isEmpty());
    loginBtn->setEnabled(state);
}

void Game::onCreateAccountBtnTriggered()
{
    _user.userName(create_usernameInput->text());
    _user.password(create_passwordInput->text());
    int u_id = DAO->insertUser(_user);
    _user = DAO->getUser(u_id);

    buildLoginScene();
}

void Game::enableCreateAccountButton(QString text)
{
    bool state = (!create_usernameInput->text().isEmpty() && !create_passwordInput->text().isEmpty());
    createAccountBtn->setEnabled(state);
}

void Game::onClearBtnTriggered(){
    DAO->removeAllScores();
}
void Game::onGoBackBtnTriggered(){
    buildPlayNowScene();
}
void Game::buildCreateAccountScene(){
    createAccountScene = new QGraphicsScene();
    createAccountScene->setSceneRect(0,0,800,600);

    createAccountBtn = new QPushButton();
    createAccountBtn->setStyleSheet("QPushButton{background-color:black;color:white;}"
                              "QPushButton:hover{background-color:white;color:black;}");
    createAccountBtn->setGeometry(((800/2)-50),((600/2)+10),100,60);
    createAccountBtn->setText("signup");
    createAccountBtn->setEnabled(false);
    createAccountScene->addWidget(createAccountBtn);

    create_usernameInput = new QLineEdit();
    create_usernameInput->setPlaceholderText("name");
    create_usernameInput->setGeometry(((800/2)-75),((600/2)-130),150,30);
    create_usernameInput->setStyleSheet("QLineEdit{color:#14890E;"
                                            "border-style:solid;"
                                            "border-width:3px;"
                                            "border-radius:10px;"
                                            "font-weight:bold;"
                                            "background-color:black;"
                                            "border-color:#14890E;}");
    createAccountScene->addWidget(create_usernameInput);

    create_passwordInput = new QLineEdit();
    create_passwordInput->setPlaceholderText("name");
    create_passwordInput->setGeometry(((800/2)-75),((600/2)-65),150,30);
    create_passwordInput->setStyleSheet("QLineEdit{color:#14890E;"
                                            "border-style:solid;"
                                            "border-width:3px;"
                                            "border-radius:10px;"
                                            "font-weight:bold;"
                                            "background-color:black;"
                                            "border-color:#14890E;}");
    createAccountScene->addWidget(create_passwordInput);

    setBackgroundBrush(QBrush(QImage(":/images/images/playNow_Bg.png")));
    setScene(createAccountScene);

    connect(create_usernameInput,&QLineEdit::textChanged,this,&Game::enableCreateAccountButton);
    connect(create_passwordInput,&QLineEdit::textChanged,this,&Game::enableCreateAccountButton);
    connect(createAccountBtn,&QPushButton::clicked,this,&Game::onCreateAccountBtnTriggered);
}

void Game::buildHighScoresScene(){
//
    highscoreScene = new QGraphicsScene();

    setBackgroundBrush(QBrush(QImage(":/images/images/playNow_Bg.png")));

    // visualize the newly initialized scene
    setScene(highscoreScene); // since class Game inherits from class QGraphicsView, it can directly visualize a scene

    goBackButton = new QPushButton();
    goBackButton->setGeometry(500,10,100,30);
    //goBackButton->setIcon(QIcon(":/imgs/Asset 1.png"));
    //goBackButton->setIconSize(QSize(100,100));
    goBackButton->setText("go back");
    goBackButton->setToolTip("go back to main menu");
    goBackButton->setStyleSheet("QPushButton{background-color:black;color:white;}"
                              "QPushButton:hover{background-color:white;color:black;}");
    highscoreScene->addWidget(goBackButton);

    connect(goBackButton,&QPushButton::clicked,this,&Game::onGoBackBtnTriggered);

    clearMyScores = new QPushButton();
    clearMyScores->setGeometry(QRect(610,10,100,30));
    //clearMyScores->setIcon(QIcon(":/imgs/Asset 1.png"));
    //clearMyScores->setIconSize(QSize(100,100));
    clearMyScores->setText("clear my scores");
    clearMyScores->setToolTip("clear the high scores");
    clearMyScores->setStyleSheet("QPushButton{background-color:black;color:white;}"
                              "QPushButton:hover{background-color:white;color:black;}");
    highscoreScene->addWidget(clearMyScores);

    connect(clearMyScores,&QPushButton::clicked,this,&Game::onClearBtnTriggered);

    scoresTable = new QTableWidget();
    scoresTable->setRowCount(10);
    scoresTable->setColumnCount(3);
    QStringList tableHeader;
    tableHeader<<"Name"<<"Date"<<"Score";
    scoresTable->setHorizontalHeaderLabels(tableHeader);
    scoresTable->horizontalHeader()->setDefaultAlignment(Qt::AlignLeft);
    scoresTable->verticalHeader()->setVisible(false);
    scoresTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    scoresTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    scoresTable->setSelectionMode(QAbstractItemView::SingleSelection);
    scoresTable->setShowGrid(false);
    scoresTable->setStyleSheet("QTableView {selection-background-color: #444;}"
                               "QTableWidget {background-color: transparent;color:white;}"
                               "QHeaderView::section {background-color: transparent;color:white;}"
                               "QHeaderView {background-color: transparent;color:white;}"
                               "QTableCornerButton::section {background-color: transparent;}");
    scoresTable->setGeometry(50,50,700,500);
    scoresTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    //insert data
    QList<score_schema> * highScores =  DAO->getAllScores();

    QString name, date, u_score;
    int r = 0;
    for(score_schema s: *highScores){
        u_score = QString::number(s.score());
        date = s.dateCreated();
        name = s.getReferencedUser().userName();
        scoresTable->setItem(r, 0, new QTableWidgetItem(name));
        scoresTable->setItem(r, 1, new QTableWidgetItem(date));
        scoresTable->setItem(r, 2, new QTableWidgetItem(u_score));
        r++;
    }

    highscoreScene->addWidget(scoresTable);
}

void Game::dataAccessTesting(){
    user_schema u1 = user_schema();
    u1.userName("andrew");

    user_schema u2 = user_schema();
    u2.userName("anisha");

    user_schema u3 = user_schema();
    u3.userName("edwin");

    // insert 3 user
    DAO->insertUser(u1);
    DAO->insertUser(u2);
    DAO->insertUser(u3);

    // get user 1
    user_schema u1_ret = DAO->getUser(1);

    // get user 2
    user_schema u2_ret = DAO->getUser(2);

    // get user 3
    user_schema u3_ret = DAO->getUser(3);

    // set score for user 1
    score_schema u1_score = score_schema();
    score_schema u1_score2 = score_schema();
    score_schema u1_score3 = score_schema();
    u1_score.userRefID(u1_ret.userID());
    u1_score2.userRefID(u1_ret.userID());
    u1_score3.userRefID(u1_ret.userID());
    u1_score.score(600);
    u1_score2.score(10);
    u1_score3.score(300);

    // set scores from user 2
    score_schema u2_score = score_schema();
    score_schema u2_score2 = score_schema();
    score_schema u2_score3 = score_schema();
    score_schema u2_score4 = score_schema();
    score_schema u2_score5 = score_schema();
    u2_score.userRefID(u2_ret.userID());
    u2_score2.userRefID(u2_ret.userID());
    u2_score3.userRefID(u2_ret.userID());
    u2_score4.userRefID(u2_ret.userID());
    u2_score5.userRefID(u2_ret.userID());
    u2_score.score(600);
    u2_score2.score(10);
    u2_score3.score(300);
    u2_score4.score(400);
    u2_score5.score(700);

    // insert user 1 scores
    DAO->insertUserScore(u1_score);
    DAO->insertUserScore(u1_score2);
    DAO->insertUserScore(u1_score3);

    // insert user 2 scores
    DAO->insertUserScore(u2_score);
    DAO->insertUserScore(u2_score2);
    DAO->insertUserScore(u2_score3);
    DAO->insertUserScore(u2_score4);
    DAO->insertUserScore(u2_score5);

    // get all users
    QList<user_schema> * AllUsers = DAO->getAllUsers();

    // get all user scores
    QList<score_schema> * AllScores = DAO->getAllScores();

    qDebug()<<"all users: "<<*AllUsers;
    qDebug()<<"user 1: "<<u1_ret;
    qDebug()<<"user 2: "<<u2_ret;
    qDebug()<<"user 3: "<<u3_ret;
    qDebug()<<"all scores:"<<*AllScores;

    qDebug()<<"user 1 scores: "<<*DAO->getScoresBelongingTo(u1_ret.userID());

    qDebug()<<"user 2 scores: "<<*DAO->getScoresBelongingTo(u2_ret.userID());

    qDebug()<<"user 3 scores: "<<*DAO->getScoresBelongingTo(u3_ret.userID());


    DAO->removeUser(3); // removes edwin from users
    qDebug()<<"updated users: "<<*DAO->getAllUsers();

    DAO->removeScore(1);    // remove score at index 1

    qDebug()<<"all scores after removal of 1:"<<*AllScores;

    qDebug()<<"top 5 scores: "<<*DAO->getTopScores(5);

    qDebug()<<"top 3 scores for user 2 descending order: "<<*DAO->getTopScoresBelongingTo(2,3);
    qDebug()<<"top 3 scores for user 2 ascending order: "<<*DAO->getTopScoresBelongingTo(2,3,"ASC");

    DAO->removeAllUsers();  // will removes scores, since score belongs to user

    qDebug()<<"user table after all records removed"<< *DAO->getAllUsers();
    qDebug()<<"scores table after all records removed"<< *DAO->getAllScores();
}

void Game::closeEvent(QCloseEvent *e){
    qDebug()<<"user: "<<_user;
    // score belonging to a user
    if(_user.userID() != -1){
        _score.userRefID(_user.userID());
        _score.score(score->getScore());
        DAO->insertUserScore(_score);
    }

    e->accept();
}





