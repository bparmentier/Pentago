#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <QtNetwork>
#include "type.h"
#include <string>
#include <QVector>
#include "playercolor.h"

class Message
{
private:
    TypeMessage type;

    int row;
    int column;
    PlayerColor color;
    int miniBoard;
    QChar direction;
    QVector<QVector<QChar>> board;
    bool winner;
    bool yourTurn;
public:
    Message();
    Message(TypeMessage type,PlayerColor color,int row, int colum,
            int miniBoard, QChar direction, bool winner, bool yourTurn,QVector<QVector<QChar>> board);
    Message(TypeMessage type,PlayerColor color);
    Message(TypeMessage type,QVector<QVector<QChar>> board);
    //Message(TypeMessage type,QList)
    TypeMessage getType() const;
    int getRow() const;
    int getColumn() const;
    PlayerColor getColor() const;
    int getMiniBoard() const;
    QVector<QVector<QChar>> getBoard() const;
    QChar getDirection() const;
    bool getWinner() const;
    bool getTurn() const;
};

inline QDataStream &operator<<( QDataStream &flux, const Message & msg)
{
    flux << msg.getType();
    flux << msg.getColor();
    flux << msg.getRow();
    flux << msg.getColumn();
    flux << msg.getBoard();
    flux << msg.getDirection();
    flux << msg.getBoard();
    flux << msg.getWinner();
    flux << msg.getTurn();
    return flux;
}

inline void operator>>( QDataStream &flux, Message & msg)
{
    TypeMessage type;
    PlayerColor color;
    int row, colum, miniBoard;
    QChar direction;
    bool winner, yourTurn;
    QVector<QVector<QChar>> board;

    flux >> type;
    flux >> color;
    flux >> row;
    flux >> colum;
    flux >> miniBoard;
    flux >> direction;
    flux >> board;
    flux >> winner;
    flux >> yourTurn;
    msg = Message(type,color,row,colum,miniBoard,direction,winner,yourTurn,board);
}

#endif // MESSAGE_H
