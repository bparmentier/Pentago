#ifndef PENTAGO_H
#define PENTAGO_H

#include "gamemanager.h"
#include "board.h"
#include "actiongame.h"
#include <vector>

class Pentago
{

public:
    GameManager gameManager;
    Board board;
    ActionGame nextAction;
    BallColor winner;

public:

    /*!
     * \brief Constructeur du jeu pentago
     * \param players le tableau des joueurs qui vont y jouer
     */
    Pentago(std::vector<Player> & players);

    /*!
     * \brief permet de joueur une bille sur le plateau
     * \param x la ligne choisie
     * \param y la colonne choisie
     * \throw PentagoException si la partie est terminé
     */
    void play(int x, int y, QTcpSocket *player);

    /*!
     * \brief permet d'éffectuer la rotation d'un mini-plateau
     * \param miniBoard numéro du mini-plateau
     * \param direction la direction de la rotation
     * \throw PentagoException si la partie est terminé ou que le
     * numéro du mini-plateau est invalide
     */
    void rotate(int miniBoard, Direction direction, QTcpSocket * player);

    /*!
     * \brief permet de savoir si une partie est fini
     * \return true si elle est fini false si non
     */
    bool isFinished() const;

    /*!
     * \brief permet de savoir si une partie s'est fini par une égalité
     * \return true si c'est égalité false si non
     */
    bool resultatEgalite() const;

    /*!
     * \brief permet d'obtenir le nom du joueur gagnant
     * \return le nom du joueur
     * \throw PentagoException si la partie n'est pas terminée
     */
    std::string getWinnerName();

    /*!
     * \brief permet d'obtenir la couleur des billes du joueur gagnant
     * \return la couleur des billes du joueur gagnant
     * \throw PentagoException si la partie n'est pas terminée
     */
    BallColor getWinnerBallColor();

    /*!
     * \brief permet d'obtenir le socket du joueur gagnant
     * \return le socket du joueur
     * \throw PentagoException si la partie n'est pas terminée
     */
    QTcpSocket *getWinnerSocket();

    /*!
     * \brief permet d'obtenir le nom du joueur courant de la partie
     * \return le nom du joueur courant
     */
    std::string getCurrentPlayerName();

    /*!
     * \brief permet d'obtenir la couleur des billes du joueur courant
     * \return la couleur des billes du joueur courant
     */
    BallColor getCurrentPLayerBallColor();

    /*!
     * \brief permet d'obtenir le plateau du jeu
     * \return le plateau du jeu
     */
    std::vector<std::vector<Hole>> getBoard() const;

};

#endif // PENTAGO_H
