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
    GameManager(std::vector<Player> & players);
    Player *getCurrentPlayer();
    void nextPlayer();
};

#endif // GAMEMANAGER_H
