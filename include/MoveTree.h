//
// Created by tekiflo on 07/01/17.
//

#ifndef IA_MOVETREE_H
#define IA_MOVETREE_H


#include "Move.h"
#include "MoveNode.h"

/**
 * Represente un arbre de mouvement.
 */
class MoveTree {
private:
    /**
     * La position initiale de la racine (du mouvement).
     */
    const int m_src;
    /**
     * LA hauteur du noeud le plus bas.
     */
    int m_lowest;
    /**
     * Retourne la liste des noeuds les plus bas.
     */
    std::list<MoveNode *> *m_lowestLeafs;
    /**
     * Retourne les enfants de ce mouvement.
     */
    std::list<MoveNode *> *m_children;
public:
    /**
     * Constructeur prenant en argument la position initiale.
     */
    MoveTree(int src);
    /**
     * Destructeur.
     */
    ~MoveTree();
    /**
     * Retourne la liste des mouvement les plus bas.
     */
    std::list<MoveNode *> getLowestLeafs() const;
    /**
     * Retourne la hauteur maximale a laquelle on peut descendre.
     */
    int getHeight() const;
    /**
     * Ajout d'une feuille dans l'arbre.
     */
    void addLeaf(MoveNode *move, int height);
    /**
     * Ajout d'un enfant au noeud courrant.
     */
    void addChild(MoveNode *node);
};


#endif //IA_MOVETREE_H
