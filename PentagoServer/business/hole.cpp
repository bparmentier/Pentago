#include "hole.h"
#include "ballcolor.h"

Hole::Hole(): ball(BallColor::NONE), player(nullptr)
{
}

void Hole::setBall(Ball ball)
{
    this->ball = ball;
}

void Hole::setPlayer(Player * player)
{
    this->player = player;
}

Ball Hole::getBall() const
{
    return ball;
}

Player * Hole::getPlayer() const
{
    return player;
}

bool Hole::isOccupied() const
{
    return player!=nullptr;
}

bool operator==(Hole const& a, Hole const& b){
    return a.getBall().getColor() == b.getBall().getColor()
            && a.getPlayer() == b.getPlayer();
}
