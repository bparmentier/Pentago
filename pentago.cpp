#include "pentago.h"
#include "pentagoexception.h"
#include <iostream>

using namespace std;

Pentago::Pentago(vector<Joueur> & tabJoueurs):lesJoueurs(tabJoueurs), plateauJeu(),
    finPartie(false)
{
}

void Pentago::jouer(int x, int y)
{
    if(finPartie == true){
        throw PentagoException("La partie est terminée !");
    }
    this->plateauJeu.placerBille(x,y,lesJoueurs.getJoueurCourant());
    finPartie = plateauJeu.verifierSuitePion(x,y);
}

void Pentago::tourner(int miniPlateau, Direction direction)
{
    if(finPartie == true){
        throw string("la partie est terminé !");
    }
    if(miniPlateau < 1 || miniPlateau > 4){
        throw PentagoException("le mini-plateau choisit est incorrecte !");
    }
    plateauJeu.tournerMiniPlateau(miniPlateau, direction);
    finPartie = plateauJeu.verifierSuitePionApresTour(miniPlateau);
    if(!finPartie){
        lesJoueurs.joueurSuivant();
    }
}

bool Pentago::estTerminer() const
{
    return finPartie || plateauJeu.dernierCoup();
}

bool Pentago::resultatEgalite() const{
    return plateauJeu.dernierCoup();
}

string Pentago::getNomGagnant() {
    if(!finPartie){
        throw string("error, la partie n'est pas terminé");
    }
    return lesJoueurs.getJoueurCourant()->getNom();
}

string Pentago::getNomJoueurCourant()
{
    return lesJoueurs.getJoueurCourant()->getNom();
}

vector<vector<Trou> > Pentago::getPlateau() const
{
    return plateauJeu.getPlateau();
}
