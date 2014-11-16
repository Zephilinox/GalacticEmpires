#ifndef GALACTICEMPIRES_HPP
#define GALACTICEMPIRES_HPP

#include <SFML/Graphics.hpp>

#include "Helper/Settings.hpp"
#include "Helper/GUIManager.hpp"
#include "State/StateManager.hpp"
#include "FPSDisplay.hpp"

class GalacticEmpires
{
public:
    GalacticEmpires();

    void run();

    void handleError(std::string err);

    sf::RenderWindow* getWindow();
    StateManager<GalacticEmpires>* getStateManager();
    Settings* getSettings();

private:
    void loadSettings();

    void gameLoop();
    void handleEvent(const sf::Event& e);
    void update(float dt);
    void draw();

    sf::RenderWindow m_window;
    GUIManager m_guiManager;
    StateManager<GalacticEmpires> m_stateMan;
    std::shared_ptr<BaseState> m_curState;
    FPSDisplay m_fps;

    sf::Event m_event;
    sf::Clock m_frameTime;
    sf::Time m_prevFrameTime;

    std::string m_exceptionErrorMessage;

    Settings m_settings;

    static const unsigned VERSION_MAJOR = 0;
    static const unsigned VERSION_MINOR = 0;
    static const unsigned VERSION_REVISION = 0;
};

#endif //GALACTICEMPIRES_HPP
