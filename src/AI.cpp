//
// Created by kadinator on 22/01/17.
//

#include "../include/AI.h"
#include "../include/Board.h"
#include "../include/Turn.h"
#include "../include/NegMaxNode.h"
#include "../include/SSS.h"

std::string AI::playEasy(Board b, bool isWhite) {
    Turn *t = new Turn(b, isWhite, 1);
    int depth = 4;
    NegMaxNode *n = new NegMaxNode(t, isWhite);
    t = n->nextTurn(depth, isWhite);
    delete n;
    std::string newB =  t->getBoard().getString();
    delete t;
    return newB;
}

std::string AI::playMedium(Board b, bool isWhite) {
    Turn *t = new Turn(b, isWhite, 1);
    int depth = 4;
    SSS *sss = new SSS();
    t = sss->play(t, isWhite, depth);
    delete sss;
    std::string newB =  t->getBoard().getString();
    delete t;
    return newB;
}

std::string AI::playHard(Board b, bool isWhite) {
    Turn *t = new Turn(b, isWhite, 1);
    int depth = 12;
    NegMaxNode *n = new NegMaxNode(t, isWhite);
    t = n->nextTurn(depth, isWhite);
    delete n;
    std::string newB =  t->getBoard().getString();
    delete t;
    return newB;
}
