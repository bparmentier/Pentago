#include "joueur.h"

using namespace std;

Joueur::Joueur(string nom, CouleurBille couleur):nom(nom), couleur(couleur)
{
}

string Joueur::getNom() const
{
    return nom;
}

CouleurBille Joueur::getCouleurBille() const
{
    return couleur;
}
