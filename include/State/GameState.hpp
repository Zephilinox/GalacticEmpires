#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include <SFGUI/SFGUI.hpp>

#include "State/BaseState.hpp"
#include "Game/SolarSystem.hpp"
#include "GalacticEmpires.hpp"

class GameState : public BaseState
{
public:
    GameState(GalacticEmpires* galpires);
    void handleEvent(const sf::Event& e) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;
    void onActive() override;
    void onInactive() override;

private:
    GalacticEmpires* m_galpires;

    sfg::Window::Ptr m_guiWindow;

    SolarSystem m_solarSystem;
};

#endif //GAMESTATE_HPP
