#include "player.h"

using namespace std;

Player::Player(string name, BallColor color):name(name), ballColor(color)
{
}

string Player::getName() const
{
    return name;
}

BallColor Player::getBallColor() const
{
    return ballColor;
}
