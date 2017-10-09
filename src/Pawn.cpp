//
// Created by tekiflo on 06/01/17.
//

#include "../include/Pawn.h"
const Pawn Pawn::WHITE_PAWN = Pawn('w', true, false, false);
const Pawn Pawn::BLACK_PAWN    = Pawn('b', false, false, false);
const Pawn Pawn::WHITE_KING    = Pawn('W', true, true, false);
const Pawn Pawn::BLACK_KING    = Pawn('B', false, true, false);
const Pawn Pawn::EMPTY         = Pawn('o', false, false, true);

Pawn::Pawn(char v, bool w, bool k, bool e) {
    m_value = v;
    m_white = w;
    m_king = k;
    m_empty = e;
}

char Pawn::getValue() const {
    return m_value;
}

bool Pawn::isWhite() const {
    return m_white;
}

bool Pawn::isEmpty() const {
    return m_empty;
}

Pawn::operator char() const {
    return m_value;
}

bool Pawn::isKing() const {
    return m_king;
}

bool Pawn::isEnemyWith(Pawn pawn) {
    return isWhite() != pawn.isWhite();
}


Pawn Pawn::getPawn(char value) {
    switch (value) {
        case 'w':
            return Pawn::WHITE_PAWN;
        case 'b':
            return Pawn::BLACK_PAWN;
        case 'W':
            return Pawn::WHITE_KING;
        case 'B':
            return Pawn::BLACK_KING;
        default:
            return Pawn::EMPTY;
    }
}