#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "hole.h"
#include "ballcolor.h"
#include "direction.h"

class Board
{

private:
    std::vector<std::vector<Hole>> board;
    int playNumber;

public:
    /*!
     * \brief constructor of board class
     */
    Board();

    /*!
     * \brief allow to place a ball on the board
     * \param x the row choosed
     * \param y the column choosed
     * \param player the player who want to place a ball
     * \throw PentagoException if the position played is occupied
     */
    void placeBall(int x, int y, Player *player);

    /*!
     * \brief allow to rotate a mini-board of the board
     * \param miniBoardNum number of the mini-board
     * \param direction direction of the rotation
     * \param player player whor want to rotate a mini-board
     */
    void rotateMiniBoard(int miniBoardNum, Direction direction);

    /*!
     * \brief allow to get the board
     * \return the board
     */
    std::vector<std::vector<Hole>> getBoard() const;

    /*!
     * \brief allow to get the color of the ball in the position choosed
     * \param x the row choosed
     * \param y the column choosed
     * \return the color of the ball
     */
    BallColor getColor(int x, int y) const;

    /*!
     * \brief allow to get the player who played on a hole
     * \param x the row choosed
     * \param y the column choosed
     * \return the player
     */
    Player * getJoueurTrou(int x, int y) const;

    /*!
     * \brief allow to know if a hole is occuppied
     * \param x the row choosed
     * \param y the column choosed
     * \return true if it's occupied false if not
     */
    bool isHoleOccupied(int x, int y) const;

    /*!
     * \brief allow to check if there is a pentago after a ball placement
     * \param x the row where the ball has been played
     * \param y the column where the ball has been played
     * \return true si il y'a un pentago false si non
     */
    bool checkSequencePentago(int x, int y);

    /*!
     * \brief allow to check if there is a pentago after rotation of a mini-board
     * \param numMiniPlateau number of the mini-board
     * \return the color of the winner if there is one, the color of a empty hole in the other case
     */
    BallColor checkSequencePentagoAfterRotate(int numMiniPlateau);

    /*!
     * \brief allow to know if it's all the hole are occupied
     * \return true if it is false if not
     */
    bool lastPlay() const;

private:
    void rotate(int startColumn, int startLine, Direction direction);
    bool pentagoVertical(int x, int y);
    bool pentagoHorizontal(int x, int y);
    bool pentagoRightDiagonal(int x, int y);
    bool pentagoLeftDiagonal(int x, int y);
};

#endif // BOARD_H
