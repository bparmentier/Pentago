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
     * \brief constructeur d'un trou du plateau
     */
    Hole();

    /*!
     * \brief permet de placer une bille dans le trou
     * \param bille la bille à y placer
     */
    void setBall(Ball bille);

    /*!
     * \brief permet d'indiquer le joueur qui a joué sur ce trou
     * \param player le joueur
     */
    void setPlayer(Player * player);

    /*!
     * \brief permet d'obtenir la bille d'un trou
     * \return la bille du trou
     */
    Ball getBall() const;

    /*!
     * \brief permet d'obtenir le joueur du trou
     * \return le joueur du trou
     */
    Player * getPlayer()const;

    /*!
     * \brief permet de savoir si un trou est occupé
     * \return true si le trou est occupé false si non
     */
    bool isOccupied() const;

};

/*!
 * \brief operator ==
 * \param a le premier trou
 * \param b le deuxièmme trou
 * \return true si les trou ont les mêmes caractéristiques false si non
 */
bool operator==(Hole const& a, Hole const& b);

#endif // HOLE_H
