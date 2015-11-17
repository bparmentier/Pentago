#ifndef HOLE_H
#define HOLE_H

#include "ball.h"
#include "player.h"
#include "ballcolor.h"

class Hole
{

private:
    Ball ball;
    Player * player;

public:
    Hole();
    void setBall(Ball bille);
    void setPlayer(Player * player);
    Ball getBall() const;
    Player * getPlayer()const;
    bool isOccupied() const;

};

bool operator==(Hole const& a, Hole const& b);

#endif // HOLE_H
