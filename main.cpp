#include <cmath>
#include <ctime>

#include <lua.hpp>
#include <LuaBridge/LuaBridge.h>
#include "GalacticEmpires.hpp"

int main()
{
    std::srand(std::time(0));
    GalacticEmpires game;
    game.run();
}
