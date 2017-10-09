
#ifndef IA_AI_H
#define IA_AI_H

#include <iostream>
#include "Board.h"

class AI {
public:
     std::string playEasy(Board b, bool isWhite);
     std::string playMedium(Board b, bool isWhite);
     std::string playHard(Board b, bool isWhite);
};

#endif //IA_AI_H
