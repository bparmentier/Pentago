#include "message.h"

Message::Message(){

}

Message::Message(TypeMessage type, int row, int column, QString color,
        int miniBoard, QChar direction, bool winner, bool yourTurn){
    this->type = type;
    this->row = row;
    this->column = column;
    this->color = color;
    this->miniBoard = miniBoard;
    this->direction = direction;
    this->winner = winner;
    this->yourTurn = yourTurn;
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

QString Message::getColor() const{
    return color;
}

int Message::getBoard() const{
    return miniBoard;
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
