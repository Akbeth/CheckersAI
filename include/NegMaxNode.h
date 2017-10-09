//
// Created by tekiflo on 08/01/17.
//

#ifndef IA_NEGAMAXNOD_H
#define IA_NEGAMAXNOD_H

#include <iostream>
#include "Turn.h"

class NegMaxNode {
private:
    /**
     * Tour de jeu représenté par ce noeud
     */
    Turn *m_turn;
    /**
     * Liste des enfants de ce noeud
     */
    std::list<NegMaxNode *> *m_children;
    /**
     * Parent de ce noeud
     */
    NegMaxNode *m_parent;
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
public:
    /**
     * Construit le noeud, suppose parent et lastMove à null (en général utilisé pour créer la racine)
     * @param turn
     * @param isWhite
     */
    NegMaxNode(Turn *turn, bool isWhite);
    /**
    * Construit le noeud à artir des informations données
    * @param turn Le tour de jeu
    * @param isWhite La couleur de celui qui applique l'algorithme
    * @param parent Le parent du noeud que l'on veut créer
    * @param lastMove Le coup joué pour arrivé à ce tour
    */
    NegMaxNode(Turn *turn, bool isWhite, NegMaxNode *parent, MoveStack *lastMove);
    /**
     * Destructeur
     */
    ~NegMaxNode();
    /**
     * Calcule la valeure negamax de ce noeud
     * @param depth La profondeure du moeud
     * @param alpha La valeure Alpha
     * @param beta La valeure Beta
     * @param isMax Noeud Max ou min
     * @return
     */
    int negMax(int depth, int alpha, int beta, bool isMax);
    /**
     * Lance calcul de la valeure Negmax puis renvoit le nouveau tour
     * @param depth Profondeure du noeud
     * @param isWhite La couleur de celui qui applique l'algorithme
     * @return
     */
    Turn *nextTurn(int depth, bool isWhite);
};


#endif //IA_NEGAMAXNOD_H
