#include "ai.h"
#include <limits>

// Ocena stanu planszy (prosty heurystyczny placeholder)
int evaluate(Board& board, char aiPlayer, char humanPlayer) {
    return 0; // Do rozbudowania w przyszłości
}

// Funkcja Minimax z alpha-beta pruning
int minimax(Board& board, int depth, bool maximizingPlayer,
            char aiPlayer, char humanPlayer,
            int alpha, int beta, int winLength, Move& bestMove) {
    int size = board.getSize();

    // Sprawdź zwycięstwo
    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            char cell = board.getCell(r, c);
            if (cell == ' ')
                continue;

            if (board.checkWin(r, c, cell)) {
                if (cell == aiPlayer)
                    return 10 - depth;
                else
                    return depth - 10;
            }
        }
    }

    if (board.isFull())
        return 0; // remis

    if (depth == 0)
        return evaluate(board, aiPlayer, humanPlayer);

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (int r = 0; r < size; ++r) {
            for (int c = 0; c < size; ++c) {
                if (board.getCell(r, c) == ' ') {
                    board.makeMove(r, c, aiPlayer);
                    Move dummy;
                    int eval = minimax(board, depth - 1, false,
                                       aiPlayer, humanPlayer,
                                       alpha, beta, winLength, dummy);
                    board.makeMove(r, c, ' '); // cofnij ruch

                    if (eval > maxEval) {
                        maxEval = eval;
                        bestMove = {r, c};
                    }

                    alpha = std::max(alpha, eval);
                    if (beta <= alpha)
                        return maxEval;
                }
            }
        }
        return maxEval;
    } else {
        int minEval = std::numeric_limits<int>::max();
        for (int r = 0; r < size; ++r) {
            for (int c = 0; c < size; ++c) {
                if (board.getCell(r, c) == ' ') {
                    board.makeMove(r, c, humanPlayer);
                    Move dummy;
                    int eval = minimax(board, depth - 1, true,
                                       aiPlayer, humanPlayer,
                                       alpha, beta, winLength, dummy);
                    board.makeMove(r, c, ' '); // cofnij ruch

                    if (eval < minEval) {
                        minEval = eval;
                        bestMove = {r, c};
                    }

                    beta = std::min(beta, eval);
                    if (beta <= alpha)
                        return minEval;
                }
            }
        }
        return minEval;
    }
}

Move getBestMove(Board board, char aiPlayer, char humanPlayer, int depthLimit) {
    Move bestMove = {-1, -1};
    int depth = (depthLimit == -1) ? board.getSize() * board.getSize() : depthLimit;

    minimax(board, depth, true, aiPlayer, humanPlayer,
            std::numeric_limits<int>::min(),
            std::numeric_limits<int>::max(),
            3, // winLength – do poprawy na dynamiczne pobieranie
            bestMove);

    return bestMove;
}
