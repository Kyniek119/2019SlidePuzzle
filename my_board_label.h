#ifndef MY_QLABEL_H
#define MY_QLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <QEvent>
#include <QDebug>
#include <QPainter>
#include <QVector>
#include "puzzleboard.h"

class my_board_label : public QLabel
{
    Q_OBJECT
public:
    explicit my_board_label(QWidget *parent = 0);
    ~my_board_label();

    void mouseMoveEvent(QMouseEvent *ev);
    void mousePressEvent(QMouseEvent *ev);
    void leaveEvent(QEvent *);

    void printBoard();
    void initializeBoard(PuzzleBoard *board);
    int getMoveCount();

    int x,y;

signals:
    void Mouse_Pressed();
    void Mouse_Pos();
    void Mouse_Left();
    void Board_Changed();

private:
    PuzzleBoard *board;

    int tileWidth;
    int tileHeight;
    int lastClickedPos = 0;
    int moveCount = 0;
    QVector<QImage> defaultImagePieces;

    void resetMoveCount();
    void incrementMoveCount();
    void drawText(QPainter & painter, const QPointF & point, Qt::Alignment flags,
                       const QString & text, QRectF * boundingRect = {});
    void drawText(QPainter & painter, qreal x, qreal y, Qt::Alignment flags,
                  const QString & text, QRectF * boundingRect = 0);

public slots:

};

#endif // MY_QLABEL_H
