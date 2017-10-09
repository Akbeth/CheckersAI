//
// Created by tekiflo on 06/01/17.
//

#ifndef IA_MOVEMENT_H
#define IA_MOVEMENT_H

#include "Direction.h"

/**
 * Classe facilitant le déplcaement
 */
class PawnMove {
private:
    // PRIVATE CONSTANTS
    /**
     * Les différents pas permettant de se déplacer en diagonale dans le plateau
     */
    static const int UP_LEFT_EVEN   = -5;
    static const int UP_RIGHT_EVEN  = -4;
    static const int UP_LEFT_ODD    = -6;
    static const int UP_RIGHT_ODD   = -5;
    // STATIC PRIVATE METHOD
    static const bool isEven(int pos);
    // CONSTRUCTOR
    PawnMove() { }
public:
    // STATIC METHODS
    /**
     * Récupère la position de la case dans la direction donnée
     * @param pos
     * @param d
     * @return
     */
    static const int get(int pos, Direction d);
    static const int getUpLeft(int pos);
    static const int getUpRight(int pos);
    static const int getDownLeft(int pos);
    static const int getDownRight(int pos);
    /**
     * Vérifie que le pion peut aller dans la direction donnée
     * @param pos
     * @param d
     * @return
     */
    static const bool canGo(int pos, Direction d);
    static const bool canGoUp(int pos);
    static const bool canGoDown(int pos);
    static const bool canGoLeft(int pos);
    static const bool canGoRight(int pos);
    /**
     * Vérifie si le pion est en haut/en bas du plateau
     * @param pos
     * @return
     */
    static const bool isOnTop(int pos);
    static const bool isOnBottom(int pos);
};


#endif //IA_MOVEMENT_H
