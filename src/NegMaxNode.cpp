//
// Created by tekiflo on 08/01/17.
//

#include <list>
#include <iostream>
#include "../include/NegMaxNode.h"

using namespace std;

NegMaxNode::NegMaxNode(Turn *turn, bool isWhite, NegMaxNode *parent, MoveStack *lastMove) {
    m_turn = turn;
    m_children = new list<NegMaxNode *>();
    m_parent = parent;
    m_lastMove = lastMove;
    m_bestMove = nullptr;
    m_isWhite = isWhite;
}

NegMaxNode::NegMaxNode(Turn *turn, bool isWhite) : NegMaxNode(turn, isWhite, nullptr, nullptr) { }

NegMaxNode::~NegMaxNode() {
    for (auto it = m_children->begin(); it != m_children->end(); it++) {
        delete (*it)->m_turn;
        delete *it;
    }
    delete m_children;
}

int NegMaxNode::negMax(int depth, int alpha, int beta, bool isWhite) {
    if (depth == 0 ||
            (m_turn->getBoard().getString().find("b") == string::npos &&
                    m_turn->getBoard().getString().find("B") == string::npos) ||
            (m_turn->getBoard().getString().find("w") == string::npos &&
                    m_turn->getBoard().getString().find("W") == string::npos)) {
        int heur;
        (isWhite == m_isWhite) ? heur = m_lastMove->getHeuristic(*(m_parent->m_turn)) : heur = -m_lastMove->getHeuristic(*(m_parent->m_turn));
        return heur;
    }
    generateChildren();
    if (m_children->size() == 0) {
        if (isWhite == m_isWhite) {
            return -4483;
        } else {
            return 4483;
        }
    }
    for (auto it = m_children->begin(); it != m_children->end(); it++) {
        int val = - (*it)->negMax(depth - 1, -beta, -alpha, !isWhite);
        if (val > alpha) {
            m_bestMove = (*it)->m_lastMove;
            alpha = val;
        }
        if (alpha >= beta) {
            return alpha;
        }
    }
    return alpha;
}

void NegMaxNode::generateChildren() {
    m_turn->generateTurn();
    std::list<MoveStack *> available = m_turn->getAvailableMoves();
    for (auto it = available.begin(); it != available.end(); it++) {
        Turn *childTurn = m_turn->getNextTurn(*it);
        NegMaxNode *child = new NegMaxNode(childTurn, m_isWhite, this, *it);
        m_children->push_back(child);
    }
}

Turn *NegMaxNode::nextTurn(int depth, bool isWhite) {
    negMax(depth, -4483, 4483, isWhite);
    //cout << "plays : " << *m_bestMove << endl;
    return m_turn->getNextTurn(m_bestMove);
}
