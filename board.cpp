#include "board.h"
#include "pentagoexception.h"

using namespace std;

Board::Board():board(6, vector<Hole>(6,Hole())), nombreCoup(0)
{
}


void Board::placeBall(int x, int y, Player * player)
{
    if(x < 0 || x > board.size() || y < 0 || y > board.at(0).size()){
        throw PentagoException("la position choisie est invalide !");
    }
    if(board[x][y].isOccupied()){
        throw PentagoException("la position choisie est occupée !");
    }
    board[x][y].setBall(Ball(player->getBallColor()));
    board[x][y].setPlayer(player);
    nombreCoup++;
}

void Board::rotateMiniBoard(int numMiniPlateau, Direction direction)
{
    int posMiniPlaX = numMiniPlateau==1 || numMiniPlateau==2 ? 0 : 3;
    int posMiniPlaY = numMiniPlateau==1 || numMiniPlateau==3 ? 0 : 3;
    if(direction==COUNTERCLOCKWISE){
        rotateCounterclockwise(posMiniPlaX,posMiniPlaY);
    }else{
        rotateClockwise(posMiniPlaX,posMiniPlaY);
    }
}

vector<vector<Hole> > Board::getBoard() const
{
    return board;
}

BallColor Board::getColor(int x, int y) const
{
    return board[x][y].getBall().getColor();
}

Player * Board::getJoueurTrou(int x, int y) const
{
    return board[x][y].getPlayer();
}

bool Board::isHoleOccupied(int x, int y) const
{
    return board[x][y].isOccupied();
}

bool Board::verifierSuitePion(int x, int y)
{
    bool suiteCinq = pentagoVerticale(x,y) || pentagoHorizontal(x,y)
            || pentagoDiagonaleDroite(x,y) || pentagoDiagonaleGauche(x,y);
    return suiteCinq;
}

bool Board::verifierSuitePionApresTour(int numMiniPlateau)
{
    int posMiniPlaX = numMiniPlateau==1 || numMiniPlateau==2 ? 0 : 3;
    int posMiniPlaY = numMiniPlateau==1 || numMiniPlateau==3 ? 0 : 3;
    bool suiteCinq = false;
    bool blanche = false;
    bool noir = false;
    for(int i = posMiniPlaX; i<posMiniPlaX+3 && (!blanche || !noir); i++){
        for(int j = posMiniPlaY; j<posMiniPlaY+3 && (!blanche || !noir); j++){
            if(board[i][j].getBall().getColor() == WHITE
                    || board[i][j].getBall().getColor() == BLACK){
                suiteCinq = pentagoVerticale(i,j) || pentagoHorizontal(i,j)
                        || pentagoDiagonaleDroite(i,j) || pentagoDiagonaleGauche(i,j);
                if(suiteCinq){
                    if(board[i][j].getBall().getColor() == WHITE){
                        blanche = true;
                    }else{
                        noir = true;
                    }
                }
            }
        }
    }
    return suiteCinq;
}

bool Board::dernierCoup()const
{
    return nombreCoup == (board.size()* board.size());
}

void Board::rotateClockwise(int x, int y){
    vector<vector<Hole>> platCopie (3, vector<Hole>(3));
    for(int i = x, icopie = 0; i<x+3; i++, icopie++){
        for(int j = y, jcopie = 0; j<y+3; j++, jcopie++){
            platCopie[icopie][jcopie] = board[i][j];
        }
    }
    for(int i = 0, icopie = x; i<platCopie.size(); i++, icopie++){
        for(int j = 0, jcopie = y; j<platCopie.at(i).size(); j++, jcopie++){
            board[icopie][jcopie] = platCopie[platCopie.at(i).size()-j-1][i];
        }
    }
}

void Board::rotateCounterclockwise(int x, int y){
    vector<vector<Hole>> platCopie (3, vector<Hole>(3));
    for(int i = x, icopie = 0; i<x+3; i++, icopie++){
        for(int j = y, jcopie = 0; j<y+3; j++, jcopie++){
            platCopie[icopie][jcopie] = board[i][j];
        }
    }
    for(int i = 0, icopie = x; i<platCopie.size(); i++, icopie++){
        for(int j = 0, jcopie = y; j<platCopie.at(i).size(); j++, jcopie++){
            board[icopie][jcopie] = platCopie[j][platCopie.at(i).size()-i-1];
        }
    }
}

bool Board::pentagoVerticale(int x, int y){
    int nbMemeBille = 1;
    int i = x+1;
    while(i < board.size() && nbMemeBille < 5
          && board[i][y] == board[x][y] ){
        nbMemeBille++;
        i++;
    }
    if(nbMemeBille<5){
        i = x-1;
        while(i >= 0 && nbMemeBille < 5
              && board[i][y] == board[x][y] ){
            nbMemeBille++;
            i--;
        }
    }
    return nbMemeBille == 5;
}

bool Board::pentagoHorizontal(int x, int y){
    int nbMemeBille = 1;
    int i = y+1;
    while(i < board[x].size() && nbMemeBille < 5
          && board[x][i] == board[x][y]){
        nbMemeBille++;
        i++;
    }
    if(nbMemeBille<5){
        i = y-1;
        while(i >= 0 && nbMemeBille < 5
              && board[x][i] == board[x][y]){
            nbMemeBille++;
            i--;
        }
    }
    return nbMemeBille == 5;
}

bool Board::pentagoDiagonaleDroite(int x, int y){
    int nbMemeBille = 1;
    int i = x-1 , j = y+1;
    while(i>=0 && j < board[i].size() && nbMemeBille < 5
          && board[i][j] == board[x][y]){
        i--;
        j++;
        nbMemeBille++;
    }
    if(nbMemeBille<5){
        i = x+1;
        j = y-1;
        while(i < board.size() && j >= 0 && nbMemeBille < 5
              && board[i][j] == board[x][y]){
            i++;
            j--;
            nbMemeBille++;
        }
    }
    return nbMemeBille == 5;
}

bool Board::pentagoDiagonaleGauche(int x, int y){
    int nbMemeBille = 1;
    int i = x+1 , j = y+1;
    while(i<board.size() && j < board[i].size() && nbMemeBille < 5
          && board[i][j] == board[x][y]){
        i++;
        j++;
        nbMemeBille++;
    }
    if(nbMemeBille<5){
        i = x-1;
        j = y-1;
        while(i >= 0 && j >= 0 && board[i][j] == board[x][y]
              && nbMemeBille < 5){
            i--;
            j--;
            nbMemeBille++;
        }
    }
    return nbMemeBille == 5;
}
