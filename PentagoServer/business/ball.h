#ifndef BALL_H
#define BALL_H

#include "ballcolor.h"

class Ball
{

private:
    BallColor color;

public:
    Ball(BallColor color);
    BallColor getColor() const;
};

#endif // BALL_H