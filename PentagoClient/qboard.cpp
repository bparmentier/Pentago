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

void QBoard::drawMiniBoard(qreal x, qreal y,QVector<QVector<PlayerColor>> board)
{
    QGraphicsRectItem *miniBoard = addRect(0, 0, 50 * BOARD_WIDTH / 2, 50 * BOARD_WIDTH / 2);
    miniBoard->setPos(x, y);
    miniBoard->setBrush(QColor(192, 35, 35));
    QBallColor tmp;
    QCursor pointingHandCursor{QCursor(Qt::PointingHandCursor)};

    for (auto line = 0; line < 3; ++line) {
        for (auto column = 0; column < 3; ++column) {
            if(board.at(line).at(column) != PlayerColor::NONE){
                if(board.at(line).at(column) == PlayerColor::WHITE) {
                    tmp = QBallColor::WHITE;
                }
                else {
                    tmp = QBallColor::BLACK;
                }
                QBall *ball = new QBall(tmp);
                addItem(ball);
                ball->setPos(x + line * 50 + 10, y + column * 50 + 10);
            }
            else{
                QHole *hole = new QHole();
                addItem(hole);
                hole->setPos(x + line * 50 + 10, y + column * 50 + 10);
                hole->setCursor(pointingHandCursor);
                holes.at(line).at(column) = hole;
            }
        }
    }
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

void QBoard::updateBoard(QVector<QVector<PlayerColor> > board)
{

    this->clear();
    QVector<QVector<PlayerColor>> miniTL(3,QVector<PlayerColor>(3)),miniTR(3,QVector<PlayerColor>(3)),
            miniBL(3,QVector<PlayerColor>(3)),miniBR(3,QVector<PlayerColor>(3));

    for(int i = 0;i<3;i++){
        for( int j = 0;j<3;j++){
            miniTL[i][j] = board.at(i).at(j);
        }
    }

    for(int i = 0;i<3;i++){
        for(int j = 0,z=3 ; j<3 ; j++,z++){
            miniTR[i][j] = board[i][z];
        }
    }
    for(int i = 0,y=3;i<3;i++,y++){
        for( int j = 0,y=3;j<0;j++,y++){
            miniBL[i][j] = board.at(y).at(j);
        }
    }
    for(int i = 0,y=3;i<3;i++,y++){
        for( int j = 0,z=3;j<3;j++,z++){
            miniBR[i][j] = board[y][z];
        }
    }

    drawMiniBoard(0, 0,miniTL);
    drawMiniBoard(0, 160,miniTR);
    drawMiniBoard(160, 0,miniBL);
    drawMiniBoard(160, 160,miniBR);
}

void QBoard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int x,y;
    QGraphicsScene::mousePressEvent(event);

    foreach(auto item, items(event->scenePos())) {
        if(item->type() == QHole::Type) {
            QBall *ball = new QBall(color);
            addItem(ball);
            ball->setPos(item->scenePos());
            x = (event->pos().y()-10)/50;
            y = (event->pos().x()-10)/50;
            qDebug() << "(" <<x<<","<<y<<")";
            pentagoGui->play(x,y);
            break;
        }
    }
}
void QBoard::setColor(QBallColor aColor){
    color = aColor;
    if(color == QBallColor::BLACK) otherColor = QBallColor::WHITE;
    else otherColor = QBallColor::BLACK;
}

int QBoard::getX()
{
    return x;
}

int QBoard::getY()
{
    return y;
}











