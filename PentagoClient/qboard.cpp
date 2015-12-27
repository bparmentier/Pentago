#include "qboard.h"
#include "pentagogui.h"
#include "qhole.h"
#include "qball.h"

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

    if (!event->isAccepted()) {



    //if (item) {
    foreach(auto item, items(event->scenePos())) {
        qDebug() << item->type();
        if(item->type() == QHole::Type) {
            qDebug() << "hello";
            QBall *ball = new QBall(QBallColor::WHITE);
            addItem(ball);
            ball->setPos(item->scenePos());

            break;
        }
    //}
    }
    }
}
