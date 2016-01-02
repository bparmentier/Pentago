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
    PlayerColor playerColor;
    QVector<QVector<PlayerColor>> board;
    int line;
    int column;
    bool clockwise;
    QString error;

public:
    Message();
    Message(TypeMessage type);
    void setPlayerColor(PlayerColor color);
    void setBoard(QVector<QVector<PlayerColor>> board);
    void setLine(int line);
    void setColumn(int column);
    void setClockwiseRotation(bool clockwise);
    void setError(QString error);

    TypeMessage getType() const;
    PlayerColor getPlayerColor() const;
    QVector<QVector<PlayerColor>> getBoard() const;
    int getLine() const;
    int getColumn() const;
    bool isClockwiseRotation() const;
    QString getError() const;

};

inline QDataStream &operator<<( QDataStream &flux, const Message &message)
{
    flux << message.getType();
    switch (message.getType()) {
    case TypeMessage::READY:
        flux << message.getPlayerColor();
        break;
    case TypeMessage::PLAYER_TURN:
        flux << message.getPlayerColor();
        break;
    case TypeMessage::BOARD_UPDATE:
        flux << message.getBoard();
        break;
    case TypeMessage::PLAY:
        flux << message.getLine();
        flux << message.getColumn();
        break;
    case TypeMessage::ROTATE:
        flux << message.isClockwiseRotation();
        break;
    case TypeMessage::FINISHED:
        flux << message.getPlayerColor();
        break;
    case TypeMessage::ERROR:
        flux << message.getError();
        break;
    }

    return flux;
}

inline void operator>>( QDataStream &flux, Message & msg)
{
    TypeMessage type;
    flux >> type;

    msg = Message(type);
    switch (type) {
    case TypeMessage::READY:
    case TypeMessage::PLAYER_TURN:
    case TypeMessage::FINISHED:
        PlayerColor color;
        flux >> color;
        msg.setPlayerColor(color);
        break;
    case TypeMessage::BOARD_UPDATE:
    {
        QVector<QVector<PlayerColor>> board;
        flux >> board;
        msg.setBoard(board);
    }
        break;
    case TypeMessage::PLAY:
        int line, column;
        flux >> line >> column;
        msg.setLine(line);
        msg.setColumn(column);
        break;
    case TypeMessage::ROTATE:
        bool isClockwiseRotation;
        flux >> isClockwiseRotation;
        msg.setClockwiseRotation(isClockwiseRotation);
        break;
    case TypeMessage::ERROR:
        QString error;
        flux >> error;
        msg.setError(error);
        break;
    }
}


#endif // MESSAGE_H
