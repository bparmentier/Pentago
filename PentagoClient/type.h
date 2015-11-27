#ifndef TYPE_H
#define TYPE_H

#include <QDataStream>

enum class TypeMessage {
    PLAY,
    ROTATE,
    PLAY_STATE,
    ROTATE_STATE,
    FINAL_STATE,
    BEGIN_STATE,
    ERROR
};

inline QDataStream &operator<<( QDataStream &flux, TypeMessage const& type)
{
    switch(type){
    case TypeMessage::PLAY:
        flux << 1;
        break;
    case TypeMessage::ROTATE:
        flux << 2;
        break;
    case TypeMessage::PLAY_STATE:
        flux << 3;
        break;
    case TypeMessage::ROTATE_STATE:
        flux << 4;
        break;
    case TypeMessage::FINAL_STATE:
        flux << 5;
        break;
    case TypeMessage::BEGIN_STATE:
        flux << 6;
        break;
    case TypeMessage::ERROR:
        flux << 7;
        break;
    }
    return flux;
}

inline void operator>>( QDataStream &flux, TypeMessage & type)
{
    int number;
    flux >> number;
    switch(number){
    case 1:
        type = TypeMessage::PLAY;
        break;
    case 2:
        type = TypeMessage::ROTATE;
        break;
    case 3:
        type = TypeMessage::PLAY_STATE;
        break;
    case 4:
        type = TypeMessage::ROTATE_STATE;
        break;
    case 5:
        type = TypeMessage::FINAL_STATE;
        break;
    case 6:
        type = TypeMessage::BEGIN_STATE;
        break;
    case 7:
        type = TypeMessage::ERROR;
        break;
    }
}
#endif // TYPE_H
