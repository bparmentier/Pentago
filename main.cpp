#include <iostream>
#include "pentago.h"
#include <sstream>
#include <algorithm>
#include "pentagoexception.h"
using namespace std;

int lireEntier(string phrase);
Direction lireSens();
void printBoard(vector<vector<Hole> > board);
string conversion(Hole trou);

int main()
{
    int x,y,numMini;
    Direction dir;
    vector<Player> players;
    string nom;
    cout<<"entrez nom joueur 1 : "<<endl;
    cin >> nom;
    players.push_back(Player(nom,BLACK));
    cout<<"entrez nom joueur 2 : "<<endl;
    cin >> nom;
    players.push_back(Player(nom,WHITE));

    Pentago partie(players);
    printBoard(partie.getBoard());
    while(!partie.isFinished()){
        cout<<"au tour de "<<partie.getCurrentPlayerName()<<endl;
        x = lireEntier("entrez la ligne où vous voulez placer votre bille :");
        y = lireEntier("entrez la colonne où vous voulez placer votre bille :");
        try {
            partie.play(x,y);
            printBoard(partie.getBoard());
            numMini = lireEntier("entrez le numéro du mini plateau que vous désirez tourner :");
            dir = lireSens();
            partie.rotate(numMini, dir);
        } catch (PentagoException ex) {
            cout<<ex.what()<<endl;
        }
        printBoard(partie.getBoard());
    }
    if (partie.resultatEgalite()) {
        cout<<"la partie s'est terminé par une égalité !"<<endl;
    } else {
        cout<<"la partie est terminé et le gagnant est : "<<partie.getWinnerName()<<endl;
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
        return COUNTERCLOCKWISE;
    }else{
        return CLOCKWISE;
    }
}

void printBoard(vector<vector<Hole>> board ){
    cout<<"    ";
    for(int i = 0; i<board.size(); i++){
        cout<<i<<" ";
        if(i==2){
            cout<<"  ";
        }
    }
    cout<<endl;
    cout<<"    -------------"<<endl;
    for(int i = 0; i<board.size(); i++){
        cout<<i<<" | ";
        for(int j = 0; j<board.at(i).size(); j++){
            cout << conversion(board[i][j])<<" ";
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

string conversion(Hole trou){
    if(trou.getBall().getColor() == WHITE){
        return "B";
    }else if(trou.getBall().getColor() == BLACK){
        return "N";
    }else{
        return "v";
    }
}

