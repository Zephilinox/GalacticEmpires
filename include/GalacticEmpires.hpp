#ifndef GALACTICEMPIRES_HPP
#define GALACTICEMPIRES_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

//SELF

class GalacticEmpires
{
public:
    GalacticEmpires();
    void run();

private:
    void loadSettings();

    void gameLoop();
    void handleEvent(const sf::Event& e);
    void update(float dt);
    void draw();
    void postDraw();

    sf::RenderWindow m_window;

    sfg::SFGUI m_gui;
    sfg::Desktop m_guiDesktop;

    sf::Event m_event;
    sf::Clock m_frameTime;
    sf::Time m_prevFrameTime;

    static const unsigned VERSION_MAJOR = 0;
    static const unsigned VERSION_MINOR = 0;
    static const unsigned VERSION_REVISION = 0;
};

#endif //GALACTICEMPIRES_HPP
