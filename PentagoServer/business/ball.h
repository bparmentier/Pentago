#ifndef BALL_H
#define BALL_H

#include "ballcolor.h"

class Ball
{

private:
    BallColor color;

public:

    /*!
     * \brief constructor of ball class
     * \param color color of the ball
     */
    Ball(BallColor color);

    /*!
     * \return the color of the ball
     */
    BallColor getColor() const;
};

#endif // BALL_H
