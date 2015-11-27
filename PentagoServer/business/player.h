#ifndef JOUEUR_H
#define JOUEUR_H

#include "ballcolor.h"
#include <string>

class Player
{

private:
    std::string name;
    BallColor ballColor;

public:
    Player(std::string name, BallColor color);
    std::string getName() const;
    BallColor getBallColor() const;

};

#endif // JOUEUR_H
