#ifndef PLAYERCOLOR_H
#define PLAYERCOLOR_H
#include <QDataStream>
///
/// \brief The PlayerColor enum
/// The color of a player's marble
///
enum class PlayerColor {
    WHITE,    /*!< White marble */
    BLACK,       /*!< Black marble */
    NONE        /*!< Absence of a marble */
};

///
/// \brief operator << injects a PlayerColor into a QDataStream object to be sent on the network
/// \param flux the output stream
/// \param color the input color
/// \return
///
inline QDataStream &operator<<( QDataStream &flux, PlayerColor const& color)
{
    switch(color){
    case PlayerColor::WHITE:
        flux << 1;
        break;
    case PlayerColor::BLACK:
        flux << 2;
        break;
    case PlayerColor::NONE:
        flux << 3;
        break;
    }
    return flux;
}
///
/// \brief operator >> unboxes a QDataStream into a PlayerColor
/// \param flux the input stream
/// \param color the ouput PlayerColor
///
inline void operator>>( QDataStream &flux, PlayerColor & color)
{
    int number;
    flux >> number;
    switch(number){
    case 1:
        color = PlayerColor::WHITE;
        break;
    case 2:
        color = PlayerColor::BLACK;
        break;
    case 3:
        color = PlayerColor::NONE;
        break;
}
}

#endif // PLAYERCOLOR

