#include "player.h"

using namespace std;

Player::Player(string name, BallColor color, QTcpSocket * playerIdentifier):name(name), ballColor(color),
    playerIdentifier(playerIdentifier)
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

QTcpSocket *Player::getPlayerIdentifier() const
{
    return playerIdentifier;
}
