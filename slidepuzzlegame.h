#ifndef SLIDEPUZZLEGAME_H
#define SLIDEPUZZLEGAME_H

#include <QWidget>

class SlidePuzzleGame : public QWidget
{

public:
    SlidePuzzleGame(int size, int dimension, int margin);

    void mousePressEvent(QMouseEvent *e);
private:
    int _size;
    int _dimension;
    int _margin;
    int _nbTiles;
    int* _tiles;

    int _gridSize;
    int _tileSize;
    int _blankPos;

    bool _gameOver;

    void newGame();
    bool isSolveable();
    bool isSolved();
};

#endif // SLIDEPUZZLEGAME_H
