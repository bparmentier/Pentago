#include "pentago.h"
#include "pentagoexception.h"
#include <iostream>

using namespace std;

Pentago::Pentago(vector<Player> & players):gameManager(players), board(),
    finished(false)
{
}

void Pentago::play(int x, int y)
{
    if(finished == true){
        throw PentagoException("La partie est terminée !");
    }
    this->board.placeBall(x,y,gameManager.getCurrentPlayer());
    finished = board.checkSequencePentago(x,y);
}

void Pentago::rotate(int miniBoard, Direction direction)
{
    if(finished == true){
        throw string("la partie est terminé !");
    }
    if(miniBoard < 1 || miniBoard > 4){
        throw PentagoException("le mini-plateau choisit est incorrecte !");
    }
    board.rotateMiniBoard(miniBoard, direction);
    finished = board.checkSequencePentagoAfterRotate(miniBoard);
    if(!finished){
        gameManager.nextPlayer();
    }
}

bool Pentago::isFinished() const
{
    return finished || board.lastPlay();
}

bool Pentago::resultatEgalite() const{
    return board.lastPlay();
}

string Pentago::getWinnerName() {
    if(!finished){
        throw string("error, la partie n'est pas terminé");
    }
    return gameManager.getCurrentPlayer()->getName();
}

string Pentago::getCurrentPlayerName()
{
    return gameManager.getCurrentPlayer()->getName();
}
BallColor Pentago::getCurrentPLayerBallColor(){
    return gameManager.getCurrentPlayer()->getBallColor();
}

vector<vector<Hole> > Pentago::getBoard() const
{
    return board.getBoard();
}
