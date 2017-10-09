//
// Created by tekiflo on 06/01/17.
//

#ifndef IA_PAWN_H
#define IA_PAWN_H

class Pawn {
private:
    // FIELDS
    /**
     * Représentation de la pièce dans la chaine repréentant le plateu
     */
    char m_value;
    /**
     * Vérifie si le pion est blanc
     */
    bool m_white;
    /**
     * Vérifie si le pion est une reine
     */
    bool m_king;
    /**
     * Vérifie si la case est vide
     */
    bool m_empty;
    // CONSTRUCTORS
    /**
     * Construit un pion
     * @param v
     * @param w
     * @param k
     * @param e
     */
    Pawn(char v, bool w, bool k, bool e);
public:
    // CONSTANTS
    /**
     * Instance préfabriquée des 5 cas possibles
     */
    static const Pawn WHITE_PAWN;
    static const Pawn BLACK_PAWN;
    static const Pawn WHITE_KING;
    static const Pawn BLACK_KING;
    static const Pawn EMPTY;
    static Pawn getPawn(char value);
    // METHODS
    /**
     * Récupère les différentes informations du pion
     * @return
     */
    char getValue() const;
    bool isWhite() const;
    bool isKing() const;
    bool isEmpty() const;
    /**
     * Vérifie que le pion cible est un ennemi
     * @param pawn
     * @return
     */
    bool isEnemyWith(Pawn pawn);
    // OPERATORS
    operator char() const;
};

#endif //IA_PAWN_H
