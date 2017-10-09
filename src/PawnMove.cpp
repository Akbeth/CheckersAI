//
// Created by tekiflo on 06/01/17.
//

#include "../include/PawnMove.h"

const int PawnMove::getUpLeft(int pos) {
    return isEven(pos) ? pos + UP_LEFT_EVEN : pos + UP_LEFT_ODD;
}

const int PawnMove::getUpRight(int pos) {
    return isEven(pos) ? pos + UP_RIGHT_EVEN : pos + UP_RIGHT_ODD;
}

const int PawnMove::getDownLeft(int pos) {
    return isEven(pos) ? pos - UP_RIGHT_ODD : pos - UP_RIGHT_EVEN;
}

const int PawnMove::getDownRight(int pos) {
    return isEven(pos) ? pos - UP_LEFT_ODD : pos - UP_LEFT_EVEN;
}

const bool PawnMove::canGoUp(int pos) {
    return pos >= 5;
}

const bool PawnMove::canGoDown(int pos) {
    return pos < 45;
}

const bool PawnMove::canGoLeft(int pos) {
    return isEven(pos) ? true :pos % 5 != 0;
}

const bool PawnMove::canGoRight(int pos) {
    return isEven(pos) ? pos % 5 != 4 : true;
}

const bool PawnMove::isEven(int pos) {
    return pos % 10 < 5;
}

const int PawnMove::get(int pos, Direction d) {
    switch (d) {
        case UP_LEFT:
            return getUpLeft(pos);
        case UP_RIGHT:
            return getUpRight(pos);
        case DOWN_LEFT:
            return getDownLeft(pos);
        default:
            return  getDownRight(pos);
    }
}

const bool PawnMove::canGo(int pos, Direction d) {
    switch (d) {
        case UP_LEFT:
            return canGoUp(pos) && canGoLeft(pos);
        case UP_RIGHT:
            return canGoUp(pos) && canGoRight(pos);
        case DOWN_LEFT:
            return canGoDown(pos) && canGoLeft(pos);
        default:
            return canGoDown(pos) && canGoRight(pos);
    }
}

const bool PawnMove::isOnTop(int pos) {
    return !canGoUp(pos);
}

const bool PawnMove::isOnBottom(int pos) {
    return !canGoDown(pos);
}

