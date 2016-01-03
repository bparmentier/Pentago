#include "message.h"

Message::Message()
{
}

Message::Message(TypeMessage type)
{
    this->type = type;
}

void Message::setPlayerColor(PlayerColor color)
{
    if (type != TypeMessage::READY
            && type != TypeMessage::PLAYER_TURN
            && type != TypeMessage::FINISHED) {
        throw std::logic_error("The message does not support this parameter");
    }
    this->playerColor = color;
}

void Message::setGameAction(GameAction action)
{
    if (type != TypeMessage::PLAYER_TURN) {
        throw std::logic_error("The message does not support this parameter");
    }
    this->gameAction = action;
}

void Message::setBoard(QVector<QVector<PlayerColor>> board)
{
    if (type != TypeMessage::BOARD_UPDATE
            && type != TypeMessage::PLAYER_TURN
            && type != TypeMessage::FINISHED) {
        throw std::logic_error("The message does not support this parameter");
    }
    this->board = board;
}

void Message::setLine(int line)
{
    if (type != TypeMessage::PLAY) {
        throw std::logic_error("The message does not support this parameter");
    }
    this->line = line;
}

void Message::setColumn(int column)
{
    if (type != TypeMessage::PLAY) {
        throw std::logic_error("The message does not support this parameter");
    }
    this->column = column;
}

void Message::setMiniBoardIndice(int indice)
{
    if (type != TypeMessage::ROTATE) {
        throw std::logic_error("The message does not support this parameter");
    }
    this->miniBoardIndice = indice;
}

void Message::setClockwiseRotation(bool clockwise)
{
    if (type != TypeMessage::ROTATE) {
        throw std::logic_error("The message does not support this parameter");
    }
    this->clockwise = clockwise;
}

void Message::setError(QString error)
{
    if (type != TypeMessage::ERROR) {
        throw std::logic_error("The message does not support this parameter");
    }
    this->error = error;
}

TypeMessage Message::getType() const
{
    return type;
}

PlayerColor Message::getPlayerColor() const
{
    if (type != TypeMessage::READY
            && type != TypeMessage::PLAYER_TURN
            && type != TypeMessage::FINISHED) {
        throw std::logic_error("The message does not have this attribute");
    }
    return playerColor;
}

Message::GameAction Message::getGameAction() const
{
    if (type != TypeMessage::PLAYER_TURN) {
        throw std::logic_error("The message does not have this attribute");
    }
    return gameAction;
}

QVector<QVector<PlayerColor>> Message::getBoard() const
{
    if (type != TypeMessage::BOARD_UPDATE
            && type != TypeMessage::PLAYER_TURN
            && type != TypeMessage::FINISHED) {
        throw std::logic_error("The message does not have this attribute");
    }
    return board;
}

int Message::getLine() const
{
    if (type != TypeMessage::PLAY) {
        throw std::logic_error("The message does not have this attribute");
    }
    return line;
}

int Message::getColumn() const
{
    if (type != TypeMessage::PLAY) {
        throw std::logic_error("The message does not have this attribute");
    }
    return column;
}

int Message::getMiniBoardIndice() const
{
    if (type != TypeMessage::ROTATE) {
        throw std::logic_error("The message does not have this attribute");
    }
    return miniBoardIndice;
}

bool Message::isClockwiseRotation() const
{
    if (type != TypeMessage::ROTATE) {
        throw std::logic_error("The message does not have this attribute");
    }
    return clockwise;
}

QString Message::getError() const
{
    if (type != TypeMessage::ERROR) {
        throw std::logic_error("The message does not have this attribute");
    }
    return error;
}
