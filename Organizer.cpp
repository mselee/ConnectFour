#include "Organizer.h"
#include <iostream>
#include <QDebug>

int Organizer::play(int x)  {
    int y;

    for(int i=0;i<6;i++){
        if(grid[x][i] == '0') {
            y = i;
            break;
        }
    }

    grid[x][y] = turn->getcolour();
    if(isWinning(x,y))
        qDebug() <<QString::fromStdString(turn->getname()) << QString("WON");//win the game
    //else
        switchTurn();

    undo_stack.push((x,y));
    while(!redo_stack.empty())
        redo_stack.pop();
    return y;
}

pair<int,int> Organizer::undo(){
    switchTurn();
    if(undo_stack.empty())
        return false;
    pair<int,int> play = undo_stack.pop();
    grid[play.first][play.second] = '0';
    redo_stack.push(play);
    return play;
}

pair<int,int> Organizer::redo() {
    if(redo_stack.empty())
        return false;
    pair<int,int> play = redo_stack.pop();
    grid[play.first][play.second] = turnToPlay()->getcolour();
    undo_stack.push(play);
    switchTurn();
    return play;
}

bool Organizer::isWinning(int x, int y) {
    char color = grid[x][y];

    //check horizontal axis     (WORKING)
    int count = 0;
    for(int i = 0; i < 7; i++) {
        if(grid[i][y] == color) {
            count++;
            if (count > 3)
                return true;
        }
        else
            count = 0;
    }

    //check vertically      (WORKING)
    count = 0;
    for(int i = y; i >= 0; i--) {
        if(grid[x][i] == color) {
            count++;
            if (count > 3)
                return true;
        }
        else
            count = 0;
    }

    //check lower upward diagonal   (WORKING)
    if(x > y) {
        count = 0;
        int j = 0;
        for(int i = x - y; i < 7; i++) {
            if(grid[i][j] == color) {
                count++;
                if (count > 3)
                    return true;
            }
            else
                count = 0;
            j++;
        }
    }

    //check upper upward diagonal
    else {
        count = 0;
        int i = 0;
        for(int j = y - x; j < 6; j++) {
            if(grid[i][j] == color) {
                count++;
                if (count > 3)
                    return true;
            }
            else
                count = 0;
            i++;
        }
    }

    //check lower downward diagonal     (WORKING)
    if(x+y < 6) {
        count = 0;
        int i = 0;
        for(int j = x+y; j >= 0; j--) {
            if(grid[i][j] == color) {
                count++;
                if (count > 3)
                    return true;
            }
            else
                count = 0;
            i++;
        }
    }

    //check upper downward diagonal     (WORKING)
    else {
        count = 0;
        int i = x - (5-y);
        for(int j = 5; j >= (x+y) - 6; j--) {
            if(grid[i][j] == color) {
                count++;
                if (count > 3)
                    return true;
            }
            else
                count = 0;
            i++;
        }
    }
    return false;
}

void Organizer::switchTurn() {
    if(turn == player1)
        turn = player2;
    else
        turn = player1;
}
