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
    enum {
        Type = UserType + 3
    };

    RotationArrow(int aMiniBoard,Direction aDirection);
    int type() const;
    int getMiniBoard();
    Direction getDirection();
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

#endif // ROTATIONARROW_H
