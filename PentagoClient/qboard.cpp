#include "qboard.h"
#include "pentagogui.h"
#include "qhole.h"
#include "qball.h"

QBoard::QBoard(QWidget *parent) :
    QGraphicsScene{parent}
{
    pentagoGui = dynamic_cast<PentagoGui*>(parent);
    drawMiniBoard(TOP_LEFT, 0, 0);
    drawMiniBoard(BOTTOM_LEFT, 0, 160);
    drawMiniBoard(TOP_RIGHT, 160, 0);
    drawMiniBoard(BOTTOM_RIGHT, 160, 160);
}

void QBoard::drawMiniBoard(MiniBoardPosition miniBoardPosition, qreal x, qreal y,QVector<QVector<PlayerColor>> board)
{
    QGraphicsRectItem *miniBoard = addRect(0, 0, 50 * BOARD_WIDTH / 2, 50 * BOARD_WIDTH / 2);
    miniBoard->setPos(x, y);
    miniBoard->setBrush(QColor(192, 35, 35));
    QCursor pointingHandCursor{QCursor(Qt::PointingHandCursor)};

    for (auto line = 0; line < 3; ++line) {
        for (auto column = 0; column < 3; ++column) {
            if (board.at(line).at(column) != PlayerColor::NONE) {
                QBallColor ballColor;
                if (board.at(line).at(column) == PlayerColor::WHITE) {
                    qDebug() << "ballColor : WHITE";
                    ballColor = QBallColor::WHITE;
                } else {
                    qDebug() << "ballColor : BLACK";
                    ballColor = QBallColor::BLACK;
                }
                QBall *ball = new QBall(ballColor);
                addItem(ball);
                ball->setPos(x + line * 50 + 10, y + column * 50 + 10);
            } else {
                QHole *hole = new QHole();
                int holeLineIndex = line;
                int holeColumnIndex = column;
                if (miniBoardPosition == BOTTOM_LEFT
                        || miniBoardPosition == BOTTOM_RIGHT) {
                    holeLineIndex += 3;
                }
                if (miniBoardPosition == TOP_RIGHT
                        || miniBoardPosition == BOTTOM_RIGHT) {
                    holeColumnIndex += 3;
                }
                hole->setData(KEY_LINE, holeLineIndex);
                hole->setData(KEY_COLUMN, holeColumnIndex);
                addItem(hole);
                hole->setPos(x + line * 50 + 10, y + column * 50 + 10);
                hole->setCursor(pointingHandCursor);
                holes.at(line).at(column) = hole;
            }
        }
    }
}
void QBoard::drawMiniBoard(MiniBoardPosition miniBoardPosition, qreal x, qreal y)
{
    QGraphicsRectItem *miniBoard = addRect(0, 0, 50 * BOARD_WIDTH / 2, 50 * BOARD_WIDTH / 2);
    miniBoard->setPos(x, y);
    miniBoard->setBrush(QColor(192, 35, 35));
    QCursor pointingHandCursor{QCursor(Qt::PointingHandCursor)};

    for (auto line = 0; line < 3; ++line) {
        for (auto column = 0; column < 3; ++column) {
            QHole *hole = new QHole();
            int holeLineIndex = line;
            int holeColumnIndex = column;
            if (miniBoardPosition == BOTTOM_LEFT
                    || miniBoardPosition == BOTTOM_RIGHT) {
                holeLineIndex += 3;
            }
            if (miniBoardPosition == TOP_RIGHT
                    || miniBoardPosition == BOTTOM_RIGHT) {
                holeColumnIndex += 3;
            }
            hole->setData(KEY_LINE, holeLineIndex);
            hole->setData(KEY_COLUMN, holeColumnIndex);
            addItem(hole);
            hole->setPos(x + line * 50 + 10, y + column * 50 + 10);
            hole->setCursor(pointingHandCursor);
            holes.at(line).at(column) = hole;
        }
    }
}

void QBoard::updateBoard(QVector<QVector<PlayerColor> > board)
{
    this->clear();
    QVector<QVector<PlayerColor>> miniTL(3, QVector<PlayerColor>(3)),
            miniTR(3, QVector<PlayerColor>(3)),
            miniBL(3, QVector<PlayerColor>(3)),
            miniBR(3, QVector<PlayerColor>(3));

    for (int line = 0; line < 3; ++line){
        for (int column = 0; column < 3; ++column){
            miniTL[line][column] = board.at(line).at(column);
        }
    }
    for (int line = 0; line < 3; ++line){
        for (int column = 0; column < 3 ; ++column){
            miniTR[line][column] = board.at(line).at(column + 3);
        }
    }
    for (int line = 0; line < 3; ++line){
        for (int column = 0; column < 3; ++column){
            miniBL[line][column] = board.at(line + 3).at(column);
        }
    }
    for (int line = 0; line < 3; ++line){
        for (int column = 0; column < 3; ++column){
            miniBR[line][column] = board.at(line + 3).at(column + 3);
        }
    }

    drawMiniBoard(TOP_LEFT, 0, 0, miniTL);
    drawMiniBoard(BOTTOM_LEFT, 0, 160, miniBL);
    drawMiniBoard(TOP_RIGHT, 160, 0, miniTR);
    drawMiniBoard(BOTTOM_RIGHT, 160, 160, miniBR);
}

void QBoard::readyrotate()
{
    arrows.clear();
    RotationArrow * mini1CW = new RotationArrow(2,Direction::CLOCKWISE);
    RotationArrow * mini1CCW = new RotationArrow(2,Direction::COUNTERCLOCKWISE);

    RotationArrow * mini0CW = new RotationArrow(1,Direction::CLOCKWISE);
    RotationArrow * mini0CCW = new RotationArrow(1,Direction::COUNTERCLOCKWISE);

    RotationArrow * mini2CW = new RotationArrow(3,Direction::CLOCKWISE);
    RotationArrow * mini2CCW = new RotationArrow(3,Direction::COUNTERCLOCKWISE);

    RotationArrow * mini3CW = new RotationArrow(4,Direction::CLOCKWISE);
    RotationArrow * mini3CCW = new RotationArrow(4,Direction::COUNTERCLOCKWISE);

    mini1CW->setPos(340,0);
    mini1CW->setRotation(90);
    mini1CCW->setPos(280,-30);

    mini0CW->setPos(0,-30);
    mini0CCW->setPos(-30,30);
    mini0CCW->setRotation(-90);

    mini2CW->setPos(-30,310);
    mini2CW->setRotation(-90);
    mini2CCW->setPos(30,340);
    mini2CCW->setRotation(180);

    mini3CW->setPos(310,340);
    mini3CW->setRotation(180);
    mini3CCW->setPos(340,280);
    mini3CCW->setRotation(90);

    arrows.push_back(mini1CW);
    arrows.push_back(mini1CCW);
    arrows.push_back(mini0CW);
    arrows.push_back(mini0CCW);
    arrows.push_back(mini2CW);
    arrows.push_back(mini2CCW);
    arrows.push_back(mini3CW);
    arrows.push_back(mini3CCW);

    for(auto e:arrows) addItem(e);


}

void QBoard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsScene::mousePressEvent(event);

    foreach(auto item, items(event->scenePos())) {
        if(item->type() == QHole::Type) {
            int x = item->data(KEY_LINE).toInt();
            int y = item->data(KEY_COLUMN).toInt();
            qDebug() << "(" <<x<<","<<y<<")";
            pentagoGui->play(x,y);
            break;
        }else if(item->type() == RotationArrow::Type){
            RotationArrow * temp = dynamic_cast<RotationArrow *>(item);
            if(temp){
                bool clockwise = temp->getDirection() == Direction::CLOCKWISE ? true : false;
                pentagoGui->rotate(temp->getMiniBoard(),clockwise);
            }
        }
    }
}
void QBoard::setColor(QBallColor color){
    this->color = color;
}











