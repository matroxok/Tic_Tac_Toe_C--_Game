#include <clocale>
#include <iostream>
#include <limits>
#include <string>
#include "game.h"

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif

void configureConsole() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
    std::setlocale(LC_ALL, ".UTF-8");
}

int readInt(const std::string& prompt, int minValue) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= minValue) {
            return value;
        }

        std::cout << "Nieprawidłowa wartość. Spróbuj ponownie.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

bool askPlayAgain() {
    char choice;
    while (true) {
        std::cout << "\nCo dalej?\n";
        std::cout << "1. Nowa gra\n";
        std::cout << "2. Wyjście\n";
        std::cout << "Wybierz opcję: ";

        if (std::cin >> choice) {
            if (choice == '1') return true;
            if (choice == '2') return false;
        }

        std::cout << "Nieprawidłowy wybór. Wpisz 1 albo 2.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

int main() {
    configureConsole();

    std::cout << "Kółko i krzyżyk\n";
    std::cout << "Projektowanie i Analiza Algorytmów - Mateusz Kozera 281801\n";

    bool playAgain = true;
    while (playAgain) {
        int size = readInt("\nPodaj rozmiar planszy: ", 1);
        int winLength = readInt("Podaj ile znaków w rzędzie potrzeba do wygranej: ", 1);

        while (winLength > size) {
            std::cout << "Liczba znaków do wygranej nie może być większa niż rozmiar planszy.\n";
            winLength = readInt("Podaj ile znaków w rzędzie potrzeba do wygranej: ", 1);
        }

        Game gra(size, winLength);
        gra.run();

        playAgain = askPlayAgain();
    }

    std::cout << "Do zobaczenia!\n";

    return 0;
}
