#include "qball.h"

QBall::QBall(QBallColor color) : QGraphicsEllipseItem(0, 0, 30, 30)
{
    ballColor = color;
}

int QBall::type() const
{
    return Type;
}

void QBall::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rect = boundingRect();
    QRadialGradient gradient(rect.topLeft(), 30);
    if (ballColor == QBallColor::BLACK) {
        gradient.setColorAt(0, Qt::darkGray);
        gradient.setColorAt(1, Qt::black);
    } else {
        gradient.setColorAt(0, Qt::white);
        gradient.setColorAt(1, Qt::lightGray);
    }
    painter->setBrush(gradient);
    painter->drawEllipse(rect);
}
