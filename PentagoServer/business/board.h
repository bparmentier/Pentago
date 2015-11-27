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
    void rotateMiniBoard(int miniBoardNum, Direction direction);
    std::vector<std::vector<Hole>> getBoard() const;
    BallColor getColor(int x, int y) const;
    Player * getJoueurTrou(int x, int y) const;
    bool isHoleOccupied(int x, int y) const;
    bool verifierSuitePion(int x, int y);
    bool verifierSuitePionApresTour(int numMiniPlateau);
    bool dernierCoup() const;

private:
    void rotate(int startColumn, int startLine, Direction direction);
    bool pentagoVerticale(int x, int y);
    bool pentagoHorizontal(int x, int y);
    bool pentagoDiagonaleDroite(int x, int y);
    bool pentagoDiagonaleGauche(int x, int y);
};

#endif // BOARD_H
