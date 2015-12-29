#include "message.h"
Message::Message(){

}

Message::Message(TypeMessage type, PlayerColor color, int row, int column,
        int miniBoard, QChar direction, bool winner, bool yourTurn, QVector<QVector<PlayerColor>> board){
    this->type = type;
    this->row = row;
    this->column = column;
    this->color = color;
    this->miniBoard = miniBoard;
    this->direction = direction;
    this->winner = winner;
    this->yourTurn = yourTurn;
    this->board = board;
}
Message::Message(TypeMessage type,PlayerColor color):
    type{type},color{color}
{
}
Message::Message(TypeMessage type, QVector<QVector<PlayerColor>> board):
    type{type},board{board}
{
}
TypeMessage Message::getType() const{
    return type;
}

int Message::getRow() const{
    return row;
}

int Message::getColumn() const{
    return column;
}

PlayerColor Message::getColor() const{
    return color;
}

int Message::getMiniBoard() const{
    return miniBoard;
}
QVector<QVector<PlayerColor>> Message::getBoard()const{
    return board;
}

QChar Message::getDirection() const{
    return direction;
}

bool Message::getWinner() const{
    return winner;
}

bool Message::getTurn() const{
    return yourTurn;
}
QVector<QVector<PlayerColor>> Message::convertBoard(std::vector<std::vector<Hole>> &vec){
    QVector<QVector<PlayerColor>> newVec(6,QVector<PlayerColor>(6));
    for(unsigned i = 0;i<vec.size();i++){
        for(unsigned j = 0;j < vec.at(0).size();j++){
            BallColor tmp = vec.at(i).at(j).getBall().getColor();
            switch(tmp){
            case BallColor::BLACK:
                newVec[i][j] = PlayerColor::BLACK;
                break;
            case BallColor::WHITE:
                newVec[i][j] = PlayerColor::WHITE;
                break;
            case BallColor::NONE:
                newVec[i][j] = PlayerColor::NONE;
                break;
            }
        }
    }
    return newVec;
}

