#ifndef BALL_H
#define BALL_H

#include "ballcolor.h"

class Ball
{

private:
    BallColor color;

public:
    /*!
     * \brief constructeur de la class Ball
     * \param color couleur de la bille
     */
    Ball(BallColor color);

    /*!
     * \return la couleur de la bille
     */
    BallColor getColor() const;
};

#endif // BALL_H
