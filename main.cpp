#include <cmath>
#include <ctime>
#include <iostream>

#include "GalacticEmpires.hpp"

int main()
{
    std::srand(unsigned(std::time(nullptr)));

    try
    {
        GalacticEmpires game;
        game.run();
    }
    catch (std::exception& e)
    {
        std::cout << e.what() << "\n";
    }
}
