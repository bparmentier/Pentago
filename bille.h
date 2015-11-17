#ifndef BILLE_H
#define BILLE_H

#include "type.h"

class Bille
{

private:
    CouleurBille couleur;

public:
    Bille(CouleurBille couleur);
    CouleurBille getCouleurBille() const;

};

#endif // BILLE_H
