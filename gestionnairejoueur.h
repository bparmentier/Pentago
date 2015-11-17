#ifndef GESTIONNAIREJOUEUR_H
#define GESTIONNAIREJOUEUR_H

#include <vector>
#include "joueur.h"
class GestionnaireJoueur
{
private:
    std::vector<Joueur> tabJoueurs;
    int indiceCourant;
public:
    GestionnaireJoueur(std::vector<Joueur> & tabJoueurs);
    Joueur *getJoueurCourant();
    void joueurSuivant();
};

#endif // GESTIONNAIREJOUEUR_H
