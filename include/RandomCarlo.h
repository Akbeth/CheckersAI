//
// Created by B0lignon on 22/01/2017.
//

#ifndef IA_RANDOMCARLO_H
#define IA_RANDOMCARLO_H

#include <iostream>
#include "Turn.h"

class RandomCarlo {
public:
    RandomCarlo();
    ~RandomCarlo() {};
    Turn* play(Board &b, bool isWhite);
};

#endif //IA_RANDOMCARLO_H
