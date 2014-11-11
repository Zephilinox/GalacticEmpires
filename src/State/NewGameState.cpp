#include "State/NewGameState.hpp"

#include "State/GameState.hpp"

NewGameState::NewGameState(GalacticEmpires* galemp)
    : m_galemp(galemp)
    , m_guiWindow(sfg::Window::Create())
{
    sf::Vector2u windowSize = m_galemp->getWindow()->getSize();
    m_guiWindow->SetAllocation(sf::FloatRect(windowSize.x * 0.3, windowSize.y * 0.1, windowSize.x * 0.4, windowSize.y * 0.8));
}

void NewGameState::handleEvent(const sf::Event& e)
{
    m_guiWindow->HandleEvent(e);
}

void NewGameState::update(float dt)
{
    m_guiWindow->Update(dt);
    m_galemp->getStateManager()->pop();
    m_galemp->getStateManager()->push<GameState>(m_galemp);
}

void NewGameState::draw(sf::RenderWindow& window) const
{

}

void NewGameState::onActive()
{
    m_guiWindow->Show(true);
}

void NewGameState::onInactive()
{
    m_guiWindow->Show(false);
}
