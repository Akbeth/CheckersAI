//
// Created by tekiflo on 06/01/17.
//

#include <list>
#include "../include/Turn.h"

using namespace std;

Turn::Turn(Board &board, bool isWhite, int nb) : m_board(board), m_isWhite(isWhite), m_nb(nb) {
    m_moves = new map<int, MoveTree *>();
    m_available = new list<MoveStack *>();
}

Turn::~Turn() {
    for (auto ci = m_available->begin(); ci != m_available->end(); ci++) {
        delete *ci;
    }
    delete m_available;
    if (!m_moves->empty()) {
        list<int> pawns = m_board.getAllPawns(isWhite());
        for (auto ci = pawns.begin(); ci != pawns.end(); ci++) {
            delete m_moves->at(*ci);
        }
    }
    delete m_moves;
}

Board Turn::getBoard() const {
    return m_board;
}

bool Turn::isWhite() const {
    return m_isWhite;
}

int Turn::getTurnNumber() const {
    return m_nb;
}

std::list<MoveStack *> Turn::getAvailableMoves() {
    return *m_available;
}

void Turn::generateTurn() {
    int maxHeight = 0;
    list<int> pawns = m_board.getAllPawns(isWhite());
    for (auto ci = pawns.begin(); ci != pawns.end(); ci++) {
        MoveTree *pmoves = new MoveTree(*ci);
        m_moves->insert(pair<int, MoveTree *>(*ci, pmoves));
        generateMoves(*ci, pmoves);
        if (pmoves->getHeight() > maxHeight)
            maxHeight = pmoves->getHeight();
    }
    for (auto ci = pawns.begin(); ci != pawns.end(); ci++) {
        MoveTree *pmoves = m_moves->at(*ci);
        if (maxHeight > 0) {
            if (pmoves->getHeight() == maxHeight) {
                auto leafs = pmoves->getLowestLeafs();
                for (auto ci2 = leafs.begin(); ci2 != leafs.end(); ci2++) {
                    MoveNode *n = *ci2;
                    MoveStack *st = new MoveStack();
                    while (n != nullptr) {
                        st->push_back(n->getMove());
                        n = n->getParent();
                    }
                    m_available->push_front(st);
                }
            }
        }
    }
}

void Turn::generateMoves(int src, MoveTree *tree) {
    Pawn p = getBoard().getPawn(src);
    Board b = getBoard().remove(src);
    Move *m = nullptr;
    MoveNode *n = nullptr;
    if (!p.isKing()) {
        // Coup normal
        if (p.isWhite()) {
            m = new Move(b, p, src, Direction::UP_LEFT, 1);
            if (m->isValid()) new MoveNode(tree, m);
            else delete m;

            m = new Move(b, p, src, Direction::UP_RIGHT, 1);
            if (m->isValid()) new MoveNode(tree, m);
            else delete m;
        } else {
            m = new Move(b, p, src, Direction::DOWN_LEFT, 1);
            if (m->isValid()) new MoveNode(tree, m);
            else delete m;

            m = new Move(b, p, src, Direction::DOWN_RIGHT, 1);
            if (m->isValid()) new MoveNode(tree, m);
            else delete m;
        }
        // Saut
        for (int i = Direction::UP_LEFT; i < 4; i++) {
            m = new Move(b, p, src, static_cast<Direction>(i), 2);
            if (m->isValid()) {
                n = new MoveNode(tree, m);
                // Rafle
                addPawnJumps(b, p, m->getDestination(), tree, n);
            } else
                delete m;
        }
    } else {
        // Dame
        for (int i = Direction::UP_LEFT; i < 4; i++) {
            int distance = 1;
            bool delMaker = false;
             do {
                if (!delMaker) delete m;
                m = new Move(b, p, src, static_cast<Direction>(i), distance);
                if (m->isValid()) {
                    n = new MoveNode(tree, m);
                    // Saut
                    if (m->hasJumped()) {
                        addKingJumps(b, p, m->getDestination(), tree, n);
                    }
                    delMaker = true;
                } else
                    delMaker = false;
                distance++;
            } while (!m->isOutOfBounds());
        }
        delete m;
    }
}

void Turn::addPawnJumps(Board &b, Pawn &p, int src, MoveTree *tree, MoveNode *parent) {
    for (int i = Direction::UP_LEFT; i < 4; i++) {
        Move *m = new Move(b, p, src, static_cast<Direction>(i), 2);
        if (m->isValid()) {
            if (!hasAlreadyJumped(parent, m->getDeleted())) {
                MoveNode *child = new MoveNode(tree, parent, m);
                addPawnJumps(b, p, m->getDestination(), tree, child);
            } else
                delete m;
        } else
            delete m;
    }
}

void Turn::addKingJumps(Board &b, Pawn &p, int src, MoveTree *tree, MoveNode *parent) {
    for (int i = Direction::UP_LEFT; i < 4; i++) {
        int distance = 2;
        Move *m = nullptr;
        bool delMaker = false;
        do {
            if (!delMaker) delete m;
            m = new Move(b, p, src, static_cast<Direction>(i), distance);
            if (m->isValid() && m->hasJumped()) {
                if (!hasAlreadyJumped(parent, m->getDeleted())) {
                    MoveNode *child = new MoveNode(tree, parent, m);
                    addKingJumps(b, p, m->getDestination(), tree, child);
                    delMaker = true;
                } else
                    delMaker = false;
            } else
                delMaker = false;
            distance++;
        } while (!m->isOutOfBounds());
        if (!delMaker) delete m;
    }
}

bool Turn::hasAlreadyJumped(MoveNode *n, int jumped) {
    MoveNode *parent = n;
    while (parent != nullptr) {
        if (jumped == parent->getMove()->getDeleted()) {
            return true;
        }
        parent = parent->getParent();
    }
    return false;
}

Turn* Turn::getNextTurn(MoveStack *chosenMove) {
    string str = chosenMove->doMoves(*this);
    Board b = Board(str);
    int nb = getTurnNumber();
    if (!isWhite())
        nb++;
    return new Turn(b, !isWhite(), nb);
}

std::ostream& operator<<(std::ostream &os, const Turn &obj) {
    os << "Turn " << obj.getTurnNumber() << " - ";
    if (obj.isWhite())
        os << "white plays" << endl;
    else
        os << "black plays" << endl;
    os << obj.getBoard() << endl;
}