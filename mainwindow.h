#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
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
    void startGame();
private slots:
    void columnClicked(int column);
    void newGameClk();
    void finished(Player* player);
    void undo();
    void redo();
    void on_btnLoad_clicked();
    void on_btnSave_clicked();
};

#endif // MAINWINDOW_H
