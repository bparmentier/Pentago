#include "trou.h"
#include "type.h"

Trou::Trou(): billeTrou(NONE), joueur(nullptr)
{
}

void Trou::setBilleTrou(Bille bille)
{
    billeTrou = bille;
}

void Trou::setJoueurTrou(Joueur * joueur)
{
    this->joueur = joueur;
}

Bille Trou::getBilleTrou() const
{
    return billeTrou;
}

Joueur * Trou::getJoueurTrou() const
{
    return joueur;
}

bool Trou::estOccupe() const
{
    return joueur!=nullptr;
}

bool operator==(Trou const& a, Trou const& b){
    return a.getBilleTrou().getCouleurBille() == b.getBilleTrou().getCouleurBille()
            && a.getJoueurTrou() == b.getJoueurTrou();
}
