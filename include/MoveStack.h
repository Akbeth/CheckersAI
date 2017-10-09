//
// Created by tekiflo on 07/01/17.
//

#ifndef IA_MOVESTACK_H
#define IA_MOVESTACK_H


#include <deque>
#include "Move.h"
#include "Board.h"

class Turn;

/**
 * Represente une sequence de mouvement.
 */
class MoveStack : public std::deque<Move *> {
public:
    /**
     * Produit le mouvement stocke.
     */
    std::string doMoves(Turn &t);
    /**
     * Retourne l'heuristic du tour donne en argument par rapport au coup stocke.
     */
    int getHeuristic(Turn &t);
    /**
     * Redefinition de l'operateur d'attribution pour l'affichage.
     */
    friend std::ostream& operator<<(std::ostream& os, const MoveStack& obj);
};


#endif //IA_MOVESTACK_H
