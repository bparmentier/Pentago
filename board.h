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
    int nombreCoup;

public:
    Board();
    void placeBall(int x, int y, Player *player);
    void rotateMiniBoard(int numMiniPlateau, Direction direction);
    std::vector<std::vector<Hole>> getBoard() const;
    BallColor getColor(int x, int y) const;
    Player * getJoueurTrou(int x, int y) const;
    bool isHoleOccupied(int x, int y) const;
    bool verifierSuitePion(int x, int y);
    bool verifierSuitePionApresTour(int numMiniPlateau);
    bool dernierCoup() const;

private:
    void rotateClockwise(int x, int y);
    void rotateCounterclockwise(int x, int y);
    bool pentagoVerticale(int x, int y);
    bool pentagoHorizontal(int x, int y);
    bool pentagoDiagonaleDroite(int x, int y);
    bool pentagoDiagonaleGauche(int x, int y);
};

#endif // BOARD_H
