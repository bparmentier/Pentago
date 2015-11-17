#ifndef TYPE
#define TYPE

/*!
 * \brief   type de couleur pour les billes du jeu
 */
typedef enum
{
    BLANCHE,    /*!< Couleur bille blanche */
    NOIR,       /*!< Couleur bille noir */
    NONE        /*!< Bille trou vide */
} CouleurBille;

/*!
 * \brief   type de couleur pour les billes du jeu
 */
typedef enum
{
    VERS_LE_HAUT,    /*!< direction pour tourner le mini plateau */
    VERS_LE_BAS      /*!< direction pour tourner le mini plateau */
} Direction;

#endif // TYPE
