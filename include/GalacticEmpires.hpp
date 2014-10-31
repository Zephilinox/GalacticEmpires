#ifndef GALACTICEMPIRES_HPP
#define GALACTICEMPIRES_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/State/StateHandler.hpp>
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

    Settings m_settings;
    zge::StateHandler m_stateHandler;

    sfg::SFGUI m_gui;
    sfg::Window::Ptr m_guiWindow;

    sf::Event m_event;
    sf::Clock m_frameTime;
    sf::Time m_prevFrameTime;
};

#endif //GALACTICEMPIRES_HPP
