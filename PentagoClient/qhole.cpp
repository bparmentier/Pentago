#include "qhole.h"

QHole::QHole() :
    QGraphicsEllipseItem(0, 0, 30, 30)
{
}

int QHole::type() const
{
    return Type;
}

void QHole::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();

    QRadialGradient gradient(rect.topLeft(), 30);
    gradient.setColorAt(0, QColor(192, 35, 35));
    gradient.setColorAt(1, QColor(226, 36, 36));
    painter->setBrush(gradient);

    painter->drawEllipse(rect);
}

void QHole::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsEllipseItem::mousePressEvent(event);
}

