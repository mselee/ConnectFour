#include <QObject>
#include <QVector>
#include "Player.h"

class Organizer : public QObject
{
    Q_OBJECT
private:
    Player *player1, *player2, *turn;
    char **grid = new char*[7];
    bool isWinning(int x, int y);
    void switchTurn();
signals:
    void finished(Player *player);
public:
    QVector<int> *plays;

    Organizer(Player *p1, Player *p2) {
        player1 = p1;
        player2 = p2;
    }

    void init() {
        plays = new QVector<int>();
        for(int i = 0; i<7; i++){
            grid[i] = new char[6];
            for(int j = 0; j<6; j++)
                grid[i][j] = '0';
        }
        turn = player1;
    }

    int play(int x);

    void setPlayer1(Player *p){
        player1 = p;
    }

    void setPlayer2(Player *p){
        player2 = p;
    }

    Player* getPlayer1(){
        return player1;
    }

    Player* getPlayer2(){
        return player2;
    }

    Player* turnToPlay(){
        return turn;
    }

    char** getGrid(){
        return grid;
    }

    char getGrid(int x,int y){
        return grid[x][y];
    }
};
