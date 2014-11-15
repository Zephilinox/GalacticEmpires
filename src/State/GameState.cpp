#include "State/GameState.hpp"

GameState::GameState(GalacticEmpires* galemp)
    : m_galemp(galemp)
    , m_universe(m_galemp)
    , m_camera(m_galemp)
{
}

void GameState::handleEvent(const sf::Event& e)
{
    m_camera.handleEvent(e);
    m_universe.handleEvent(e);
}

void GameState::update(float dt)
{
    m_camera.update(dt);
    m_universe.update(dt);
}

void GameState::draw(sf::RenderWindow& window) const
{
    m_universe.draw(window);
}

void GameState::onActive()
{
}

void GameState::onInactive()
{
}
