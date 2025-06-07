#include <iostream>
#include "board.h"
#include "game.h"

int main() {
    int size, winLength;
    std::cout << "Podaj rozmiar planszy: ";
    std::cin >> size;
    std::cout << "Podaj ile znaków w rzędzie potrzeba do wygranej: ";
    std::cin >> winLength;

   
    Game gra(size, winLength);
    gra.run();

    return 0;
}
