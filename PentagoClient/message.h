#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <QtNetwork>
#include "type.h"
#include <string>

class Message
{
private:
    TypeMessage type;

    int row;
    int column;
    QString color;

    int miniBoard;
    QChar direction;

    bool winner;

    bool yourTurn;
public:
    Message();
    Message(TypeMessage type, int row, int colum, QString color,
            int miniBoard, QChar direction, bool winner, bool yourTurn);
    TypeMessage getType() const;
    int getRow() const;
    int getColumn() const;
    QString getColor() const;
    int getBoard() const;
    QChar getDirection() const;
    bool getWinner() const;
    bool getTurn() const;
};

inline QDataStream &operator<<( QDataStream &flux, Message const& msg)
{
    flux << msg.getType();
    flux << msg.getRow();
    flux << msg.getColumn();
    flux << msg.getColor();
    flux << msg.getBoard();
    flux << msg.getDirection();
    flux << msg.getWinner();
    flux << msg.getTurn();
    return flux;
}

inline void operator>>( QDataStream &flux, Message & msg)
{
    TypeMessage type;
    int row, colum, miniBoard;
    QString color;
    QChar direction;
    bool winner, yourTurn;

    flux >> type;
    flux >> row;
    flux >> colum;
    flux >> color;
    flux >> miniBoard;
    flux >> direction;
    flux >> winner;
    flux >> yourTurn;
    msg = Message(type,row,colum,color,miniBoard,direction,winner,yourTurn);
}

#endif // MESSAGE_H
