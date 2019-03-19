#ifndef PUZZLEELEMENTS_H
#define PUZZLEELEMENTS_H

#include <QVector>
#include <QImage>
#include <viewtype.h>

class PuzzleElements
{
public:
    PuzzleElements();
    ~PuzzleElements();

    QImage getElementImage(int elementPos);
    void setViewType(ViewType newViewType);


private:
    int n, m;
    ViewType viewType;
    QVector<QImage> outsourceImages;
    QVector<QImage> defaultImages;
};

#endif // PUZZLEELEMENTS_H
