#include "pentago.h"
#include "pentagoexception.h"
#include <iostream>

using namespace std;

Pentago::Pentago(vector<Player> & players):gameManager(players), board(),
    nextAction(ActionGame::PLAY), winner(BallColor::NONE)
{
}

void Pentago::play(int x, int y, QTcpSocket * player)
{
    if(isFinished()){
        throw PentagoException("La partie est terminée !");
    }
    if(player!=this->gameManager.getCurrentPlayer()->getPlayerSocket()){
        throw PentagoException("c'est à votre adversaire de jouer !");
    }
    if(nextAction!=ActionGame::PLAY){
        throw PentagoException("il faut d'abord effectuer la rotation d'un mini-plateau !");
    }
    this->board.placeBall(x,y,gameManager.getCurrentPlayer());
    if(board.checkSequencePentago(x,y)){
        winner = this->gameManager.getCurrentPlayer()->getBallColor();
    }
    nextAction = ActionGame::ROTATE;
}

void Pentago::rotate(int miniBoard, Direction direction, QTcpSocket * player)
{
    if(isFinished()){
        throw PentagoException("la partie est terminé !");
    }
    if(player!=this->gameManager.getCurrentPlayer()->getPlayerSocket()){
        throw PentagoException("c'est à votre adversaire de jouer !");
    }
    if(nextAction!=ActionGame::ROTATE){
        throw PentagoException("il faut d'abord placer une bille sur le plateau !");
    }
    if(miniBoard < 1 || miniBoard > 4){
        throw PentagoException("le mini-plateau choisit est incorrecte !");
    }
    board.rotateMiniBoard(miniBoard, direction);
    switch(board.checkSequencePentagoAfterRotate(miniBoard)){
    case BallColor::BLACK:
        winner=BallColor::BLACK;
        break;
    case BallColor::WHITE:
        winner=BallColor::WHITE;
        break;
    }
    gameManager.nextPlayer();
    nextAction = ActionGame::PLAY;
}

bool Pentago::isFinished() const
{
    return winner!=BallColor::NONE || (board.lastPlay() && nextAction==ActionGame::PLAY);
}

bool Pentago::resultatEgalite() const{
    return winner==BallColor::NONE;
}

string Pentago::getWinnerName() {
    if(!isFinished()){
        throw PentagoException("error, la partie n'est pas terminé");
    }
    return gameManager.getNamePlayerByColor(winner);
}

BallColor Pentago::getWinnerBallColor()
{
    if(!isFinished()){
        throw PentagoException("error, la partie n'est pas terminé");
    }
    return winner;
}

QTcpSocket * Pentago::getWinnerSocket()
{
    if(!isFinished()){
        throw PentagoException("error, la partie n'est pas terminé");
    }
    return gameManager.getIdentifierPlayerByColor(winner);
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
