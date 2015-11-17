#include <iostream>
#include "pentago.h"
#include <sstream>
#include <algorithm>
#include "pentagoexception.h"
using namespace std;

int lireEntier(string phrase);
Direction lireSens();
void afficherTab(vector<vector<Trou> > plateau);
string conversion(Trou trou);

int main()
{
    int x,y,numMini;
    Direction dir;
    vector<Joueur> lesJoueurs;
    string nom;
    cout<<"entrez nom joueur 1 : "<<endl;
    cin >> nom;
    lesJoueurs.push_back(Joueur(nom,NOIR));
    cout<<"entrez nom joueur 2 : "<<endl;
    cin >> nom;
    lesJoueurs.push_back(Joueur(nom,BLANCHE));

    Pentago partie(lesJoueurs);
    afficherTab(partie.getPlateau());
    while(!partie.estTerminer()){
        cout<<"au tour de "<<partie.getNomJoueurCourant()<<endl;
        x = lireEntier("entrez la ligne où vous voulez placer votre bille :");
        y = lireEntier("entrez la colonne où vous voulez placer votre bille :");
        try {
            partie.jouer(x,y);
            afficherTab(partie.getPlateau());
            numMini = lireEntier("entrez le numéro du mini plateau que vous désirez tourner :");
            dir = lireSens();
            partie.tourner(numMini, dir);
        } catch (PentagoException ex) {
            cout<<ex.what()<<endl;
        }
        afficherTab(partie.getPlateau());
    }
    if (partie.resultatEgalite()) {
        cout<<"la partie s'est terminé par une égalité !"<<endl;
    } else {
        cout<<"la partie est terminé et le gagnant est : "<<partie.getNomGagnant()<<endl;
    }
}

int lireEntier(string phrase){
    int entier = 0;
    bool bonneEntre = false;
    while(!bonneEntre){
        cout<<phrase<<endl;
        cin>>entier;
        if(!cin.fail() && entier>=0){
            bonneEntre=true;
        }else{
            cin.clear();
            cin.ignore();
        }
    }
    return entier;
}

Direction lireSens(){
    string direction;
    do{
        cout<<"entrez la direction désiré pour le tour (A : AntiHorlogique)(H : Horlogique)"<<endl;
        cin>>direction;
        transform(direction.begin(), direction.end(), direction.begin(), ::toupper);
    }while(direction != "A" && direction != "H");
    if(direction == "A"){
        return VERS_LE_BAS;
    }else{
        return VERS_LE_HAUT;
    }
}

void afficherTab(vector<vector<Trou>> plateau ){
    cout<<"    ";
    for(int i = 0; i<plateau.size(); i++){
        cout<<i<<" ";
        if(i==2){
            cout<<"  ";
        }
    }
    cout<<endl;
    cout<<"    -------------"<<endl;
    for(int i = 0; i<plateau.size(); i++){
        cout<<i<<" | ";
        for(int j = 0; j<plateau.at(i).size(); j++){
            cout << conversion(plateau[i][j])<<" ";
            if(j == 2){
                cout<<"| ";
            }
        }
        cout<<"|"<<endl;
        if(i == 2){
            cout<<"    -------------"<<endl;
        }
    }
    cout<<"    -------------"<<endl;
}

string conversion(Trou trou){
    if(trou.getBilleTrou().getCouleurBille() == BLANCHE){
        return "B";
    }else if(trou.getBilleTrou().getCouleurBille() == NOIR){
        return "N";
    }else{
        return "v";
    }
}

