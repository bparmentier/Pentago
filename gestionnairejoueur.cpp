#include "gestionnairejoueur.h"
#include <iostream>

GestionnaireJoueur::GestionnaireJoueur(std::vector<Joueur> &tabJoueurs):indiceCourant(0)
{
    for(int i = 0; i<tabJoueurs.size();i++){
        this->tabJoueurs.push_back(Joueur(tabJoueurs[i]));
    }
}

Joueur * GestionnaireJoueur::getJoueurCourant()
{
    return &(tabJoueurs.at(indiceCourant));
}

void GestionnaireJoueur::joueurSuivant()
{
    indiceCourant = ((indiceCourant + 1)%tabJoueurs.size());
}

