#ifndef GALACTICEMPIRES_HPP
#define GALACTICEMPIRES_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF
#include "LuaState.hpp"

class GalacticEmpires
{
public:
    GalacticEmpires();
    void run();

private:
    void gameLoop();
    void handleEvent(const sf::Event& e);
    void update(float dt);
    void draw();

    zge::LuaState m_lua;

    sf::RenderWindow m_window;
    sf::Event m_event;
    sf::Clock m_frameTime;
    sf::Time m_prevFrameTime;
};

#endif //GALACTICEMPIRES_HPP
