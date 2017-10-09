//
// Created by tekiflo on 07/01/17.
//

#include <iostream>
#include <stack>
#include "../include/MoveStack.h"
#include "../include/Turn.h"
#include "../include/PawnMove.h"

using namespace std;

string MoveStack::doMoves(Turn &t) {
    stack<Move *> st = stack<Move *>(*this);
    string b = t.getBoard().getString();
    if (!st.empty()) {
        Move *m = st.top();
        char pawn = b[m->getSource()];
        b[m->getSource()] = (char) Pawn::EMPTY;
        m->doMove(b);
        while (!st.empty()) {
            m = st.top();
            m->doMove(b);
            st.pop();
        }
        int dst = m->getDestination();
        if (t.isWhite() && PawnMove::isOnTop(dst)) {
            b[dst] = (char) Pawn::WHITE_KING;
        } else if (!t.isWhite() && PawnMove::isOnBottom(dst)) {
            b[dst] = (char) Pawn::BLACK_KING;
        } else {
            b[dst] = pawn;
        }
    }
    return b;
}

std::ostream& operator<<(std::ostream &os, const MoveStack &obj) {
    stack<Move *> st = stack<Move *>(obj);
    os << "Move : [";
    if (!st.empty()) {
        Move *m = st.top();
        os << Move::getCoordinates(m->getSource()) << "->" << Move::getCoordinates(m->getDestination());
        if (m->hasJumped())
            os << '(' << Move::getCoordinates(m->getDeleted()) << ')';
        st.pop();
        while (!st.empty()) {
            m = st.top();
            os << "-" << Move::getCoordinates(m->getSource()) << "->" << Move::getCoordinates(m->getDestination());
            if (m->hasJumped())
                os << '(' << Move::getCoordinates(m->getDeleted()) << ')';
            st.pop();
        }
    }
    return os << ']' << endl;
}

string preview(string &board, stack<Move *> &moves) {
    string futureboard = string(board);
    while (!moves.empty()) {
        Move *move = moves.top();
        move->doMove(futureboard);
        moves.pop();
    }
    return futureboard;
}

bool couronneExt(int pos) {
    return pos < 5 || pos > 44 || pos%10 == 4 || pos%10 == 5;
}

bool couronneInt(int pos) {
    return pos < 10 || pos > 39 || pos%10 == 0 || pos%10 == 9;
}

int MoveStack::getHeuristic(Turn &t) {
    string b = t.getBoard().getString();
    bool isWhite = !t.isWhite();
    int i = 0;
    stack<Move *> st = stack<Move *>(*this);
    string futureBoard = preview(b, st);
    if (isWhite) {
        if (futureBoard.find(Pawn::BLACK_PAWN.getValue()) == string::npos && futureBoard.find(Pawn::BLACK_KING.getValue()) == string::npos) {
            i = 4482;
        } else if (futureBoard.find(Pawn::WHITE_PAWN.getValue()) == string::npos && futureBoard.find(Pawn::WHITE_KING.getValue()) == string::npos) {
            i = -4482;
        } else {
            for (int j = 0; j < 50; j++) {
                int point = 0;
                if (futureBoard[j] == Pawn::WHITE_PAWN) {
                    point += 1 + (6 - j / 5);
                    if (point < 1) point = 1;
                } else if (futureBoard[j] == Pawn::WHITE_KING) {
                    point += 28;
                } else if (futureBoard[j] == Pawn::BLACK_PAWN) {
                    point -= 1 + (j / 5 - 3);
                    if (point > -1) point = -1;
                } else if (futureBoard[j] == Pawn::BLACK_KING) {
                    point -= 56;
                }
                if (couronneExt(j)) {
                    point *= 4;
                } else if (couronneInt(j)) {
                    point *= 2;
                }
                i += point;
            }
        }
    } else {
        if (futureBoard.find(Pawn::BLACK_PAWN.getValue()) == string::npos && futureBoard.find(Pawn::BLACK_KING.getValue()) == string::npos) {
            i = -4482;
        } else if (futureBoard.find(Pawn::WHITE_PAWN.getValue()) == string::npos && futureBoard.find(Pawn::WHITE_KING.getValue()) == string::npos) {
            i = 4482;
        } else {
            for (int j = 0; j < 50; j++) {
                int point = 0;
                if (futureBoard[j] == Pawn::BLACK_PAWN) {
                    point += 1 + (j/5 - 3);
                    if (point < 1) point = 1;
                } else if (futureBoard[j] == Pawn::BLACK_KING) {
                    point += 28;
                } else if (futureBoard[j] == Pawn::WHITE_PAWN) {
                    point -= (1 + (6 - j / 5));
                    if (point > -1) point = -1;
                } else if (futureBoard[j] == Pawn::WHITE_KING) {
                    point -= 56;
                }
                if (couronneExt(j)) {
                    point *= 4;
                } else if (couronneInt(j)) {
                    point *= 2;
                }
                i += point;
            }
        }
    }
    return i;
}


