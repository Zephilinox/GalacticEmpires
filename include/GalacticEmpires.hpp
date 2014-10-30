#ifndef GALACTICEMPIRES_HPP
#define GALACTICEMPIRES_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/LuaState.hpp>
#include <SFGUI/SFGUI.hpp>

//SELF
#include "Settings.hpp"

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

    sf::RenderWindow m_window;

    zge::LuaState m_lua;
    Settings m_settings;
    sfg::SFGUI m_gui;
    sfg::Window::Ptr m_guiWindow;

    sf::Event m_event;
    sf::Clock m_frameTime;
    sf::Time m_prevFrameTime;
};

#endif //GALACTICEMPIRES_HPP
