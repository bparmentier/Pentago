#ifndef JOUEUR_H
#define JOUEUR_H

#include "type.h"
#include <string>

class Joueur
{

private:
    std::string nom;
    CouleurBille couleur;

public:
    Joueur(std::string nom, CouleurBille couleur);
    std::string getNom() const;
    CouleurBille getCouleurBille() const;

};

#endif // JOUEUR_H
