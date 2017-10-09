#ifndef IA_SSSNODE_H
#define IA_SSSNODE_H

#include <iostream>
#include "Turn.h"

/**
 * Classe utilisée pour construire l'arbre lors de l'algorithme SSS*
 */
class SSSNode {
private :
public :
    /**
     * Tour de jeu représenté par ce noeud
     */
    Turn *m_turn;
    /**
     * Liste des enfants de ce noeud
     */
    std::list<SSSNode *> *m_children;
    /**
     * Parent de ce noeud
     */
    SSSNode *m_parent;
    /**
     * Frère droit de ce noeud
     */
    SSSNode *m_brother;
    /**
     * Coup effectué pour arriver à ce tour
     */
    MoveStack *m_lastMove;
    /**
     * Permet la transmission du meilleur coup
     */
    MoveStack *m_bestMove;
    /**
     * La couleur du joueur qui applique l'algorithme
     */
    bool m_isWhite;
    /**
     * Génère les enfants du noeud actuel
     */
    void generateChildren();

    /**
     * Construit le noeud, suppose parent et lastMove à null (en général utilisé pour créer la racine)
     * @param turn
     * @param isWhite
     */
    SSSNode(Turn *turn, bool isWhite);
    /**
     * Construit le noeud à artir des informations données
     * @param turn Le tour de jeu
     * @param isWhite La couleur de celui qui applique l'algorithme
     * @param parent Le parent du noeud que l'on veut créer
     * @param lastMove Le coup joué pour arrivé à ce tour
     */
    SSSNode(Turn *turn, bool isWhite, SSSNode *parent, MoveStack *lastMove);
    /**
     * Destructeur
     */
    ~SSSNode();
    /**
     * La profondeur du moeud
     */
    int m_depth;
};

#endif //IA_SSSNODE_H
