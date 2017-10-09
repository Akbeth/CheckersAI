//
// Created by tekiflo on 07/01/17.
//

#ifndef IA_MOVENODE_H
#define IA_MOVENODE_H


#include <list>
#include "Move.h"

class MoveTree;

/**
 * Afin de contenir les mouvements, nous utilisons un arbre. Ainsi cette classe
 *  modélise un noeud de cette arbre.
 */
class MoveNode {
protected:
    /**
     * Represente la racine.
     */
    MoveTree *m_root;
    /**
     * Represente le parent du noeud.
     */
    MoveNode *m_parent;
    /**
     * Le mouvement associe a ce noeud.
     */
    Move *m_move;
    /**
     * Represente la hauteur.
     */
    int m_height;
    /**
     * Contient les enfants de ce noeud.
     */
    std::list<MoveNode *> *m_children;
    /**
     * Ajoute un mouvement aux enfants.
     */
    void addChild(MoveNode *child);
public:
    /**
     * Cosntructeur prenant en argument la racine et le mouvement actuel.
     */
    MoveNode(MoveTree *tree, Move *move);
    /**
     * Constructeur prenant en argument la racine, le parent et le mouvement
     *  actuel.
     */
    MoveNode(MoveTree *tree, MoveNode *parent, Move *move);
    /**
     * Destructeur.
     */
    ~MoveNode();
    /**
     * Retourne le parent.
     */
    MoveNode* getParent() const;
    /**
     * Retourne la racine.
     */
    MoveTree* getRoot() const;
    /**
     * Retourne le mouvement associe.
     */
    Move* getMove() const;
    /**
     * Retourne al liste des enfants.
     */
    std::list<MoveNode *> getChildren() const;
};


#endif //IA_MOVENODE_H
