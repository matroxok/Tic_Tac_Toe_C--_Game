#ifndef AI_H
#define AI_H

#include "board.h"

struct Move {
    int row;
    int col;
};

Move getBestMove(Board board, char aiPlayer, char humanPlayer, int winLength, int depthLimit = -1);

#endif