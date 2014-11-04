#include "State/GameState.hpp"

GameState::GameState(GalacticEmpires* galemp)
    : m_galemp(galemp)
    , m_guiWindow(sfg::Window::Create())
    , m_solarSystem(m_galemp, m_galemp->getWindow()->getSize())
    , m_camera(m_galemp->getWindow())
{
    sf::Vector2u windowSize = m_galemp->getWindow()->getSize();
    m_guiWindow->SetAllocation(sf::FloatRect(windowSize.x * 0.3, windowSize.y * 0.1, windowSize.x * 0.4, windowSize.y * 0.8));
    m_guiWindow->Show(false);
}

void GameState::handleEvent(const sf::Event& e)
{
    m_guiWindow->HandleEvent(e);
    m_camera.handleEvent(e);
    m_solarSystem.handleEvent(e);
}

void GameState::update(float dt)
{
    m_guiWindow->Update(dt);
    m_camera.update(dt);
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
