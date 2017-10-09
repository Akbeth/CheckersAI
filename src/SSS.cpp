
#include <iostream>
#include <algorithm>
#include <list>
#include "../include/SSS.h"

Turn *SSS::play(Turn *t, bool isWhite, int depth) {
    l = new std::list<std::tuple<SSSNode*, bool, int>>();
    root = new SSSNode(t, isWhite);
    l->push_back(std::make_tuple(root, false, 4483));
    while (!(std::get<0>(l->front())->m_parent == nullptr && std::get<1>(l->front()) == true)) {
        std::tuple<SSSNode*, bool, int> tete = std::tuple<SSSNode*, bool, int>(l->front());
        if (std::get<2>(tete) == -9) {
        }
        if (!std::get<1>(tete)) {
            if (std::get<0>(tete)->m_depth == depth) {
                l->pop_front();
                std::get<1>(tete) = true;
                if (std::get<0>(tete)->m_lastMove->getHeuristic(*(std::get<0>(tete)->m_parent->m_turn)) < std::get<2>(tete)) {
                    std::get<0>(tete)->m_bestMove = std::get<0>(tete)->m_lastMove;
                }
                std::get<2>(tete) = std::min(std::get<0>(tete)->m_lastMove->getHeuristic(*(std::get<0>(tete)->m_parent->m_turn)), std::get<2>(tete));
                l->push_back(tete);
                sortList();
            } else {
                std::get<0>(tete)->generateChildren();
                if (std::get<0>(tete)->m_children->size() == 0) {
                    l->pop_front();
                    std::get<1>(tete) = true;
                    if (std::get<0>(tete)->m_lastMove->getHeuristic(*(std::get<0>(tete)->m_parent->m_turn)) < std::get<2>(tete)) {
                        std::get<0>(tete)->m_bestMove = std::get<0>(tete)->m_lastMove;
                    }
                    std::get<2>(tete) = std::min(std::get<0>(tete)->m_lastMove->getHeuristic(*(std::get<0>(tete)->m_parent->m_turn)), std::get<2>(tete));
                    l->push_back(tete);
                    sortList();
                } else {
                    if (std::get<0>(tete)->m_isWhite == std::get<0>(tete)->m_turn->isWhite()) {
                        l->pop_front();
                        for (std::list<SSSNode*>::iterator it = std::get<0>(tete)->m_children->begin(); it != std::get<0>(tete)->m_children->end(); it++) {
                            l->push_back(std::make_tuple(*it, false, std::get<2>(tete)));
                        }
                        sortList();
                    } else {
                        l->pop_front();
                        l->push_back(std::make_tuple(std::get<0>(tete)->m_children->front(), false, std::get<2>(tete)));
                        sortList();
                    }
                }
            }
        } else {
            if (std::get<0>(tete)->m_isWhite == std::get<0>(tete)->m_turn->isWhite()) {
                if (std::get<0>(tete)->m_brother != nullptr) {
                    l->pop_front();
                    SSSNode *brother = std::get<0>(tete)->m_brother;
                    brother->m_bestMove = std::get<0>(tete)->m_bestMove;
                    l->push_back(std::make_tuple(brother, false, std::get<2>(tete)));
                    sortList();
                } else {
                    l->pop_front();
                    SSSNode *parent = std::get<0>(tete)->m_parent;
                    parent->m_bestMove = std::get<0>(tete)->m_bestMove;
                    l->push_back(
                            std::make_tuple(parent, true, std::get<2>(tete)));
                    sortList();
                }
            } else {
                l->pop_front();
                SSSNode *parent = std::get<0>(tete)->m_parent;
                parent->m_bestMove = std::get<0>(tete)->m_lastMove;
                for (int i = 0; i < l->size(); i++) {
                    std::tuple<SSSNode*, bool, int> front = l->front();
                    l->pop_front();
                    if (std::get<0>(front)->m_parent != parent) {
                        l->push_back(front);
                        sortList();
                    }
                }
                l->push_back(
                        std::make_tuple(parent, true, std::get<2>(tete)));
                sortList();
            }
        }
        /*std::cout << "[";
        for (std::list<std::tuple<SSSNode*, bool, int>>::iterator it = l->begin();
             it != l->end(); it++) {
            std::cout << "<" << std::get<2>(*it) << ">";
        }
        std::cout << "]" << std::endl;*/
    }
    return root->m_turn->getNextTurn(root->m_bestMove);
}

bool SSS::tuplecomp(const std::tuple<SSSNode *, bool, int>& t1,
                    const std::tuple<SSSNode *, bool, int>& t2) {
    return std::get<2>(t1) > std::get<2>(t2);
}

SSS::SSS() {
    l = new std::list<std::tuple<SSSNode*, bool, int>>();
}

SSS::~SSS() {
    l->clear();
    delete l;
    delete root;
}

void SSS::sortList() {
    std::list<std::tuple<SSSNode*, bool, int>> *temp = new std::list<std::tuple<SSSNode*, bool, int>>();
    std::tuple<SSSNode*, bool, int> last = l->back(); 
    l->pop_back();
    while (tuplecomp(last, l->back()) > 0 && l->size() > 0) {
        //std::cout << std::get<2>(last) << " ? " << std::get<2>(l->back()) << " | ";
        temp->push_back(l->back());
        l->pop_back();
    }
    //std::cout << std::endl;
    l->push_back(last);
    while (temp->size() != 0) {
        l->push_back(temp->back());
        temp->pop_back();
    }
}
