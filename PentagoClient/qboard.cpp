#include "qboard.h"
#include "pentagogui.h"
#include "qhole.h"
#include "qball.h"

QBoard::QBoard(QWidget *parent) :
    QGraphicsScene{parent}
{
    pentagoGui = dynamic_cast<PentagoGui*>(parent);
    x,y=0;
    drawMiniBoard(0, 0);
    drawMiniBoard(0, 160);
    drawMiniBoard(160, 0);
    drawMiniBoard(160, 160);
}

void QBoard::drawMiniBoard(qreal x, qreal y)
{
    QGraphicsRectItem *miniBoard = addRect(0, 0, 50 * BOARD_WIDTH / 2, 50 * BOARD_WIDTH / 2);
    miniBoard->setPos(x, y);
    miniBoard->setBrush(QColor(192, 35, 35));

    QCursor pointingHandCursor{QCursor(Qt::PointingHandCursor)};

    for (auto line = 0; line < 3; ++line) {
        for (auto column = 0; column < 3; ++column) {
            QHole *hole = new QHole();
            addItem(hole);
            hole->setPos(x + line * 50 + 10, y + column * 50 + 10);

            hole->setCursor(pointingHandCursor);
            holes.at(line).at(column) = hole;
        }
    }
}

void QBoard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);

    foreach(auto item, items(event->scenePos())) {
        if(item->type() == QHole::Type) {
            QBall *ball = new QBall(color);
            addItem(ball);
            ball->setPos(item->scenePos());
            pentagoGui->play((event->pos().y()-10)/50,(event->pos().x()-10)/50);
            break;
        }
    }
}
void QBoard::setColor(QBallColor aColor){
    color = aColor;
}

int QBoard::getX()
{
  return x;
}

int QBoard::getY()
{
    return y;
}











