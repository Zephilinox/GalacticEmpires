#include "State/GameState.hpp"

GameState::GameState(GalacticEmpires* galpires)
    : m_galpires(galpires)
    , m_guiWindow(sfg::Window::Create())
    , m_solarSystem(m_galpires->getWindow()->getSize())
{
    sf::Vector2u windowSize = m_galpires->getWindow()->getSize();
    m_guiWindow->SetAllocation(sf::FloatRect(windowSize.x * 0.3, windowSize.y * 0.1, windowSize.x * 0.4, windowSize.y * 0.8));
}

void GameState::handleEvent(const sf::Event& e)
{
    m_guiWindow->HandleEvent(e);
    m_solarSystem.handleEvent(e);
}

void GameState::update(float dt)
{
    m_guiWindow->Update(dt);
    m_solarSystem.update(dt);
}

void GameState::draw(sf::RenderWindow& window) const
{
    window.draw(m_solarSystem);
}

void GameState::onActive()
{
    m_guiWindow->Show(true);
}

void GameState::onInactive()
{
    m_guiWindow->Show(false);
}
