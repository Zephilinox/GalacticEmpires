#include "State/NewGameState.hpp"

NewGameState::NewGameState(GalacticEmpires* galpires)
    : m_galpires(galpires)
    , m_guiWindow(sfg::Window::Create())
{
    sf::Vector2u windowSize = m_galpires->getWindow()->getSize();
    m_guiWindow->SetAllocation(sf::FloatRect(windowSize.x * 0.3, windowSize.y * 0.1, windowSize.x * 0.4, windowSize.y * 0.8));
}

void NewGameState::handleEvent(const sf::Event& e)
{
    m_guiWindow->HandleEvent(e);
}

void NewGameState::update(float dt)
{
    m_guiWindow->Update(dt);
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
