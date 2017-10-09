//
// Created by tekiflo on 06/01/17.
//

#ifndef IA_TURN_H
#define IA_TURN_H

#include <stack>
#include <map>
#include <list>
#include "Board.h"
#include "MoveTree.h"
#include "MoveStack.h"

/**
 * Classe représentant un tour de jeu.
 */
class Turn {
private:
    // CONSTANTS
    /**
     * Le plateau actuel.
     */
    const Board m_board;
    /**
     * Booléen déterminant la couleur de celui qui  doit jouer.
     */
    const bool m_isWhite;
    /**
     * Numéro du tour.
     */
    const int m_nb;
    // FIELDS
    /**
     * Map reliant un pion (représenté par sa case) avec ses coups possibles.
     */
    std::map<int, MoveTree *> *m_moves;
    /**
     * Liste de tous les coups jouables.
     */
    std::list<MoveStack *> *m_available;
    // PRIVATE METHODS
    /**
     * Rempli la map pour la case src
     * @param src Case du pion dont on va générer les coups
     * @param tree Arbre des coups du pion
     */
    void generateMoves(int src, MoveTree *tree);
    /**
     * Ajoute la suite de la rafle par la reine dans l'arbre des coups
     * @param b Plateau
     * @param p Pion
     * @param src Case de départ du pion
     * @param tree Arbre des coups
     * @param parent Coup précédent
     */
    void addKingJumps(Board &b, Pawn &p, int src, MoveTree *tree, MoveNode *parent);
    /**
     * Ajoute la suite de la rafle par le pion dans l'arbre des coups
     * @param b Plateau
     * @param p Pion
     * @param src Case de départ du pion
     * @param tree Arbre des coups
     * @param parent Coup précédent
     */
    void addPawnJumps(Board &b, Pawn &p, int src, MoveTree *tree, MoveNode *parent);
    /**
     * Vérifie si le pion a déjà été mangé
     * @param n Coup à vérifier
     * @param jumped Pion pret à être mangé
     * @return
     */
    bool hasAlreadyJumped(MoveNode *n, int jumped);
public:
    // CONSTRUCTOR
    /**
     * Constructeur du tour, demande le plateau, la couleur et le numéro de tour
     * @param board Le plateau
     * @param isWhite La couleur
     * @param nb Le numéro du tour
     */
    Turn(Board &board, bool isWhite, int nb);
    /**
     * Destrcuteur
     */
    ~Turn();
    // METHODS
    /**
     * Remplit la map des coups ainsi que la liste des coups autorisés
     */
    void generateTurn();
    /**
     * Applique sur le plateau le mouvement choisi
     * @param chosenMove Le mouvement choisi
     * @return
     */
    Turn* getNextTurn(MoveStack *chosenMove);
    /**
     * Renvoit le plateu de jeu
     * @return
     */
    Board getBoard() const;
    /**
     * Renvoit la couleur
     * @return
     */
    bool isWhite() const;
    /**
     * Renvoit le numéro du tour
     * @return
     */
    int getTurnNumber() const;
    /**
     * Renvoit la liste des coups autorisés
     * @return
     */
    std::list<MoveStack *> getAvailableMoves();
    /**
     * Premet un affichage compréhensible du plateau
     * @param os Affichage
     * @param obj Plateau
     * @return
     */
    friend std::ostream& operator<<(std::ostream& os, const Turn& obj);
};


#endif //IA_TURN_H
