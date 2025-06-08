#include "ai.h"
#include <limits>
#include <iostream>

int scoreLine(int count, int empty, int winLength) {
    if (count == winLength) return 1000;
    if (count == winLength - 1 && empty > 0) return 100;
    if (count == winLength - 2 && empty > 1) return 10;
    return count;
}

int evaluate(Board& board, char aiPlayer, char humanPlayer, int winLength) {
    int size = board.getSize();
    int score = 0;

    for (int r = 0; r < size; ++r) {
        for (int c = 0; c < size; ++c) {
            for (int dr = -1; dr <= 1; ++dr) {
                for (int dc = -1; dc <= 1; ++dc) {
                    if (dr == 0 && dc == 0) continue;

                    int aiCount = 0, humanCount = 0, emptyCount = 0;
                    for (int k = 0; k < winLength; ++k) {
                        int nr = r + dr * k;
                        int nc = c + dc * k;
                        if (nr >= 0 && nr < size && nc >= 0 && nc < size) {
                            char cell = board.getCell(nr, nc);
                            if (cell == aiPlayer) aiCount++;
                            else if (cell == humanPlayer) humanCount++;
                            else emptyCount++;
                        }
                    }

                    if (humanCount == 0)
                        score += scoreLine(aiCount, emptyCount, winLength);
                    if (aiCount == 0)
                        score -= scoreLine(humanCount, emptyCount, winLength);
                }
            }
        }
    }

    return score;
}

int minimax(Board& board, int depth, bool maximizingPlayer,
            char aiPlayer, char humanPlayer,
            int alpha, int beta, int winLength, Move& bestMove) {
    if (board.isFull() || depth == 0)
        return evaluate(board, aiPlayer, humanPlayer, winLength);

    int size = board.getSize();

    if (maximizingPlayer) {
        int maxEval = std::numeric_limits<int>::min();
        for (int r = 0; r < size; ++r) {
            for (int c = 0; c < size; ++c) {
                if (board.getCell(r, c) == ' ') {
                    board.makeMove(r, c, aiPlayer);
                    if (board.checkWin(r, c, aiPlayer)) {
                        board.makeMove(r, c, ' ');
                        bestMove = {r, c};
                        return 10000 - depth;
                    }
                    Move dummy;
                    int eval = minimax(board, depth - 1, false,
                                       aiPlayer, humanPlayer, alpha, beta, winLength, dummy);
                    board.makeMove(r, c, ' ');

                    if (eval > maxEval) {
                        maxEval = eval;
                        bestMove = {r, c};
                        // std::cout << "[AI DEBUG] Max wybiera (" << r << "," << c << ") z oceną " << eval << "\n";
                    }
                    alpha = std::max(alpha, eval);
                    if (beta <= alpha) return maxEval;
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
                    if (board.checkWin(r, c, humanPlayer)) {
                        board.makeMove(r, c, ' ');
                        bestMove = {r, c};
                        return depth - 10000;
                    }
                    Move dummy;
                    int eval = minimax(board, depth - 1, true,
                                       aiPlayer, humanPlayer, alpha, beta, winLength, dummy);
                    board.makeMove(r, c, ' ');

                    if (eval < minEval) {
                        minEval = eval;
                        bestMove = {r, c};
                    }
                    beta = std::min(beta, eval);
                    if (beta <= alpha) return minEval;
                }
            }
        }
        return minEval;
    }
}

Move getBestMove(Board board, char aiPlayer, char humanPlayer, int winLength, int depthLimit) {
    Move bestMove = {-1, -1};
    int depth = (depthLimit == -1) ? (board.getSize() <= 3 ? 9 : 4) : depthLimit;

    minimax(board, depth, true, aiPlayer, humanPlayer,
            std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), winLength, bestMove);

    return bestMove;
}
