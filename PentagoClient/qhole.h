#ifndef QHOLE_H
#define QHOLE_H

#include <QPainter>
#include <QGraphicsEllipseItem>
#include <QDebug>

class QHole : public QGraphicsEllipseItem
{

private:
    bool black;

public:
    enum {
        Type = UserType + 2
    };

    /*!
     * \brief Constructs a QHole
     */
    QHole();

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

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // QHOLE_H
