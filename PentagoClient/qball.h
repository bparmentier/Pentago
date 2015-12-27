#ifndef QBALL_H
#define QBALL_H

#include <QGraphicsEllipseItem>
#include <QPainter>
#include "qballcolor.h"

class QBall : public QGraphicsEllipseItem
{
public:
    enum {
        Type = UserType + 1
    };

    QBall(QBallColor color);

    int type() const;

    /*!
     * \brief Reimplemented from QGraphicsEllipseItem::paint().
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

private:
    QBallColor ballColor;
};

#endif // QBALL_H
