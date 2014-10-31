//STD

//3RD
#include "ini_parser.hpp"

//SELF
#include "GalacticEmpires.hpp"

int main()
{
    ini_parser parser("settings.ini");
    parser.set_value("fullscreen", false, "Video");
    //GalacticEmpires game;
    //game.run();
}
