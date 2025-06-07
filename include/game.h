#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "ai.h"

class Game {
public:
    Game(int size, int winLength);
    void run();

private:
    Board board;
    char currentPlayer;

    void switchPlayer();
    Move playerMove();
    Move aiMove();
};

#endif
