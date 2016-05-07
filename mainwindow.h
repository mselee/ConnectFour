#ifndef MAINWINDOW_H
#define MAINWINDOW_H

using namespace std;

#include <QMainWindow>
#include <string>
#include <iostream>
#include "gui.h"
#include "Organizer.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    gui* helper;
    Player *p1;
    Player *p2;
    Organizer *gameOrganizer;
    void undo();
    void redo();
private slots:
    void columnClicked(int column);
};

#endif // MAINWINDOW_H
