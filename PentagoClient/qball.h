#ifndef QBALL_H
#define QBALL_H

#include <QGraphicsEllipseItem>
#include <QPainter>
#include "qballcolor.h"

class QBall : public QGraphicsEllipseItem
{
private:
    QBallColor ballColor;

public:
    enum {
        Type = UserType + 1
    };

    /*!
     * \brief Construct a QBall of the given color
     * \param color the color of the QBall
     */
    QBall(QBallColor color);

    /*!
     * \brief Returns the custom type of the item
     * \return the custom type of the item
     */
    int type() const;

    /*!
     * \brief Reimplemented from QGraphicsEllipseItem::paint().
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);
};

#endif // QBALL_H
