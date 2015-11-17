#include "gamemanager.h"
#include <iostream>

GameManager::GameManager(std::vector<Player> &tabJoueurs):currentIndice(0)
{
    for(int i = 0; i<tabJoueurs.size();i++){
        this->players.push_back(Player(tabJoueurs[i]));
    }
}

Player * GameManager::getCurrentPlayer()
{
    return &(players.at(currentIndice));
}

void GameManager::nextPlayer()
{
    currentIndice = ((currentIndice + 1)%players.size());
}

