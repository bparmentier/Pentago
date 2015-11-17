#include "plateau.h"
#include "pentagoexception.h"

using namespace std;

Plateau::Plateau():plateau(6, vector<Trou>(6,Trou())), nombreCoup(0)
{
}


void Plateau::placerBille(int x, int y, Joueur * joueur)
{
    if(x < 0 || x > plateau.size() || y < 0 || y > plateau.at(0).size()){
        throw PentagoException("la position choisie est invalide !");
    }
    if(plateau[x][y].estOccupe()){
        throw PentagoException("la position choisie est occupée !");
    }
    plateau[x][y].setBilleTrou(Bille(joueur->getCouleurBille()));
    plateau[x][y].setJoueurTrou(joueur);
    nombreCoup++;
}

void Plateau::tournerMiniPlateau(int numMiniPlateau, Direction direction)
{
    int posMiniPlaX = numMiniPlateau==1 || numMiniPlateau==2 ? 0 : 3;
    int posMiniPlaY = numMiniPlateau==1 || numMiniPlateau==3 ? 0 : 3;
    if(direction==VERS_LE_BAS){
        rotationAntiHorlogique(posMiniPlaX,posMiniPlaY);
    }else{
        rotationHorlogique(posMiniPlaX,posMiniPlaY);
    }
}

vector<vector<Trou> > Plateau::getPlateau() const
{
    return plateau;
}

CouleurBille Plateau::getCouleurBille(int x, int y) const
{
    return plateau[x][y].getBilleTrou().getCouleurBille();
}

Joueur * Plateau::getJoueurTrou(int x, int y) const
{
    return plateau[x][y].getJoueurTrou();
}

bool Plateau::getTrouEstOccupe(int x, int y) const
{
    return plateau[x][y].estOccupe();
}

bool Plateau::verifierSuitePion(int x, int y)
{
    bool suiteCinq = pentagoVerticale(x,y) || pentagoHorizontal(x,y)
            || pentagoDiagonaleDroite(x,y) || pentagoDiagonaleGauche(x,y);
    return suiteCinq;
}

bool Plateau::verifierSuitePionApresTour(int numMiniPlateau)
{
    int posMiniPlaX = numMiniPlateau==1 || numMiniPlateau==2 ? 0 : 3;
    int posMiniPlaY = numMiniPlateau==1 || numMiniPlateau==3 ? 0 : 3;
    bool suiteCinq = false;
    bool blanche = false;
    bool noir = false;
    for(int i = posMiniPlaX; i<posMiniPlaX+3 && (!blanche || !noir); i++){
        for(int j = posMiniPlaY; j<posMiniPlaY+3 && (!blanche || !noir); j++){
            if(plateau[i][j].getBilleTrou().getCouleurBille() == BLANCHE
                    || plateau[i][j].getBilleTrou().getCouleurBille() == NOIR){
                suiteCinq = pentagoVerticale(i,j) || pentagoHorizontal(i,j)
                        || pentagoDiagonaleDroite(i,j) || pentagoDiagonaleGauche(i,j);
                if(suiteCinq){
                    if(plateau[i][j].getBilleTrou().getCouleurBille() == BLANCHE){
                        blanche = true;
                    }else{
                        noir = true;
                    }
                }
            }
        }
    }
    return suiteCinq;
}

bool Plateau::dernierCoup()const
{
    return nombreCoup == (plateau.size()* plateau.size());
}

void Plateau::rotationHorlogique(int x, int y){
    vector<vector<Trou>> platCopie (3, vector<Trou>(3));
    for(int i = x, icopie = 0; i<x+3; i++, icopie++){
        for(int j = y, jcopie = 0; j<y+3; j++, jcopie++){
            platCopie[icopie][jcopie] = plateau[i][j];
        }
    }
    for(int i = 0, icopie = x; i<platCopie.size(); i++, icopie++){
        for(int j = 0, jcopie = y; j<platCopie.at(i).size(); j++, jcopie++){
            plateau[icopie][jcopie] = platCopie[platCopie.at(i).size()-j-1][i];
        }
    }
}

void Plateau::rotationAntiHorlogique(int x, int y){
    vector<vector<Trou>> platCopie (3, vector<Trou>(3));
    for(int i = x, icopie = 0; i<x+3; i++, icopie++){
        for(int j = y, jcopie = 0; j<y+3; j++, jcopie++){
            platCopie[icopie][jcopie] = plateau[i][j];
        }
    }
    for(int i = 0, icopie = x; i<platCopie.size(); i++, icopie++){
        for(int j = 0, jcopie = y; j<platCopie.at(i).size(); j++, jcopie++){
            plateau[icopie][jcopie] = platCopie[j][platCopie.at(i).size()-i-1];
        }
    }
}

bool Plateau::pentagoVerticale(int x, int y){
    int nbMemeBille = 1;
    int i = x+1;
    while(i < plateau.size() && nbMemeBille < 5
          && plateau[i][y] == plateau[x][y] ){
        nbMemeBille++;
        i++;
    }
    if(nbMemeBille<5){
        i = x-1;
        while(i >= 0 && nbMemeBille < 5
              && plateau[i][y] == plateau[x][y] ){
            nbMemeBille++;
            i--;
        }
    }
    return nbMemeBille == 5;
}

bool Plateau::pentagoHorizontal(int x, int y){
    int nbMemeBille = 1;
    int i = y+1;
    while(i < plateau[x].size() && nbMemeBille < 5
          && plateau[x][i] == plateau[x][y]){
        nbMemeBille++;
        i++;
    }
    if(nbMemeBille<5){
        i = y-1;
        while(i >= 0 && nbMemeBille < 5
              && plateau[x][i] == plateau[x][y]){
            nbMemeBille++;
            i--;
        }
    }
    return nbMemeBille == 5;
}

bool Plateau::pentagoDiagonaleDroite(int x, int y){
    int nbMemeBille = 1;
    int i = x-1 , j = y+1;
    while(i>=0 && j < plateau[i].size() && nbMemeBille < 5
          && plateau[i][j] == plateau[x][y]){
        i--;
        j++;
        nbMemeBille++;
    }
    if(nbMemeBille<5){
        i = x+1;
        j = y-1;
        while(i < plateau.size() && j >= 0 && nbMemeBille < 5
              && plateau[i][j] == plateau[x][y]){
            i++;
            j--;
            nbMemeBille++;
        }
    }
    return nbMemeBille == 5;
}

bool Plateau::pentagoDiagonaleGauche(int x, int y){
    int nbMemeBille = 1;
    int i = x+1 , j = y+1;
    while(i<plateau.size() && j < plateau[i].size() && nbMemeBille < 5
          && plateau[i][j] == plateau[x][y]){
        i++;
        j++;
        nbMemeBille++;
    }
    if(nbMemeBille<5){
        i = x-1;
        j = y-1;
        while(i >= 0 && j >= 0 && plateau[i][j] == plateau[x][y]
              && nbMemeBille < 5){
            i--;
            j--;
            nbMemeBille++;
        }
    }
    return nbMemeBille == 5;
}
