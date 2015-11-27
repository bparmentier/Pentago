#include "ball.h"


Ball::Ball(BallColor color):color(color)
{
}
///
/// \brief Ball::getColor
/// \return
///
BallColor Ball::getColor() const
{
    return color;
}

