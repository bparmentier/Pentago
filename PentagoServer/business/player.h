#ifndef JOUEUR_H
#define JOUEUR_H

#include "ballcolor.h"
#include <string>

class Player
{

private:
    std::string name;
    BallColor ballColor;

public:

    /*!
     * \brief Constructeur d'un joueur de Pentago
     * \param name nom du joueur
     * \param color couleur des billes du joueur
     */
    Player(std::string name, BallColor color);

    /*!
     * \brief permet d'obtenir le nom du joueur
     * \return le nom du joueur
     */
    std::string getName() const;

    /*!
     * \brief permet d'obtenir la couleur des billes du joueur
     * \return la couleur des billes du joueur
     */
    BallColor getBallColor() const;

};

#endif // JOUEUR_H
