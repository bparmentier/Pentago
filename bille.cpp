#include "bille.h"


Bille::Bille(CouleurBille couleur):couleur(couleur)
{
}

CouleurBille Bille::getCouleurBille() const
{
    return couleur;
}

