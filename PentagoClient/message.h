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
public:
    enum class GameAction {
        PLACE_BALL,
        ROTATE
    };

    Message();
    Message(TypeMessage type);
    void setPlayerColor(PlayerColor color);
    void setGameAction(GameAction action);
    void setBoard(QVector<QVector<PlayerColor>> board);
    void setLine(int line);
    void setColumn(int column);
    void setMiniBoardIndice(int indice);
    void setClockwiseRotation(bool clockwise);
    void setError(QString error);

    TypeMessage getType() const;
    PlayerColor getPlayerColor() const;
    GameAction getGameAction() const;
    QVector<QVector<PlayerColor>> getBoard() const;
    int getLine() const;
    int getColumn() const;
    int getMiniBoardIndice() const;
    bool isClockwiseRotation() const;
    QString getError() const;

private:
    TypeMessage type;
    PlayerColor playerColor;
    GameAction gameAction;
    QVector<QVector<PlayerColor>> board;
    int line;
    int column;
    int miniBoardIndice;
    bool clockwise;
    QString error;
};

inline QDataStream &operator<<( QDataStream &flux, const Message::GameAction &action)
{
    switch (action) {
    case Message::GameAction::PLACE_BALL:
        flux << 0;
        break;
    case Message::GameAction::ROTATE:
        flux << 1;
        break;
    }

    return flux;
}

inline void operator>>( QDataStream &flux, Message::GameAction &action)
{
    int actionId;
    flux >> actionId;
    switch (actionId) {
    case 0:
        action = Message::GameAction::PLACE_BALL;
        break;
    case 1:
        action = Message::GameAction::ROTATE;
        break;
    }
}

inline QDataStream &operator<<( QDataStream &flux, const Message &message)
{
    flux << message.getType();
    switch (message.getType()) {
    case TypeMessage::READY:
        flux << message.getPlayerColor();
        break;
    case TypeMessage::PLAYER_TURN:
        flux << message.getPlayerColor();
        flux << message.getGameAction();
        flux << message.getBoard();
        break;
    case TypeMessage::BOARD_UPDATE:
        flux << message.getBoard();
        break;
    case TypeMessage::PLAY:
        flux << message.getLine();
        flux << message.getColumn();
        break;
    case TypeMessage::ROTATE:
        flux << message.getMiniBoardIndice();
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
    case TypeMessage::FINISHED:
        {
            PlayerColor color;
            flux >> color;
            msg.setPlayerColor(color);
        }
        break;
    case TypeMessage::PLAYER_TURN:
        {
            PlayerColor color;
            Message::GameAction action;
            QVector<QVector<PlayerColor>> board;
            flux >> color;
            flux >> action;
            flux >> board;
            msg.setPlayerColor(color);
            msg.setGameAction(action);
            msg.setBoard(board);
        }
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
        int miniBoardIndice;
        bool isClockwiseRotation;
        flux >> miniBoardIndice;
        flux >> isClockwiseRotation;
        msg.setMiniBoardIndice(miniBoardIndice);
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
