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

    /*!
     * \brief Constructs an arrow for the given mini-board to rotate it in the
     * given Direction
     * \param aMiniBoard the associated mini-board identifier
     * \param aDirection the direction in which to rotate the mini-board
     */
    RotationArrow(int aMiniBoard, Direction aDirection);

    /*!
     * \brief Returns the custom type of the item
     * \return the custom type of the item
     */
    int type() const;

    /*!
     * \brief Returns the associated miniboard identifier
     * \return the associated miniboard identifier
     */
    int getMiniBoard();

    /*!
     * \brief Returns the direction in which the arrow is set to rotate the
     * associated mini-board
     * \return the direction in which the arrow is set to rotate the
     * associated mini-board
     */
    Direction getDirection();
};

#endif // ROTATIONARROW_H
