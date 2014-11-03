#ifndef GALACTICEMPIRES_HPP
#define GALACTICEMPIRES_HPP

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

#include "State/StateManager.hpp"

class GalacticEmpires
{
public:
    GalacticEmpires();
    void run();

    sf::RenderWindow* getWindow();
    StateManager<GalacticEmpires>* getStateManager();

private:
    void loadSettings();
    void handleError(std::string err);

    void gameLoop();
    void handleEvent(const sf::Event& e);
    void update(float dt);
    void draw();

    sf::RenderWindow m_window;
    StateManager<GalacticEmpires> m_stateMan;
    std::shared_ptr<BaseState> m_curState;

    sfg::SFGUI m_gui;
    sfg::Desktop m_guiDesktop;
    sfg::Window::Ptr m_errorWindow;

    sf::Event m_event;
    sf::Clock m_frameTime;
    sf::Time m_prevFrameTime;

    std::string m_exceptionErrorMessage;

    static const unsigned VERSION_MAJOR = 0;
    static const unsigned VERSION_MINOR = 0;
    static const unsigned VERSION_REVISION = 0;
};

#endif //GALACTICEMPIRES_HPP
