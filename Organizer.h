#include <QObject>
#include <QVector>
#include "Player.h"
#include <stack>

using namespace std;

class Organizer
{
private:
    Player *player1, *player2, *turn;
    char **grid = new char*[7];
    bool isWinning(int x, int y);
    void switchTurn();
    bool finished;

    stack<pair<int,int>> undo_stack;
    stack<pair<int,int>> redo_stack;

public:
    QVector<int> *plays;

    Organizer(Player *p1, Player *p2) {
        player1 = p1;
        player2 = p2;
    }
    ~Organizer() {
        delete player1;
        delete player2;
    }

    void init() {
        finished = false;
        plays = new QVector<int>();
        for(int i = 0; i<7; i++){
            grid[i] = new char[6];
            for(int j = 0; j<6; j++)
                grid[i][j] = '0';
        }
        turn = player1;
    }

    int play(int x);

    pair<int,int> undo();
    pair<int,int> redo();

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

    bool isFinished() const {
        return finished;
    }
};
