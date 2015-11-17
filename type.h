#ifndef TYPE
#define TYPE

/*!
 * \brief   type de couleur pour les billes du jeu
 */
typedef enum
{
    WHITE,    /*!< Couleur bille blanche */
    BLACK,       /*!< Couleur bille noir */
    NONE        /*!< Bille trou vide */
} BallColor;

/*!
 * \brief   type de couleur pour les billes du jeu
 */
typedef enum
{
    CLOCKWISE,    /*!< direction pour tourner le mini plateau */
    COUNTERCLOCKWISE      /*!< direction pour tourner le mini plateau */
} Direction;

#endif // TYPE
