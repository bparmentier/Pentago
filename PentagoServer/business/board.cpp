#include "board.h"
#include "pentagoexception.h"

using namespace std;

Board::Board():board(6, vector<Hole>(6,Hole())), playNumber(0)
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
    playNumber++;
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

bool Board::checkSequencePentago(int x, int y)
{
    bool fiveSequence = pentagoVertical(x,y) || pentagoHorizontal(x,y)
            || pentagoRightDiagonal(x,y) || pentagoLeftDiagonal(x,y);
    return fiveSequence;
}

BallColor Board::checkSequencePentagoAfterRotate(int numMiniBoard)
{
    int posMiniBoardX = numMiniBoard==1 || numMiniBoard==2 ? 0 : 3;
    int posMiniBoardY = numMiniBoard==1 || numMiniBoard==3 ? 0 : 3;
    bool fiveSequence = false;
    for(int i = posMiniBoardX; i<posMiniBoardX+3; i++){
        for(int j = posMiniBoardY; j<posMiniBoardY+3; j++){
            if(board[i][j].getBall().getColor() == BallColor::WHITE
                    || board[i][j].getBall().getColor() == BallColor::BLACK){
                fiveSequence = checkSequencePentago(i,j);
                if(fiveSequence){
                    return board[i][j].getBall().getColor();
                }
            }
        }
    }
    return BallColor::NONE;
}

bool Board::lastPlay()const
{
    return playNumber == (board.size()* board.size());
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

bool Board::pentagoVertical(int x, int y){
    int nbSaleBall = 1;
    int i = x+1;
    while(i < board.size() && nbSaleBall < 5
          && board[i][y] == board[x][y] ){
        nbSaleBall++;
        i++;
    }
    if(nbSaleBall<5){
        i = x-1;
        while(i >= 0 && nbSaleBall < 5
              && board[i][y] == board[x][y] ){
            nbSaleBall++;
            i--;
        }
    }
    return nbSaleBall == 5;
}

bool Board::pentagoHorizontal(int x, int y){
    int nbSameBall = 1;
    int i = y+1;
    while(i < board[x].size() && nbSameBall < 5
          && board[x][i] == board[x][y]){
        nbSameBall++;
        i++;
    }
    if(nbSameBall<5){
        i = y-1;
        while(i >= 0 && nbSameBall < 5
              && board[x][i] == board[x][y]){
            nbSameBall++;
            i--;
        }
    }
    return nbSameBall == 5;
}

bool Board::pentagoRightDiagonal(int x, int y){
    int nbSameBall = 1;
    int i = x-1 , j = y+1;
    while(i>=0 && j < board[i].size() && nbSameBall < 5
          && board[i][j] == board[x][y]){
        i--;
        j++;
        nbSameBall++;
    }
    if(nbSameBall<5){
        i = x+1;
        j = y-1;
        while(i < board.size() && j >= 0 && nbSameBall < 5
              && board[i][j] == board[x][y]){
            i++;
            j--;
            nbSameBall++;
        }
    }
    return nbSameBall == 5;
}

bool Board::pentagoLeftDiagonal(int x, int y){
    int nbSameBall = 1;
    int i = x+1 , j = y+1;
    while(i<board.size() && j < board[i].size() && nbSameBall < 5
          && board[i][j] == board[x][y]){
        i++;
        j++;
        nbSameBall++;
    }
    if(nbSameBall<5){
        i = x-1;
        j = y-1;
        while(i >= 0 && j >= 0 && board[i][j] == board[x][y]
              && nbSameBall < 5){
            i--;
            j--;
            nbSameBall++;
        }
    }
    return nbSameBall == 5;
}
