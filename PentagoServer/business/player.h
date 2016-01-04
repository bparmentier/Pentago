#ifndef JOUEUR_H
#define JOUEUR_H

#include "ballcolor.h"
#include <string>
#include <QTcpSocket>

class Player
{

private:
    std::string name;
    BallColor ballColor;
    QTcpSocket * playerIdentifier;

public:

    /*!
     * \brief constructor of the player of pentagoConstructeur d'un joueur de Pentago
     * \param name name of the player
     * \param color the player ball color
     */
    Player(std::string name, BallColor color, QTcpSocket * playerIdentifier);

    /*!
     * \brief allow to get the name of the player
     * \return the name of the player
     */
    std::string getName() const;

    /*!
     * \brief allow to get the color of the player ball
     * \return the color of the ball
     */
    BallColor getBallColor() const;

    /*!
     * \brief allow to get the socket of the player
     * \return the socket of the player
     */
    QTcpSocket * getPlayerSocket() const;

};

#endif // JOUEUR_H
