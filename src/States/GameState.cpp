#include "States/GameState.hpp"

GameState::GameState(sf::RenderWindow* window, zge::StateCollection* stateCollection)
    : BaseState(window, stateCollection)
{
    m_stateID = "GameState";
}

void GameState::handleEvent(const sf::Event& event)
{
}

void GameState::update(float dt)
{
}

void GameState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_solSys, states);
}

void GameState::postDraw()
{
}
