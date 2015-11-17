#ifndef PENTAGO_H
#define PENTAGO_H

#include "gestionnairejoueur.h"
#include "plateau.h"
#include <vector>

class Pentago
{

public:
    GestionnaireJoueur lesJoueurs;
    Plateau plateauJeu;
    bool finPartie;

public:
    Pentago(std::vector<Joueur> & tabJoueurs);
    void jouer(int x, int y);
    void tourner(int miniPlateau, Direction direction);
    bool estTerminer() const;
    bool resultatEgalite() const;
    std::string getNomGagnant();
    std::string getNomJoueurCourant();
    std::vector<std::vector<Trou>> getPlateau() const;

};

#endif // PENTAGO_H
