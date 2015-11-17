#ifndef PLATEAU_H
#define PLATEAU_H

#include <vector>
#include "trou.h"
#include "type.h"

class Plateau
{

private:
    std::vector<std::vector<Trou>> plateau;
    int nombreCoup;

public:
    Plateau();
    void placerBille(int x, int y, Joueur *joueur);
    void tournerMiniPlateau(int numMiniPlateau, Direction direction);
    std::vector<std::vector<Trou>> getPlateau() const;
    CouleurBille getCouleurBille(int x, int y) const;
    Joueur * getJoueurTrou(int x, int y) const;
    bool getTrouEstOccupe(int x, int y) const;
    bool verifierSuitePion(int x, int y);
    bool verifierSuitePionApresTour(int numMiniPlateau);
    bool dernierCoup() const;

private:
    void rotationHorlogique(int x, int y);
    void rotationAntiHorlogique(int x, int y);
    bool pentagoVerticale(int x, int y);
    bool pentagoHorizontal(int x, int y);
    bool pentagoDiagonaleDroite(int x, int y);
    bool pentagoDiagonaleGauche(int x, int y);
};

#endif // PLATEAU_H
