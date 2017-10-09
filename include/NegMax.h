//
// Created by B0lignon on 22/01/2017.
//

#ifndef IA_MINMAX_H
#define IA_MINMAX_H

#include <iostream>
#include "Turn.h"

/**
 * Represente un noeud de l'arbre NegaMax.
 */
class NegMax {
private:
    /**
     * Represente le tour de ce noeud.
     */
    Turn *m_turn;
    /**
     * Represente la liste des enfants de ce noeud.
     */
    std::list<NegMax *> *m_children;
    /**
     * Represente le parent du noeud.
     */
    NegMax *m_parent;
    /**
     * La sequence du dernier mouvement.
     */
    MoveStack *m_lastMove;
    /**
     * La sequence representant le meilleur mouvement.
     */
    MoveStack *m_bestMove;
    /**
     * L'heuristic du noeud.
     */
    int m_heuristic;
    /**
     * La couleur du noeud.
     */
    bool m_isWhite;
    /**
     * Genere les enfants du noeud courant.
     */
    void generateChildren();
public:
    /**
     * Cosntructeur prenant un tour et indiquant si nous sommes sur un noeud Noir
     * ou un noeud Blanc.
     */
    NegMax(Turn *turn, bool isWhite);
    /**
     * Cosntructeur plus complet que le preccedent prenant un parent et le dernier
     * mouvement joue.
     */
    NegMax(Turn *turn, bool isWhite, NegMax *parent, MoveStack *lastMove);
    /**
     * Destructeur.
     */
    ~NegMax();
    /**
     * Genere l'arborescence et calcul le meilleur coup possible selon la
     *  profondeur attribuee.
     */
    int negMax(int depth, bool isMax);
    /**
     * Simule le prochain tour et renvoie celui-ci (utilise negMax).
     */
    Turn *nextTurn(int depth, bool isWhite);
};

#endif //IA_MINMAX_H
