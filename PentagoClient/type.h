#ifndef TYPE_H
#define TYPE_H

#include <QDataStream>

/*!
 * brief The TypeMessage enum Defines the type of a message
 */
enum class TypeMessage {
    READY,                  /*!< To indicate that the server is ready to process user requests */
    PLAYER_TURN,            /*!< To indicate who will play next */
    BOARD_UPDATE,           /*!< To indicate that the message contains a board update */
    PLAY,                   /*!< To indicate that the message contains an action to place a ball */
    ROTATE,                 /*!< To indicate that the message contains a request to rotate a quadrant */
    FINISHED,               /*!< To indicate to the clients that the game is over */
    ERROR                   /*!< To indicate that a request from a client has resulted in an error */
};

/*!
 * \brief operator << Injects a TypeMessage into a QDataStream
 * \param flux the output object
 * \param type the input TypeMessage object
 * \return
 */
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

/*!
 * \brief operator >> Unboxes a QDataStream into a TypeMessage
 * \param flux the input object
 * \param type the output object
 */
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
