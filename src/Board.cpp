//
// Created by tekiflo on 06/01/17.
//

#include <iostream>
#include "../include/Board.h"

using namespace std;

const string Board::STARTING_BOARD = "bbbbbbbbbbbbbbbbbbbboooooooooowwwwwwwwwwwwwwwwwwww";

Board::Board(std::string board) : m_board(board) { }

Board::Board() : Board(STARTING_BOARD) { }

std::string Board::getString() const {
    return m_board;
}

Pawn Board::getPawn(int pos) const {
    return Pawn::getPawn(m_board[pos]);
}

std::list<int> Board::getAllPawns(bool isWhite) const {
    list<int> pawns = list<int>();
    for (int i = 0; i < 50; i++) {
        char c = m_board[i];
        if (isWhite && (c == 'w' || c == 'W')) {
            pawns.push_front(i);
        } else if (!isWhite && (c == 'b' || c == 'B')) {
            pawns.push_front(i);
        }
    }
    return pawns;
}

Board Board::remove(int i) {
    string str = m_board;
    str[i] = 'o';
    return Board(str);
}

std::ostream& operator<<(std::ostream &os, const Board &obj) {
    string str = obj.getString();
    os << "  ";
    for (int i = 0; i < 10; i++) {
        os << "  " << i << " ";
    }
    os << endl;
    for (int i = 0; i < 10; i++) {
        os << (char) ('A' + i) << " |";
        if (i % 2 == 0)
            os << "   |";
        for (int j = 0; j < 4; j++) {
            os << ' ' << str[(i * 5) + j] << " |   |";
        }
        os << ' ' << str[(i * 5) + 4] << " |";
        if (i % 2 == 1)
            os << "   |";
        os << endl;
    }
    return os << "Board string : " << endl << str << endl;
}
