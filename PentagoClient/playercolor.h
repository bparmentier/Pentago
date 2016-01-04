#ifndef BALLCOLOR
#define BALLCOLOR

#include <QDataStream>

enum class PlayerColor {
    WHITE,  /*!< White player */
    BLACK,  /*!< Black player */
    NONE    /*!< Neither black, nor white player */
};

inline QDataStream &operator<<(QDataStream &flux, PlayerColor const& color)
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

inline void operator>>(QDataStream &flux, PlayerColor & color)
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
#endif // BALLCOLOR

