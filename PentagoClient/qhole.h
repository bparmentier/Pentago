#ifndef QHOLE_H
#define QHOLE_H

#include <QPainter>
#include <QGraphicsEllipseItem>

class QHole : public QGraphicsEllipseItem
{
public:
    enum {
        Type = UserType + 2
    };

    QHole();

    int type() const;

    /*!
     * \brief Reimplemented from QGraphicsEllipseItem::paint().
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
               QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QHOLE_H
