#include "game.h"
#include <iostream>
#include <limits>

Game::Game(int size, int winLength) : board(size, winLength), currentPlayer('X') {}

void Game::switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

Move Game::playerMove() {
    int row, col;
    while (true) {
        std::cout << "Ruch gracza " << currentPlayer << " (wiersz kolumna): ";
        if (!(std::cin >> row >> col)) {
            std::cout << "Nieprawidłowe dane. Wpisz numer wiersza i kolumny, np. 1 2.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        row -= 1; // Dostosowanie do indeksowania od 0
        col -= 1; // Dostosowanie do indeksowania od 0
        if (board.makeMove(row, col, currentPlayer)) {
            break;
        } else {
            std::cout << "Nieprawidłowy ruch. Spróbuj ponownie.\n";
        }
    }
    board.print();
    return {row, col};
}

Move Game::aiMove() {
    std::cout << "Ruch komputera...\n";
    Move move = getBestMove(
        board,
        currentPlayer,
        currentPlayer == 'X' ? 'O' : 'X',
        board.getWinLength()
    );

    if (move.row != -1 && move.col != -1) {
        board.makeMove(move.row, move.col, currentPlayer);
        board.print();
    } else {
        std::cout << "AI nie znalazło ruchu.\n";
    }
    return move;
}

void Game::run() {
    board.print();
    while (true) {
        Move lastMove;
        if (currentPlayer == 'X')
            lastMove = playerMove();
        else
            lastMove = aiMove();

        if (board.checkWin(lastMove.row, lastMove.col, currentPlayer)) {
            std::cout << "Gracz " << currentPlayer << " wygrywa!\n";
            break;
        }

        if (board.isFull()) {
            std::cout << "Remis!\n";
            break;
        }

        switchPlayer();
    }
}
