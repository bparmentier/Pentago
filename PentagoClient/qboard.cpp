#include "qboard.h"
#include "pentagogui.h"

QBoard::QBoard(QWidget *parent) :
    QGraphicsScene{parent}
{
    drawMiniBoard(0, 0);
    drawMiniBoard(0, 160);
    drawMiniBoard(160, 0);
    drawMiniBoard(160, 160);
}

void QBoard::drawMiniBoard(qreal x, qreal y)
{
    addRect(0, 0, 50 * BOARD_WIDTH / 2, 50 * BOARD_WIDTH / 2)->setPos(x, y);

    for (auto line = 0; line < 3; ++line) {
        for (auto column = 0; column < 3; ++column) {
            qreal xHole = x + line * 50;
            qreal yHole = y + column * 50;

            QGraphicsEllipseItem *hole = addEllipse(10, 10, 30, 30);
            hole->setPos(xHole, yHole);

            QRadialGradient gradient(hole->boundingRect().topLeft(), 30);
            gradient.setColorAt(0, Qt::white);
            gradient.setColorAt(1, Qt::gray);
            hole->setBrush(gradient);
            holes.at(line).at(column) = hole;
        }
    }
}
