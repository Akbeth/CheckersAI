//
// Created by B0lignon on 22/01/2017.
//

#ifndef IA_MONTECARLONODE_H
#define IA_MONTECARLONODE_H

#include <iostream>
#include "Turn.h"

class MonteCarloNode {
private:
    /**
     * Represente le tour actuel.
     */
    Turn *m_turn;
    /**
     * Represente les enfants de ce noeud.
     *  Si taille(m_children) == 0 alors nous sommes sur une feuille.
     */
    std::list<MonteCarloNode *> *m_children;
    /**
     * Represente le noeud parent.
     *  Si m_parent == nullptr, alors nous sommes sur la racine.
     */
    MonteCarloNode *m_parent;
    /**
     * On sauvegarde le dernier mouvement effectue.
     */
    MoveStack *m_lastMove;
    /**
     * On garde le meilleur coup de ce noeud.
     */
    MoveStack *m_bestMove;
    /**
     * L'heuristic actuelle de ce noeud.
     */
    int m_heuristic;
    /**
     * Si nous sommes sur un noeud Blanc ou Noir.
     */
    bool m_isWhite;
    /**
     * Fonction permettant de generer les enfants.
     */
    void generateChildren();
    /**
     * Premiere phase de MonteCarlo, il faut selectionner quel noeud nous prenons
     *  pour propager l'algorithme.
     */
    Turn &selectionCarlo();
    /**
     * Une fois le noeud choisi dans la premiere phase, nous etendons celui-ci
     *  pour faire de nombreux tirages aleatoires permettant de nous assurer
     *  qu'il existe une strategie gagnante sur ce noeud.
     */
    void expandCarlo();
    /**
     * Une fois etendu, nous provoquons une simualtion sur tous les noeuds de l'arbre
     * , y compris  ceux precendents la selection.
     */
    void simulateCarlo(int depth);
    /**
     * Nous remontons le resultat des simulations jusque la racine.
     */
    Turn &backPropCarlo();

public:
    /**
     * Cosntructeur prenant un tour et indiquant si nous sommes sur un noeud Noir
     * ou un noeud Blanc.
     */
    MonteCarloNode(Turn *turn, bool isWhite);
    /**
     * Cosntructeur plus complet que le preccedent prenant un parent et le dernier
     * mouvement joue.
     */
    MonteCarloNode(Turn *turn, bool isWhite, MonteCarloNode *parent, MoveStack *lastMove);
    /**
     * Destructeur.
     */
    ~MonteCarloNode();
};

#endif //IA_MONTECARLONODE_H
