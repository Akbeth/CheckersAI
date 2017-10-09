//
// Created by B0lignon on 22/01/2017.
//

#include "../include/NegMax.h"
#include "../include/MoveStack.h"

using namespace std;
NegMax::NegMax(Turn *turn, bool isWhite, NegMax *parent,
               MoveStack *lstMove) {
    m_turn = turn;
    m_children = new list<NegMax *>();
    m_parent = parent;
    m_lastMove = lstMove;
    m_bestMove = nullptr;
    m_heuristic = 0;
    m_isWhite = isWhite;
}
NegMax::NegMax(Turn *turn, bool isWhite) :
        NegMax(turn, isWhite, nullptr, nullptr) {}
NegMax::~NegMax() {
    for (auto it = m_children->begin(); it != m_children->end(); it++) {
        delete (*it)->m_turn;
        delete *it;
    }
    delete m_children;
}

int NegMax::negMax(int depth, bool isWhite) {
    if (depth == 0 ||
        (m_turn->getBoard().getString().find("b") == string::npos &&
         m_turn->getBoard().getString().find("B") == string::npos) ||
        (m_turn->getBoard().getString().find("w") == string::npos &&
         m_turn->getBoard().getString().find("W") == string::npos)) {
        int heur;
        (isWhite == m_isWhite) ? heur = m_lastMove->getHeuristic(*(m_parent->m_turn)) :
                heur = -m_lastMove->getHeuristic(*(m_parent->m_turn));
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
    int temp = -4483;
    for (auto it = m_children->begin(); it != m_children->end(); it++) {
        int val = - (*it)->negMax(depth - 1, !isWhite);
        if (val > temp) {
            temp = val;
            m_bestMove = (*it)->m_lastMove;
        }
    }

    return temp;
}

void NegMax::generateChildren() {
    m_turn->generateTurn();
    std::list<MoveStack *> available = m_turn->getAvailableMoves();
    for (auto it = available.begin(); it != available.end(); it++) {
        Turn *childTurn = m_turn->getNextTurn(*it);
        NegMax *child = new NegMax(childTurn, m_isWhite, this, *it);
        m_children->push_back(child);
    }
}

Turn *NegMax::nextTurn(int depth, bool isWhite) {
    negMax(depth, isWhite);

    return m_turn->getNextTurn(m_bestMove);
}