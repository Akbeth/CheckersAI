//
// Created by tekiflo on 06/01/17.
//

#ifndef IA_MOVE_H
#define IA_MOVE_H

#include "Pawn.h"
#include "Board.h"
#include "Direction.h"

class Board;

class Move {
private:
    // CONSTANTS
    /**
     * Represente la position initiale.
     */
    const int m_src;
    // FIELDS
    /**
     * Boolean indiquant si nous sommes en dehors des marges externes.
     */
    bool m_outOfBounds;
    /**
     * Indique la position d'un pion detruit.
     */
    int m_deleted;
    /**
     * La distance parcourue pendant le mouvement.
     */
    int m_dst;
public:
    // CONSTRUCTOR
    /**
     * Cosntructeur prenant en arguments un plateau de jeu, un pion, une position
     * initiale, une direction et une distance.
     */
    Move(Board &b, Pawn &p, int src, Direction direction, int distance);
    // METHODS
    /**
     * Retourne la position initiale.
     */
    int getSource() const;
    /**
     * Retourne la position du dernier pion mange (-1 si aucun).
     */
    int getDeleted() const;
    /**
     * Retourne la destination du mouvement.
     */
    int getDestination() const;
    /**
     * Indique si le mouvement est valide.
     */
    bool isValid() const;
    /**
     * Indique si le mouvement n'est pas en dehors du champ.
     */
    bool isOutOfBounds() const;
    /**
     * Indique si il y a eu un saut de pion.
     */
    bool hasJumped() const;
    /**
     * Effectue le mouvement sur le board.
     */
    void doMove(std::string &b);
    // STATIC METHODS
    static std::string getCoordinates(int pos);
};


#endif //IA_MOVE_H
