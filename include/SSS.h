#ifndef IA_SSS_H
#define IA_SSS_H

#include <iostream>
#include <list>
#include "SSSNode.h"

/**
 * Classe effectuant l'algorithme SSS*.
 */
class SSS {
private :
    /**
     * Liste contenant les triplets rangés dans l'ordre décroissant de sheuristiques.
     * Les triplets sont composés de : - Le noeud associé
     *                                 - Le statut vivant (false) ou résolu (true)
     *                                 - l'heuristique
     */
    std::list<std::tuple<SSSNode*, bool, int>> *l;
    /**
     * La racine de l'arbre utilisé par l'algorithme
     */
    SSSNode *root;
public :
    /**
     * Constructeur (initialise la liste)
     */
    SSS();
    /**
     * Destructeur
     */
    ~SSS();
    /**
     * Vérifie que l'heuristique de t1 est plus grande que l'heuristique de t2
     * @param t1
     * @param t2
     * @return
     */
    static bool tuplecomp(const std::tuple<SSSNode*, bool, int>& t1, const std::tuple<SSSNode*, bool, int>& t2);
    /**
     * Applique l'lgorithme SSS* sur le tour donné à la profondeur donnée
     * @param t Le tour actuel
     * @param isWhite La couleur de celui qui applique l'algorithme
     * @param depth Profondeure d'exécution
     * @return
     */
    Turn *play(Turn *t, bool isWhite, int depth);
    /**
     * Trie la liste dans l'ordre décroissant
     */
    void sortList();
};
#endif //IA_SSS_H
