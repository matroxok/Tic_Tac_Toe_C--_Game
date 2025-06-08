#ifndef BOARD_H
#define BOARD_H

#include <vector>

class Board {
    int size;
    int winLength;
    std::vector<std::vector<char>> grid;

public:
    Board(int size, int winLength);
    void print() const;
    bool makeMove(int row, int col, char player);
    bool isFull() const;
    bool checkWin(int row, int col, char player) const;
    bool checkDirection(int row, int col, int dRow, int dCol, char player) const;
    int getSize() const;
    char getCell(int row, int col) const;
};

#endif