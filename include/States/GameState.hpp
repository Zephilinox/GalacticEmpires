#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>
#include <ZGE/State/BaseState.hpp>
#include <ZGE/State/StateCollection.hpp>

//SELF
#include "Game/SolarSystem.hpp"

class GameState : public zge::BaseState
{
public:
    GameState();
    GameState(sf::RenderWindow* window, zge::StateCollection* stateCollection);
    void handleEvent(const sf::Event& event) override;
    void update(float dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void postDraw() override;

private:
    SolarSystem m_solSys;
};

#endif //GAMESTATE_HPP
