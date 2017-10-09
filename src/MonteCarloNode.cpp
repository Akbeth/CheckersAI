//
// Created by B0lignon on 22/01/2017.
//
#include "../include/MonteCarloNode.h"
#include <list>

using namespace std;

MonteCarloNode::MonteCarloNode(Turn *turn, bool isWhite, MonteCarloNode *parent, MoveStack *lstMove) {
    m_turn = turn;
    m_children = new list<MonteCarloNode *>();
    m_parent = parent;
    m_lastMove = lstMove;
    m_bestMove = nullptr;
    m_heuristic = 0;
    m_isWhite = isWhite;
}

MonteCarloNode::MonteCarloNode(Turn *turn, bool isWhite) :
        MonteCarloNode(turn, isWhite, nullptr, nullptr) {}

MonteCarloNode::~MonteCarloNode() {
    for (auto it = m_children->begin(); it != m_children->end(); it++) {
        delete (*it)->m_turn;
        delete *it;
    }
    delete m_children;
}