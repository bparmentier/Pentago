#ifndef QBOARD_H
#define QBOARD_H

#include <array>

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>


class QBoard : public QGraphicsScene
{
    Q_OBJECT

private:
    static const int BOARD_WIDTH = 6;

    std::array<std::array<QGraphicsEllipseItem *, BOARD_WIDTH>, BOARD_WIDTH> holes;

    void drawMiniBoard(qreal x, qreal y);
    void drawHoles();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

public:
    QBoard(QWidget *parent = 0);
};

#endif // QBOARD_H
