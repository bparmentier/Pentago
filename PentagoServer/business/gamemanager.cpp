#include "gamemanager.h"
#include "pentagoexception.h"
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

std::string GameManager::getNamePlayerByColor(BallColor color){
    if(color == BallColor::NONE){
        throw PentagoException("il n'y a pas de gagnant !");
    }
    if(color==this->players.at(0).getBallColor()){
        return this->players.at(0).getName();
    }else{
        return this->players.at(1).getName();
    }
}

QTcpSocket * GameManager::getIdentifierPlayerByColor(BallColor color)
{
    if(color == BallColor::NONE){
        throw PentagoException("il n'y a pas de gagnant !");
    }
    if(color == this->players.at(0).getBallColor()){
        return this->players.at(0).getPlayerIdentifier();
    }else{
        return this->players.at(1).getPlayerIdentifier();
    }
}
