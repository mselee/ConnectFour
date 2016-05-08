#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    helper = new gui(ui->graphicsView, 6, 7);
    connect(helper, SIGNAL(columnClicked(int)), this, SLOT(columnClicked(int)));
    connect(ui->btnNew, SIGNAL(clicked(bool)),this, SLOT(newGameClk()));
    connect(ui->btnUndo, SIGNAL(clicked(bool)),this, SLOT(undo()));
    connect(ui->btnRedo, SIGNAL(clicked(bool)),this, SLOT(redo()));
}

void MainWindow::newGameClk() {
    ui->P1Name->setEnabled(false);
    ui->P2Name->setEnabled(false);

    p1 = new Player(ui->P1Name->text(), 'r');
    p2 = new Player(ui->P2Name->text(), 'b');

    gameOrganizer = new Organizer(p1,p2);
    connect(gameOrganizer, SIGNAL(finished(Player*)), this, SLOT(finished(Player*)));

    startGame();
}

void MainWindow::startGame() {
    helper->drawGrid();
    gameOrganizer->init();
}

void MainWindow::finished(Player *player) {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Game Finished!", player->getname() + " has won. Replay ?", QMessageBox::Yes | QMessageBox::No);
    if (reply == QMessageBox::Yes) {
        if(player->getcolour()=='r')
            ui->Score1->setText(QString::number(player->getscore()));
        else
            ui->Score2->setText(QString::number(player->getscore()));
        startGame();
    }
    else {
       newGameClk();
       ui->P1Name->setEnabled(true);
       ui->P2Name->setEnabled(true);
    }
}


void MainWindow::columnClicked(int column) {
    Player* turn = gameOrganizer->turnToPlay();
    int row = gameOrganizer->play(column);
    if (row == -1) return;
    char color = turn->getcolour();

    if(color == 'r')
        helper->drawBlock(column, row, QBrush(QColor(Qt::red)));
    else if(color == 'b')
        helper->drawBlock(column, row, QBrush(QColor(Qt::blue)));
    ui->btnUndo->setProperty("enabled", true);
    ui->btnRedo->setProperty("enabled", false);

}

void MainWindow::undo(){
    pair<int,int> play = gameOrganizer->undo();
    if(play.first != -1 && play.second != -1){
        helper->drawBlock(play.first, play.second, QBrush(QColor(Qt::white)));
        ui->btnRedo->setProperty("enabled", true);
        ui->btnUndo->setProperty("enabled", false);
    }

   // Player* turn = gameOrganizer->turnToPlay();
    //do something with turn
}

void MainWindow::redo(){
    char color = gameOrganizer->turnToPlay()->getcolour();
    pair<int,int> play = gameOrganizer->redo();
    if(play.first != -1 && play.second != -1) {
        if(color == 'r')
            helper->drawBlock(play.first, play.second, QBrush(QColor(Qt::red)));
        else if(color == 'b')
            helper->drawBlock(play.first, play.second, QBrush(QColor(Qt::blue)));
        ui->btnUndo->setProperty("enabled", true);
        ui->btnRedo->setProperty("enabled", false);
    }
}

void MainWindow::on_btnSave_clicked()
{
    QFile game("game.txt");
    if (game.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream stream(&game);
        for (int i = 0; i < gameOrganizer->plays->count(); ++i) {
            stream << gameOrganizer->plays->at(i) << endl;
        }
        game.close();
    }

    QFile player1("player1.txt");
    if (player1.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream stream(&player1);
        stream << gameOrganizer->getPlayer1()->getname() << endl;
        stream << gameOrganizer->getPlayer1()->getscore() << endl;
        player1.close();
    }

    QFile player2("player2.txt");
    if (player2.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream stream(&player2);
        stream << gameOrganizer->getPlayer2()->getname() << endl;
        stream << gameOrganizer->getPlayer2()->getscore() << endl;
        player2.close();
    }
}

void MainWindow::on_btnLoad_clicked()
{
    Player *p1, *p2;

    ui->P1Name->setEnabled(false);
    ui->P2Name->setEnabled(false);

    QFile player1("player1.txt");
    if (player1.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&player1);
        QString name = stream.readLine();
        int score = stream.readLine().toInt();
        p1 = new Player(name, 'r');
        p1->setscore(score);
        ui->P1Name->setText(name);
        ui->Score1->setText(QString::number(score));
        player1.close();
    }

    QFile player2("player2.txt");
    if (player2.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&player2);
        QString name = stream.readLine();
        int score = stream.readLine().toInt();
        p2 = new Player(name, 'b');
        p2->setscore(score);
        ui->P2Name->setText(name);
        ui->Score2->setText(QString::number(score));
        player2.close();
    }

    gameOrganizer = new Organizer(p1,p2);
    connect(gameOrganizer, SIGNAL(finished(Player*)), this, SLOT(finished(Player*)));
    startGame();

    QFile inputFile("game.txt");
    if (inputFile.open(QIODevice::ReadOnly))
    {
       QTextStream in(&inputFile);
       while (!in.atEnd())
       {
          QString line = in.readLine();
          int x = line.toInt();
          columnClicked(x);

       }
       inputFile.close();
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
