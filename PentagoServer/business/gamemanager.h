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
     * \brief constructor of the player manager class
     * \param players arrays of players
     */
    GameManager(std::vector<Player> & players);

    /*!
     * \brief allow to get the current player of the game
     * \return the current player
     */
    Player *getCurrentPlayer();

    /*!
     * \brief allow to pass to the next player of the game
     */
    void nextPlayer();

    /*!
     * \brief allow to get the name of the player by his ball color
     * \param color the color of the player that we want
     * \return the name of the player
     */
    std::string getNamePlayerByColor(BallColor color);

    /*!
     * \brief allow to get the socket of the player by his color
     * \param color the color of the player that we want
     * \return the socket of the player
     */
    QTcpSocket * getIdentifierPlayerByColor(BallColor color);
};

#endif // GAMEMANAGER_H
