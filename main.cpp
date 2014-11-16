#include <cmath>
#include <ctime>
#include <iostream>

#include "GalacticEmpires.hpp"

int main()
{
    std::srand(std::time(0));

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
