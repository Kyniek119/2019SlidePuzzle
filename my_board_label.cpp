#include "my_board_label.h"

my_board_label::my_board_label(QWidget *parent): QLabel(parent){
}

my_board_label::~my_board_label(){
    defaultImages.clear();
}

void my_board_label::mouseMoveEvent(QMouseEvent *ev){
    this->x = ev->x();
    this->y = ev->y();

    emit Mouse_Pos();
}

void my_board_label::mousePressEvent(QMouseEvent *ev){
    this->x = ev->x();
    this->y = ev->y();

    int n, m;
    n = x / tileWidth;
    m = y / tileHeight;

    int clickedPos = n + m*board->getN();
    if(clickedPos != lastClickedPos){
        qDebug() << QString("ClickedPosition: %1 \n").arg(clickedPos);
        board->moveIfPossible(clickedPos);
        board->printOnConsole();
        printBoard();
        lastClickedPos = clickedPos;

        emit Mouse_Pressed();
    }
}

void my_board_label::leaveEvent(QEvent *){
    emit Mouse_Left();
}

void my_board_label::printBoard(){
    int x, y, n, m, blankPos;
    int* tiles;

    n = board->getN();
    m = board->getM();

    blankPos = board->getBlankPos();
    tiles = board->getTiles();

    QPixmap *image = new QPixmap(QSize(n*tileWidth,m*tileHeight));
    QPainter *painter = new QPainter();
    painter->begin(image);
    QPen gap_pen;
    gap_pen.setColor(QColor(200,200,200));
    painter->setBackgroundMode(Qt::OpaqueMode);

    for ( int i = 0; i < n*m; i++){
        x = (i * tileWidth) % (n * tileWidth) ;
        y = (i * tileWidth) / (n * tileWidth) * tileHeight;
        //qDebug() << QString("TileWidth: %1, TileHeight: %2, on \"i\" element: %3, x: %4, y: %5").arg(tileWidth).arg(tileHeight).arg(i).arg(x).arg(y);

        painter->drawImage(QRect(x,y,tileWidth,tileHeight), defaultImages[tiles[i]-1]);
        //painter->drawLine(x,y,x+tileWidth,y);
        //painter->drawLine(x,y,x,y+tileHeight);

    }

    //painter->drawLine(0,m*tileHeight,n*tileWidth,m*tileHeight);
    //painter->drawLine(n*tileWidth,0,n*tileWidth,m*tileHeight);
    painter->end();
    this->setPixmap(*image);
    delete painter;
    emit Board_Changed();
}

void my_board_label::initializeBoard(PuzzleBoard *board){
    int n, m;
    n= board->getN();
    m = board->getM();

    this->tileWidth = this->width() / n;
    this->tileHeight = this->height() / m;

    this->board = board;
    defaultImages.clear();
    defaultImages.resize(tileWidth*tileHeight);

    for(int i = 0; i < n*m; i++){
        //qDebug() << "initializeBoard() " << i;
        QImage *image = new QImage(QSize(tileWidth,tileHeight),QImage::Format_RGB32);
        QPainter painter(image);
        painter.setBrush(QBrush(Qt::green));
        if(i == board->getBlankPos()){
            painter.fillRect(QRectF(0,0,tileWidth,tileHeight),Qt::black);
        } else {
            painter.fillRect(QRectF(0,0,tileWidth,tileHeight),Qt::darkGreen);
        }
        QFont font = painter.font();
        font.setPointSize(tileHeight/3);
        painter.setFont(font);
        painter.setPen(QPen(Qt::white));
        QString labelText = QString("%1").arg(i+1);
        drawText(painter,tileWidth/2, tileHeight/2, Qt::AlignHCenter | Qt::AlignVCenter, labelText );
        defaultImages[i] = *image;
    }

}

void my_board_label::drawText(QPainter & painter, qreal x, qreal y, Qt::Alignment flags,
              const QString & text, QRectF * boundingRect)
{
   const qreal size = 32767.0;
   QPointF corner(x, y - size);
   if (flags & Qt::AlignHCenter) corner.rx() -= size/2.0;
   else if (flags & Qt::AlignRight) corner.rx() -= size;
   if (flags & Qt::AlignVCenter) corner.ry() += size/2.0;
   else if (flags & Qt::AlignTop) corner.ry() += size;
   else flags |= Qt::AlignBottom;
   QRectF rect{corner.x(), corner.y(), size, size};
   painter.drawText(rect, flags, text, boundingRect);
}

void my_board_label::drawText(QPainter & painter, const QPointF & point, Qt::Alignment flags,
              const QString & text, QRectF * boundingRect)
{
   drawText(painter, point.x(), point.y(), flags, text, boundingRect);
}
