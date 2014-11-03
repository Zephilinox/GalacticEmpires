#include <cmath>
#include <ctime>
#include <iostream>

#include "GalacticEmpires.hpp"

int main()
{
    std::srand(std::time(0));
    GalacticEmpires game;

    game.run();
}
