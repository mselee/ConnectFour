#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    helper = new gui(ui->graphicsView, 6, 7);
    //helper->drawBlock(1, 1, QBrush(QColor(Qt::red)));
    //helper->drawBlock(5, 0, QBrush(QColor(Qt::blue)));
    connect(helper, SIGNAL(columnClicked(int)), this, SLOT(columnClicked(int)));

    p1 = new Player("Mo'men", 'r');
    p2 = new Player("Seleem", 'b');

    gameOrganizer = new Organizer(p1,p2);

}

void MainWindow::columnClicked(int column) {
    Player* turn = gameOrganizer->turnToPlay();
    int row = gameOrganizer->play(column);
    char color = turn->getcolour();

    if(color == 'r')
        helper->drawBlock(column, row, QBrush(QColor(Qt::red)));
    else if(color == 'b')
        helper->drawBlock(column, row, QBrush(QColor(Qt::blue)));

}

void MainWindow::undo(){
    pair<int,int> play = gameOrganizer->undo();
    //helper->clearBlock(play->first, play->second, QBrush(QColor(Qt::none)));
    Player* turn = gameOrganizer->turnToPlay();
    //do something with turn
}

void MainWindow::redo(){
    Player* color = gameOrganizer->turnToPlay()->getcolour();
    pair<int,int> play = gameOrganizer->redo();

    if(color == 'r')
        helper->drawBlock(play.first, play.second, QBrush(QColor(Qt::red)));
    else if(color == 'b')
        helper->drawBlock(play.first, play.second, QBrush(QColor(Qt::blue)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
