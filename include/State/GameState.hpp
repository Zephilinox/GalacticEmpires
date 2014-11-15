#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>

#include "State/BaseState.hpp"
#include "Game/Universe.hpp"
#include "GalacticEmpires.hpp"
#include "Helper/Camera.hpp"

class GameState : public BaseState
{
public:
    GameState(GalacticEmpires* galemp);
    bool handleEvent(const sf::Event& e) override;
    void update(float dt) override;
    void draw(sf::RenderWindow& window) const override;
    void onActive() override;
    void onInactive() override;

private:
    GalacticEmpires* m_galemp;

    Universe m_universe;

    Camera m_camera;
};

#endif //GAMESTATE_HPP
