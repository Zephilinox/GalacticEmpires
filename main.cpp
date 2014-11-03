#include <cmath>
#include <ctime>

#include "GalacticEmpires.hpp"

#include <Flowger.hpp>

int main()
{
    fgr_init("log.txt");
    fgr_log("test", FGR_DEBUG, PRINT_LINE | PRINT_TIME);
    fgr_close();
    std::srand(std::time(0));
    GalacticEmpires game;
    game.run();
}
