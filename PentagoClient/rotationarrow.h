#ifndef ROTATIONARROW_H
#define ROTATIONARROW_H
#include <QGraphicsPixmapItem>
#include "direction.h"

class RotationArrow : public QGraphicsPixmapItem
{
private:
    int miniboard;
    Direction dir;
    QPixmap * pixmap;
public:
    RotationArrow(int aMiniBoard,Direction aDirection);
    int getMiniBoard();
    Direction getDirection();
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

#endif // ROTATIONARROW_H
