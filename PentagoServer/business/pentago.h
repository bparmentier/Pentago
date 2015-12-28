#ifndef PENTAGO_H
#define PENTAGO_H

#include "gamemanager.h"
#include "board.h"
#include <vector>

class Pentago
{

public:
    GameManager gameManager;
    Board board;
    bool finished;

public:
    Pentago(std::vector<Player> & players);
    void play(int x, int y);
    void rotate(int miniBoard, Direction direction);
    bool isFinished() const;
    bool resultatEgalite() const;
    std::string getWinnerName();
    std::string getCurrentPlayerName();
    BallColor getCurrentPLayerBallColor();
    std::vector<std::vector<Hole>> getBoard() const;

};

#endif // PENTAGO_H
