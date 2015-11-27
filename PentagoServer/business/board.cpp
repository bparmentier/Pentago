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

void Board::rotateMiniBoard(int miniBoardNum, Direction direction)
{
    int miniBoardColumn = miniBoardNum == 1 || miniBoardNum == 2 ? 0 : 3;
    int miniBoardLine = miniBoardNum == 1 || miniBoardNum == 3 ? 0 : 3;
    rotate(miniBoardColumn, miniBoardLine, direction);
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
            if(board[i][j].getBall().getColor() == BallColor::WHITE
                    || board[i][j].getBall().getColor() == BallColor::BLACK){
                suiteCinq = pentagoVerticale(i,j) || pentagoHorizontal(i,j)
                        || pentagoDiagonaleDroite(i,j) || pentagoDiagonaleGauche(i,j);
                if(suiteCinq){
                    if(board[i][j].getBall().getColor() == BallColor::WHITE){
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

void Board::rotate(int startColumn, int startLine, Direction direction){
    vector<vector<Hole>> boardCopy (3, vector<Hole>(3));
    for(int i = startColumn, icopy = 0; i<startColumn+3; i++, icopy++){
        for(int j = startLine, jcopy = 0; j<startLine+3; j++, jcopy++){
            boardCopy[icopy][jcopy] = board[i][j];
        }
    }
    for(int i = 0, icopy = startColumn; i < boardCopy.size(); i++, icopy++){
        for(int j = 0, jcopy = startLine; j < boardCopy.at(i).size(); j++, jcopy++){
            if (direction == Direction::CLOCKWISE) {
                board[icopy][jcopy] = boardCopy[boardCopy.at(i).size()-j-1][i];
            } else {
                board[icopy][jcopy] = boardCopy[j][boardCopy.at(i).size()-i-1];
            }
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
