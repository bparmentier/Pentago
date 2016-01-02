#ifndef TYPE_H
#define TYPE_H

#include <QDataStream>

enum class TypeMessage {
    READY,
    PLAYER_TURN,
    BOARD_UPDATE,
    PLAY,
    ROTATE,
    FINISHED,
    ERROR
};

inline QDataStream &operator<<( QDataStream &flux, TypeMessage const& type)
{
    switch (type) {
    case TypeMessage::READY:
        flux << 0;
        break;
    case TypeMessage::PLAYER_TURN:
        flux << 1;
        break;
    case TypeMessage::BOARD_UPDATE:
        flux << 2;
        break;
    case TypeMessage::PLAY:
        flux << 3;
        break;
    case TypeMessage::ROTATE:
        flux << 4;
        break;
    case TypeMessage::FINISHED:
        flux << 5;
        break;
    case TypeMessage::ERROR:
        flux << 6;
        break;
    }
    return flux;
}

inline void operator>>( QDataStream &flux, TypeMessage & type)
{
    int number;
    flux >> number;
    switch(number){
    case 0:
        type = TypeMessage::READY;
        break;
    case 1:
        type = TypeMessage::PLAYER_TURN;
        break;
    case 2:
        type = TypeMessage::BOARD_UPDATE;
        break;
    case 3:
        type = TypeMessage::PLAY;
        break;
    case 4:
        type = TypeMessage::ROTATE;
        break;
    case 5:
        type = TypeMessage::FINISHED;
        break;
    case 6:
        type = TypeMessage::ERROR;
        break;
    }
}
#endif // TYPE_H
