#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <string>

class Board {
public:
    Board(int size, int winLength);
    void print() const;                    // Wyświetla planszę w terminalu
    bool makeMove(int row, int col, char player); // Wstawia znak gracza
    bool isFull() const;                   // Czy plansza jest pełna
    bool checkWin(int row, int col, char player) const; // Sprawdza wygraną
    int getSize() const;
    char getCell(int row, int col) const;

private:
    int size;
    int winLength;
    std::vector<std::vector<char>> grid;
    bool checkDirection(int row, int col, int dRow, int dCol, char player) const;
};

#endif
