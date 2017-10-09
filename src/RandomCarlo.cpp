//
// Created by B0lignon on 22/01/2017.
//

#include "../include/RandomCarlo.h"
#include <cstdlib>
#include <time.h>
#include <list>

using namespace std;

RandomCarlo::RandomCarlo() {srand((unsigned)time(0));}

Turn* RandomCarlo::play(Board &b, bool isWhite) {
    Turn t(b, isWhite, 1);

    t.generateTurn();

    std::list<MoveStack *> lis = t.getAvailableMoves();

    short r = rand() % lis.size();
    auto mvIt = lis.begin();
    for (int i = 0; i < r-1; i++, mvIt++);

    return t.getNextTurn(*mvIt);
}