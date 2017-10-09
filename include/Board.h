//
// Created by tekiflo on 06/01/17.
//

#ifndef IA_BOARD_H
#define IA_BOARD_H

#include <iostream>
#include <list>
#include "Move.h"

/**
 * Board : Représente un plateau de jeu
 */
class Board {
private:
    /**
     * Le string symbolisant le plateau.
     */
    const std::string m_board;
public:
    /**
     * Représente le plateau de départ.
     */
    static const std::string STARTING_BOARD;
    /**
     * Constructeur vide, permettant d'etre utilise comme un singleton.
     */
    Board();
    /**
     * Constructeur prenant en argument un plateau et définissant directement
     * celui-ci au board.
     */
    Board(std::string board);
    /**
     * Redefinition de l'operateur d'attribution pour afficher un board.
     */
    friend std::ostream& operator<<(std::ostream& os, const Board& obj);
    /**
     * Retourne le string associe a ce plateau.
     */
    std::string getString() const;
    /**
     * Retourne le pion a la position pos.
     */
    Pawn getPawn(int pos) const;
    /**
     * Retourne tous les pions associes a la couleur voulue.
     */
    std::list<int> getAllPawns(bool isWhite) const ;
    /**
     * Retire du plateau de jeu le pion a la position i.
     */
    Board remove(int i);
};


#endif //IA_BOARD_H
