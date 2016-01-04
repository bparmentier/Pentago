#include "rotationarrow.h"
#include <QApplication>

RotationArrow::RotationArrow(int aMiniBoard, Direction aDirection):
    miniboard{aMiniBoard},dir{aDirection}
{
    switch(dir){
    case Direction::CLOCKWISE:
        pixmap = new QPixmap(":/ressources/ArrowRight.png");
        break;
    case Direction::COUNTERCLOCKWISE:
        pixmap = new QPixmap(":/ressources/ArrowLeft.png");
        break;
    }
    QPixmap newPixmap = pixmap->scaled(QSize(30,30),Qt::KeepAspectRatio);
    setPixmap(newPixmap);
}

RotationArrow::~RotationArrow()
{
    delete pixmap;
    pixmap = nullptr;
}

int RotationArrow::type() const
{
    return Type;
}

int RotationArrow::getMiniBoard()
{
    return miniboard;
}

Direction RotationArrow::getDirection()
{
    return dir;
}
