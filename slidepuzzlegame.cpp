#include "slidepuzzlegame.h"

#include <QMouseEvent>

void SlidePuzzleGame::newGame(){

}

SlidePuzzleGame::SlidePuzzleGame(int size, int dim, int mar){
    this->_size = size;
    this->_dimension = dim;
    this->_margin = mar;

    _nbTiles = _size * _size - 1;
    _tiles = new int[size*size];

    _gridSize = (_dimension - 2 * _margin);
    _tileSize = _gridSize/_size;

    this->setMinimumSize(_dimension, _dimension + _margin);

    this->_gameOver = true;

    newGame();

}

void SlidePuzzleGame::mousePressEvent(QMouseEvent *e){
    if(_gameOver){
        newGame();
    } else {
        int ex = e->x();
        int ey = e->y();

        if(ex < 0 || ex > _gridSize || ey < 0 || ey > _gridSize){
            return;
        }

        int c1 = ex / _tileSize;
        int r1 = ey / _tileSize;

        // get position of the blank cell
        int c2 = _blankPos % _size;
        int r2 = _blankPos / _size;

        // we convert in the 1D cord
        int clickPos = r1 * _size + c1;

        int dir = 0;

        if(c1 == c2 && abs(r1 - r2) > 0){
            dir = (r1 - r2) > 0 ? _size : -_size;
        } else if (r1 == r2 && abs(c1 - c2) > 0){
            dir = (c1 - c2) > 0 ? 1 : -1;
        }

        if(dir != 0){
            do{
                int newBlankPos = _blankPos + dir;
                _tiles[_blankPos] = _tiles[newBlankPos];
                _blankPos = newBlankPos;
            }while(_blankPos != clickPos);

        _tiles[_blankPos] = 0;
        }

        // we check if game is solved
        _gameOver = isSolved();
    }

    // and repaint panel
    repaint();
}
