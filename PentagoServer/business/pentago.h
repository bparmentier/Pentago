#ifndef PENTAGO_H
#define PENTAGO_H

#include "gamemanager.h"
#include "board.h"
#include "actiongame.h"
#include <vector>

class Pentago
{

private:
    GameManager gameManager;
    Board board;
    ActionGame nextAction;
    BallColor winner;

public:

    /*!
     * \brief constructor of the game pentago
     * \param players arrays of the players
     */
    Pentago(std::vector<Player> & players);

    /*!
     * \brief allow to play a ball on the board game
     * \param x the row choosed
     * \param y the column choosed
     * \throw PentagoException if the game is finish
     */
    void play(int x, int y, QTcpSocket *player);

    /*!
     * \brief allow to make the rotation of a mini-board
     * \param miniBoard number of the mini-board
     * \param direction direction of the rotation
     * \throw PentagoException si the game is finish or the number of
     * the mini-board is invalid
     */
    void rotate(int miniBoard, Direction direction, QTcpSocket * player);

    /*!
     * \brief allow to know if a game is finish
     * \return true if it's finish false if not
     */
    bool isFinished() const;

    /*!
     * \brief allow to know if a game has finished by a draw
     * \return true if it's a draw false if not
     */
    bool resultatEgalite() const;

    /*!
     * \brief allow to get the name of the winner
     * \return the name of the winner
     * \throw PentagoException if the game is finish
     */
    std::string getWinnerName();

    /*!
     * \brief allow to get the color of the ball of the winner
     * \return the color of the winner
     * \throw PentagoException if the game is not finish
     */
    BallColor getWinnerBallColor();

    /*!
     * \brief allow to get the socket of the winner
     * \return the socket of the winner
     * \throw PentagoException if the game is finish
     */
    QTcpSocket * getWinnerSocket();

    /*!
     * \brief allow to get the name of the current player
     * \return the name of the current player
     */
    std::string getCurrentPlayerName();

    /*!
     * \brief allow to get the color of the ball of the current player
     * \return the color of the ball
     */
    BallColor getCurrentPLayerBallColor();

    /*!
     * \brief allow to get the board of the game
     * \return the board of the game
     */
    std::vector<std::vector<Hole>> getBoard() const;

};

#endif // PENTAGO_H
