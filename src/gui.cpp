#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "board.h"
#include "ai.h"

const int windowSize = 600;
int gridSize = 3;
int winLength = 3;
char currentPlayer = 'X';
Board board(gridSize, winLength);
bool gameOver = false;
bool inMenu = true;
sf::Font globalFont;

void drawGrid(sf::RenderWindow& window) {
    float cellSize = static_cast<float>(windowSize) / gridSize;
    sf::Color lineColor = sf::Color::Black;
    float thickness = 2.0f;

    for (int i = 1; i < gridSize; ++i) {
        sf::RectangleShape vLine(sf::Vector2f(thickness, windowSize));
        vLine.setPosition(i * cellSize - thickness / 2, 0);
        vLine.setFillColor(lineColor);
        window.draw(vLine);

        sf::RectangleShape hLine(sf::Vector2f(windowSize, thickness));
        hLine.setPosition(0, i * cellSize - thickness / 2);
        hLine.setFillColor(lineColor);
        window.draw(hLine);
    }
}

void drawMoves(sf::RenderWindow& window) {
    float cellSize = static_cast<float>(windowSize) / gridSize;
    for (int r = 0; r < gridSize; ++r) {
        for (int c = 0; c < gridSize; ++c) {
            char val = board.getCell(r, c);
            if (val != ' ') {
                sf::Text text(std::string(1, val), globalFont, cellSize * 0.6f);
                text.setFillColor(val == 'X' ? sf::Color::Red : sf::Color::Blue);
                text.setPosition(c * cellSize + cellSize * 0.2f, r * cellSize - cellSize * 0.1f);
                window.draw(text);
            }
        }
    }
}

void switchPlayer() {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

void handleClick(int mouseX, int mouseY) {
    if (gameOver) return;

    int cellX = mouseX / (windowSize / gridSize);
    int cellY = mouseY / (windowSize / gridSize);

    if (board.makeMove(cellY, cellX, currentPlayer)) {
        if (board.checkWin(cellY, cellX, currentPlayer)) {
            std::cout << "Gracz " << currentPlayer << " wygrywa!\n";
            gameOver = true;
        } else if (board.isFull()) {
            std::cout << "Remis!\n";
            gameOver = true;
        } else {
            switchPlayer();
            if (currentPlayer == 'O') {
                Move aiMove = getBestMove(board, 'O', 'X', winLength);
                board.makeMove(aiMove.row, aiMove.col, 'O');
                if (board.checkWin(aiMove.row, aiMove.col, 'O')) {
                    std::cout << "Gracz O (komputer) wygrywa!\n";
                    gameOver = true;
                } else if (board.isFull()) {
                    std::cout << "Remis!\n";
                    gameOver = true;
                } else {
                    switchPlayer();
                }
            }
        }
    }
}

void drawMenu(sf::RenderWindow& window) {
    window.clear(sf::Color::White);

    sf::Text title("Ustawienia gry", globalFont, 36);
    title.setFillColor(sf::Color::Black);
    title.setPosition((windowSize - title.getLocalBounds().width) / 2, 40);
    window.draw(title);

    sf::Text gridText("Rozmiar planszy: " + std::to_string(gridSize), globalFont, 24);
    gridText.setFillColor(sf::Color::Black);
    gridText.setPosition((windowSize - gridText.getLocalBounds().width) / 2, 120);
    window.draw(gridText);

    sf::Text winText("Wygrana przy: " + std::to_string(winLength), globalFont, 24);
    winText.setFillColor(sf::Color::Black);
    winText.setPosition((windowSize - winText.getLocalBounds().width) / 2, 170);
    window.draw(winText);

    sf::Text decreaseGrid("[-]", globalFont, 24);
    decreaseGrid.setFillColor(sf::Color::Red);
    decreaseGrid.setPosition(100, 120);
    window.draw(decreaseGrid);

    sf::Text increaseGrid("[+]", globalFont, 24);
    increaseGrid.setFillColor(sf::Color::Green);
    increaseGrid.setPosition(450, 120);
    window.draw(increaseGrid);

    sf::Text decreaseWin("[-]", globalFont, 24);
    decreaseWin.setFillColor(sf::Color::Red);
    decreaseWin.setPosition(100, 170);
    window.draw(decreaseWin);

    sf::Text increaseWin("[+]", globalFont, 24);
    increaseWin.setFillColor(sf::Color::Green);
    increaseWin.setPosition(450, 170);
    window.draw(increaseWin);

    sf::Text startButton("[ Start gry ]", globalFont, 28);
    startButton.setFillColor(sf::Color::Blue);
    startButton.setPosition((windowSize - startButton.getLocalBounds().width) / 2, 250);
    window.draw(startButton);

    sf::Text author("Mateusz Kozoera 281801", globalFont, 16);
    author.setFillColor(sf::Color::Black);
    author.setPosition((windowSize - author.getLocalBounds().width) / 2, windowSize - 40);
    window.draw(author);

    window.display();
}

void handleMenuClick(int x, int y) {
    if (y >= 250 && y <= 290 && x >= 200 && x <= 400) {
        board = Board(gridSize, winLength);
        inMenu = false;
    } else if (y >= 120 && y <= 150) {
        if (x < 160 && gridSize > 3) gridSize--;
        else if (x > 420 && gridSize < 10) gridSize++;
    } else if (y >= 170 && y <= 200) {
        if (x < 160 && winLength > 3) winLength--;
        else if (x > 420 && winLength < gridSize) winLength++;
    }
}

int main() {
    if (!globalFont.loadFromFile("arial.ttf")) {
        std::cerr << "Nie mozna zaladowac czcionki arial.ttf\n";
    }

    sf::RenderWindow window(sf::VideoMode(windowSize, windowSize), "Kolko i Krzyzyk");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (inMenu)
                    handleMenuClick(event.mouseButton.x, event.mouseButton.y);
                else
                    handleClick(event.mouseButton.x, event.mouseButton.y);
            }
        }

        if (inMenu)
            drawMenu(window);
        else {
            window.clear(sf::Color::White);
            drawGrid(window);
            drawMoves(window);
            window.display();
        }
    }

    return 0;
}
