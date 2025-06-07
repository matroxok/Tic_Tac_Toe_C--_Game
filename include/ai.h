#ifndef AI_H
#define AI_H

#include "board.h"

struct Move {
    int row;
    int col;
};

// depthLimit domyślnie -1 oznacza brak limitu
Move getBestMove(Board board, char aiPlayer, char humanPlayer, int depthLimit = -1);

#endif
