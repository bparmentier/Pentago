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

    /*!
     * \brief constructor of hole class
     */
    Hole();

    /*!
     * \brief allow to place a ball into a hole
     * \param ball the ball to place
     */
    void setBall(Ball bille);

    /*!
     * \brief allow to set the player who played on the hole
     * \param player the player
     */
    void setPlayer(Player * player);

    /*!
     * \brief allow to get the ball of a hole
     * \return the ball of the hole
     */
    Ball getBall() const;

    /*!
     * \brief allow to get the player who played on the hole
     * \return the player
     */
    Player * getPlayer()const;

    /*!
     * \brief allow to know if a hole is occupied
     * \return true if the hole is occupied false if not
     */
    bool isOccupied() const;

};

/*!
 * \brief operator ==
 * \param a the first hole
 * \param b the second hole
 * \return true if the two hole are the same false if not
 */
bool operator==(Hole const& a, Hole const& b);

#endif // HOLE_H
