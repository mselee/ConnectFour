#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    helper = new gui(ui->graphicsView, 6, 7);
    helper->drawBlock(1, 1, QBrush(QColor(Qt::red)));
    helper->drawBlock(5, 0, QBrush(QColor(Qt::blue)));
    connect(helper, SIGNAL(columnClicked(int)), this, SLOT(columnClicked(int)));
}

void MainWindow::columnClicked(int column) {

}

MainWindow::~MainWindow()
{
    delete ui;
}
