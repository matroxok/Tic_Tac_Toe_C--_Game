#include "board.h"
#include <iostream>

Board::Board(int size, int winLength) : size(size), winLength(winLength) {
    grid.resize(size, std::vector<char>(size, ' '));
}

void Board::print() const {
    // Rysowanie planszy w terminalu
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            std::cout << " " << grid[i][j] << " ";
            if (j < size - 1) std::cout << "|";
        }
        std::cout << "\n";
        if (i < size - 1) {
            std::cout << std::string(size * 4 - 1, '-') << "\n";
        }
    }
}

bool Board::makeMove(int row, int col, char player) {
    // Próba wstawienia znaku gracza – tylko jeśli pole puste
    if (row >= 0 && row < size && col >= 0 && col < size && grid[row][col] == ' ') {
        grid[row][col] = player;
        return true;
    }
    return false;
}

bool Board::isFull() const {
    for (const auto& row : grid) {
        for (char cell : row) {
            if (cell == ' ') return false;
        }
    }
    return true;
}

bool Board::checkWin(int row, int col, char player) const {
    // Sprawdzamy 4 kierunki: poziomo, pionowo, ukośnie 
    return checkDirection(row, col, 0, 1, player) ||  // poziomo
           checkDirection(row, col, 1, 0, player) ||  // pionowo
           checkDirection(row, col, 1, 1, player) ||  // ukośnie
           checkDirection(row, col, 1, -1, player);   // ukośnie /
}

bool Board::checkDirection(int row, int col, int dRow, int dCol, char player) const {
    // Liczy ile znaków gracza występuje w danym kierunku
    int count = 1;

    // W jedną stronę
    int r = row + dRow, c = col + dCol;
    while (r >= 0 && r < size && c >= 0 && c < size && grid[r][c] == player) {
        count++;
        r += dRow;
        c += dCol;
    }

    // W drugą stronę
    r = row - dRow, c = col - dCol;
    while (r >= 0 && r < size && c >= 0 && c < size && grid[r][c] == player) {
        count++;
        r -= dRow;
        c -= dCol;
    }

    return count >= winLength;
}

int Board::getSize() const {
    return size;
}

char Board::getCell(int row, int col) const {
    return grid[row][col];
}
