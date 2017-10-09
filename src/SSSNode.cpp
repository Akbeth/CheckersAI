//
// Created by Kadinator on 22/01/2017.
//

#include "../include/Turn.h"
#include "../include/SSSNode.h"

SSSNode::SSSNode(Turn *turn, bool isWhite, SSSNode *parent,
                 MoveStack *lastMove) {
    m_turn = turn;
    m_children = new std::list<SSSNode *>();
    m_parent = parent;
    m_brother = nullptr;
    m_lastMove = lastMove;
    m_bestMove = nullptr;
    m_isWhite = isWhite;
    if (m_parent == nullptr) {
        m_depth = 1;
    } else {
        m_depth = m_parent->m_depth + 1;
    }
}

void SSSNode::generateChildren() {
    m_turn->generateTurn();
    std::list<MoveStack *> available = m_turn->getAvailableMoves();
    SSSNode *last = nullptr;
    for (auto it = available.begin(); it != available.end(); it++) {
        Turn *childTurn = m_turn->getNextTurn(*it);
        SSSNode *child = new SSSNode(childTurn, m_isWhite, this, *it);
        child->m_bestMove = m_bestMove;
        m_children->push_back(child);
        if (last != nullptr) {
            last->m_brother = child;
        }
        last = child;
    }
}

SSSNode::~SSSNode() {
    for (auto it = m_children->begin(); it != m_children->end(); it++) {
        //delete (*it)->m_turn;
        delete *it;
    }
    delete m_children;
}

SSSNode::SSSNode(Turn *turn, bool isWhite) : SSSNode(turn, isWhite, nullptr, nullptr){}
