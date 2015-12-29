#ifndef QBOARD_H
#define QBOARD_H

#include <array>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "qballcolor.h"
#include "pentagogui.h"

class PentagoGui;
class QBoard : public QGraphicsScene
{
    Q_OBJECT

private:
    static const int BOARD_WIDTH = 6;
    QBallColor color;
    QBallColor otherColor;
    int x;
    int y;
    std::array<std::array<QGraphicsEllipseItem *, BOARD_WIDTH>, BOARD_WIDTH> holes;
    PentagoGui * pentagoGui;
    void drawMiniBoard(qreal x, qreal y);
    void drawMiniBoard(qreal x, qreal y, QVector<QVector<PlayerColor> > board);
    void drawHoles();


protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void test(int x,int y);
public:
    QBoard(QWidget *parent = 0);
    void setColor(QBallColor aColor);
    int getX();
    int getY();
    void updateBoard(QVector<QVector<PlayerColor> > board);
};

#endif // QBOARD_H