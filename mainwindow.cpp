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
    QDir().mkpath("games");
    gameOrganizer = nullptr;
}

void MainWindow::updateTurn() {
    ui->lbl_current_player->setText("Current Turn: " + gameOrganizer->turnToPlay()->getname());
}

void MainWindow::newGameClk() {
    ui->P1Name->setEnabled(false);
    ui->P2Name->setEnabled(false);

    p1 = new Player(ui->P1Name->text(), 'r');
    p2 = new Player(ui->P2Name->text(), 'b');

    ui->Score1->setText("0");
    ui->Score2->setText("0");

    gameOrganizer = new Organizer(p1,p2);

    startGame();
}

void MainWindow::startGame() {
    helper->drawGrid();
    gameOrganizer->init();
    updateTurn();
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
//       newGameClk();
       ui->P1Name->setEnabled(true);
       ui->P2Name->setEnabled(true);
    }
}


void MainWindow::columnClicked(int column) {
    Player* turn = gameOrganizer->turnToPlay();
    int row = gameOrganizer->play(column);
    char color = turn->getcolour();

    if(color == 'r')
        helper->drawBlock(column, row, QBrush(QColor(Qt::red)));
    else if(color == 'b')
        helper->drawBlock(column, row, QBrush(QColor(Qt::blue)));
    ui->btnUndo->setProperty("enabled", true);
    ui->btnRedo->setProperty("enabled", false);
    updateTurn();
    if (gameOrganizer->isFinished()) finished(gameOrganizer->turnToPlay());
}

void MainWindow::undo(){
    pair<int,int> play = gameOrganizer->undo();
    if(play.first != -1 && play.second != -1){
        helper->drawBlock(play.first, play.second, QBrush(QColor(Qt::white)));
        ui->btnRedo->setProperty("enabled", true);
        ui->btnUndo->setProperty("enabled", false);
    }

   updateTurn();

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
    updateTurn();
}

void MainWindow::on_btnSave_clicked()
{
    QString timestamp = QDateTime().currentDateTime().toString();
    QString filename = gameOrganizer->getPlayer1()->getname() + " vs " + gameOrganizer->getPlayer2()->getname() + " [" + timestamp + "]";
    QFile game("games/" + filename + ".txt");
    if (game.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text))
    {
        QTextStream stream(&game);
        stream << gameOrganizer->getPlayer1()->getname() << endl;
        stream << gameOrganizer->getPlayer1()->getscore() << endl;
        stream << gameOrganizer->getPlayer2()->getname() << endl;
        stream << gameOrganizer->getPlayer2()->getscore() << endl;
        for (int i = 0; i < gameOrganizer->plays->count(); ++i) {
            stream << gameOrganizer->plays->at(i) << endl;
        }
        game.close();
    }
}

void MainWindow::on_btnLoad_clicked()
{
    LoadDialog* dialog = new LoadDialog(this);
    if (dialog->exec() == QDialog::Accepted) {
        Player *p1, *p2;

        ui->P1Name->setEnabled(false);
        ui->P2Name->setEnabled(false);

        QFile game("games/" + dialog->filename);
        if (game.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&game);
            QString name = stream.readLine();
            int score = stream.readLine().toInt();
            p1 = new Player(name, 'r');
            p1->setscore(score);
            ui->P1Name->setText(name);
            ui->Score1->setText(QString::number(score));

            name = stream.readLine();
            score = stream.readLine().toInt();
            p2 = new Player(name, 'b');
            p2->setscore(score);
            ui->P2Name->setText(name);
            ui->Score2->setText(QString::number(score));

            gameOrganizer = new Organizer(p1,p2);

            startGame();

            while (!stream.atEnd())
            {
               int x = stream.readLine().toInt();
               columnClicked(x);
            }

            game.close();
        }
    }
    delete dialog;


}

MainWindow::~MainWindow()
{
    delete ui;
    delete helper;
    if (gameOrganizer != nullptr)
        delete gameOrganizer;
}
