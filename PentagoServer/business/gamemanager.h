#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include "player.h"
class GameManager
{

private:
    std::vector<Player> players;
    int currentIndice;

public:

    /*!
     * \brief constructeur du gestionnaire des joueurs de la partie
     * \param players tableau des joueurs de la partie
     */
    GameManager(std::vector<Player> & players);

    /*!
     * \brief permet d'obtenir le joueur courant de la partie
     * \return le joueur courant
     */
    Player *getCurrentPlayer();

    /*!
     * \brief permet de passer au joueur suivant de la partie
     */
    void nextPlayer();
};

#endif // GAMEMANAGER_H
