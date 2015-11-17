#ifndef TROU_H
#define TROU_H

#include "bille.h"
#include "joueur.h"
#include "type.h"

class Trou
{

private:
    Bille billeTrou;
    Joueur * joueur;

public:
    Trou();
    void setBilleTrou(Bille bille);
    void setJoueurTrou(Joueur * joueur);
    Bille getBilleTrou() const;
    Joueur * getJoueurTrou()const;
    bool estOccupe() const;

};

bool operator==(Trou const& a, Trou const& b);

#endif // TROU_H
