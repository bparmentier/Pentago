#include "ball.h"


Ball::Ball(BallColor color):color(color)
{
}

BallColor Ball::getColor() const
{
    return color;
}

