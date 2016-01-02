#ifndef QBOARD_H
#define QBOARD_H

#include <array>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include "qballcolor.h"
#include "pentagogui.h"
#include "rotationarrow.h"
class PentagoGui;
class QBoard : public QGraphicsScene
{
    Q_OBJECT

private:
    static const int BOARD_WIDTH = 6;
    static const int KEY_LINE = 0x0;
    static const int KEY_COLUMN = 0x1;
    enum MiniBoardPosition {
        TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
    };
    std::vector<RotationArrow *> arrows;
    QBallColor color;
    std::array<std::array<QGraphicsEllipseItem *, BOARD_WIDTH>, BOARD_WIDTH> holes;
    PentagoGui * pentagoGui;
    void drawMiniBoard(MiniBoardPosition miniBoardPosition, qreal x, qreal y);
    void drawMiniBoard(MiniBoardPosition miniBoardPosition, qreal x, qreal y, QVector<QVector<PlayerColor> > board);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    QBoard(QWidget *parent = 0);
    void setColor(QBallColor color);
    void updateBoard(QVector<QVector<PlayerColor> > board);
    void readyrotate();
};

#endif // QBOARD_H
