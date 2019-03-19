#ifndef PUZZLEBOARD_H
#define PUZZLEBOARD_H

#include <moveaction.h>
#include <puzzleelements.h>

class PuzzleBoard
{
public:
    PuzzleBoard(int n, int m);
    ~PuzzleBoard();

    void moveIfPossible(int clickedTile);

    void shuffle();
    int* getTiles();
    int getN();
    int getM();
    int getBlankPos();

    bool isSolved();


    void printOnConsole();

private:
    int n;
    int m;
    int blankPos;
    bool gameOver;
    int *tiles;

    bool isSolvable();
    void move(MoveAction moveAction);
    MoveAction getMoveAction(int clickedTile);
};

#endif // PUZZLEBOARD_H
