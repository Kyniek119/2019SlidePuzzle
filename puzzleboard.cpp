#include "puzzleboard.h"
#include <cstdlib>
#include <cstdio>
#include <QDebug>
#include <QString>
#include <time.h>

PuzzleBoard::PuzzleBoard(int n, int m){
    this->n = n;
    this->m = m;
    this->tiles = new int[n*m];
    this->blankPos = n*m-1;

    for(int i = 0; i < n*m; i++){
        tiles[i] = i+1;
    }
    srand (time(NULL));
}

void PuzzleBoard::moveIfPossible(int clickedTile){
    if(!isSolved()){
        move(getMoveAction(clickedTile));
    }
}

void PuzzleBoard::move(MoveAction moveAction){
    int tmp;
    switch(moveAction){
        case UP :
            tmp = tiles[blankPos];
            tiles[blankPos] = tiles[blankPos - n];
            tiles[blankPos - n] = tmp;
            blankPos = blankPos - n;
            break;
        case DOWN :
            tmp = tiles[blankPos];
            tiles[blankPos] = tiles[blankPos + n];
            tiles[blankPos + n] = tmp;
            blankPos = blankPos + n;
            break;
        case LEFT :
            tmp = tiles[blankPos];
            tiles[blankPos] = tiles[blankPos - 1];
            tiles[blankPos - 1] = tmp;
            blankPos = blankPos - 1;
            break;
        case RIGHT :
            tmp = tiles[blankPos];
            tiles[blankPos] = tiles[blankPos + 1];
            tiles[blankPos + 1] = tmp;
            blankPos = blankPos + 1;
            break;
        case BANNED:
            break;
    }
}

MoveAction PuzzleBoard::getMoveAction(int clickedTile){
    if(clickedTile == blankPos - n && clickedTile >= 0 && !gameOver){
        return UP;
    } else if(clickedTile == blankPos + n && clickedTile < n*m && !gameOver){
        return DOWN;
    } else if(clickedTile == blankPos - 1 && blankPos % n != 0 && !gameOver){
        return LEFT;
    } else if (clickedTile == blankPos + 1 && blankPos % n != n-1 && !gameOver){
        return RIGHT;
    } else {
        return BANNED;
    }
}

void PuzzleBoard::shuffle(){
    int tmp, newIndex, otherIndex;
    for (int i = 0; i < n*m-1; i++) {
        tmp = tiles[i];
        newIndex = rand() % (n*m-1);
        tiles[i] = tiles[newIndex];
        tiles[newIndex] = tmp;
    }

    while(!isSolvable()){
        newIndex = rand() % (n*m-1);
        tmp = tiles[newIndex];
        otherIndex = rand() % (n*m-1);
        tiles[newIndex] = tiles[otherIndex];
        tiles[otherIndex] = tmp;
    }
}

int *PuzzleBoard::getTiles(){
    return this->tiles;
}

int PuzzleBoard::getN(){
    return this->n;
}

int PuzzleBoard::getM(){
    return this->m;
}

int PuzzleBoard::getBlankPos(){
    return this->blankPos;
}

bool PuzzleBoard::isSolved(){
    if(blankPos != n*m-1){
        return false;
    }

    for (int i = 0; i < n*m; i++) {
        if(tiles[i] != i + 1){
            return false;
        }
    }
    return true;
}

void PuzzleBoard::printOnConsole(){
    qDebug() << "Board state:";
    for (int i = 0; i < n*m; i+=n) {
        QString *msg = new QString();
        for(int j = i; j < i+n; j++){
            msg->append(QString("%1 ").arg(tiles[j]));
        }
        qDebug("%s", qUtf8Printable(*msg));
    }
}

bool PuzzleBoard::isSolvable(){
    int count = 0;
    for(int i = 0; i < n*m-1; i++){
        if(tiles[i] < tiles[i+1]){
            count++;
        }
    }

    return count % 2 == n*m % 2;
}
