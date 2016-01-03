#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "hole.h"
#include "ballcolor.h"
#include "direction.h"

class Board
{

private:
    std::vector<std::vector<Hole>> board;
    int playNumber;

public:
    /*!
     * \brief constructeur de la class Board
     */
    Board();

    /*!
     * \brief permet de placer une bille sur le plateau
     * \param x la ligne choisie
     * \param y la colonne choisie
     * \param player le joueur qui place la bille
     * \throw PentagoException si la position est invalide ou occupée
     */
    void placeBall(int x, int y, Player *player);

    /*!
     * \brief permet d'effectuer la rotation d'un des mini-plateaux
     * \param miniBoardNum le numéro du mini plateau à retourner
     * \param direction la direction dans laquel on désire le tourner
     * \param player le joueur qui place la bille
     */
    void rotateMiniBoard(int miniBoardNum, Direction direction);

    /*!
     * \brief permet d'obtenir le plateau du jeu
     * \return le plateau
     */
    std::vector<std::vector<Hole>> getBoard() const;

    /*!
     * \brief permet d'obtenir la couleur de la bille à une position donnée
     * \param x la ligne choisie
     * \param y la colonne choisie
     * \return la couleur de la bille
     */
    BallColor getColor(int x, int y) const;

    /*!
     * \brief permet d'obtenir le joueur qui joué sur un trou
     * \param x la ligne choisie
     * \param y la colonne choisie
     * \return le joueur
     */
    Player * getJoueurTrou(int x, int y) const;

    /*!
     * \brief permet de savoir si un trou est occupé
     * \param x la ligne choisie
     * \param y la colonne choisie
     * \return true si il est occupé false si non
     */
    bool isHoleOccupied(int x, int y) const;

    /*!
     * \brief permet de vérifier si il y'a un pentago aprés un placement de bille
     * \param x la ligne où la bille s'est jouée
     * \param y la colonne où la bille s'est jouée
     * \return true si il y'a un pentago false si non
     */
    bool checkSequencePentago(int x, int y);

    /*!
     * \brief permet de vérifier si il y'a un pentago aprés la rotation d'un mini-plateau
     * \param numMiniPlateau numéro du plateau touché par la rotation
     * \return la couleur du joueur gagnant si égalité, renvoie la couleur d'une case vide
     */
    BallColor checkSequencePentagoAfterRotate(int numMiniPlateau);

    /*!
     * \brief permet de savoir si c'est le dernier coup possible sur le plateau
     * \return true si c'est le dernier false si non
     */
    bool lastPlay() const;

private:
    void rotate(int startColumn, int startLine, Direction direction);
    bool pentagoVertical(int x, int y);
    bool pentagoHorizontal(int x, int y);
    bool pentagoRightDiagonal(int x, int y);
    bool pentagoLeftDiagonal(int x, int y);
};

#endif // BOARD_H
