//
// Created by tekiflo on 06/01/17.
//

#include <iostream>
#include "../include/Move.h"
#include "../include/Board.h"
#include "../include/PawnMove.h"

Move::Move(Board &b, Pawn &p, int src, Direction direction, int distance)
        : m_src(src) {
    int pos = src;
    m_dst = -1;
    m_deleted = -1;
    m_outOfBounds = false;

    if (distance < 1)
        throw std::exception();
    if (p.isEmpty())
        throw std::exception();

    if (p.isKing()) {
        // Mouvement de dame
        for (int i = 0; i < distance; i++) {
            if (!PawnMove::canGo(pos, direction)) {
                m_outOfBounds = true;
                return;
            }
            pos = PawnMove::get(pos, direction);
            Pawn posPawn = b.getPawn(pos);
            if (!posPawn.isEmpty()) {
                // Pion sauté
                if (m_deleted != -1) {
                    m_outOfBounds = true;
                    return;
                }
                if (!posPawn.isEnemyWith(p)) {
                    m_outOfBounds = true;
                    return;
                }
                m_deleted = pos;
            }
        }
    } else {
        // Mouvement de pion
        if (!PawnMove::canGo(pos, direction)) {
            m_outOfBounds = true;
            return;
        }
        pos = PawnMove::get(pos, direction);
        Pawn posPawn = b.getPawn(pos);
        if (!posPawn.isEmpty()) {
            // Pion sauté
            if (distance != 2)
                return;
            if (m_deleted != -1)
                return;
            if (!posPawn.isEnemyWith(p))
                return;
            m_deleted = pos;
            if (!PawnMove::canGo(pos, direction)) {
                m_outOfBounds = true;
                return;
            }
            pos = PawnMove::get(pos, direction);
        } else {
            if (distance != 1)
                return;
        }
    }
    if (!b.getPawn(pos).isEmpty())
        return;
    m_dst = pos;
}

int Move::getSource() const {
    return m_src;
}

int Move::getDeleted() const {
    return m_deleted;
}

int Move::getDestination() const {
    return m_dst;
}

bool Move::isValid() const {
    return m_dst != -1;
}

bool Move::hasJumped() const {
    return m_deleted != -1;
}

bool Move::isOutOfBounds() const {
    return m_outOfBounds;
}

void Move::doMove(std::string &board) {
    if (m_deleted != -1)
        board[m_deleted] = (char) Pawn::EMPTY;
}

std::string Move::getCoordinates(int pos) {
    std::string str = std::string();
    str = (char) ('A' + pos / 5);
    if (pos % 10 < 5)
        str = str + (char) ('1' + (pos % 5 * 2));
    else
        str = str + (char) ('0' + (pos % 5 * 2));
    return str;
}