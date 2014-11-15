#include "State/NewGameState.hpp"

#include "State/GameState.hpp"

NewGameState::NewGameState(GalacticEmpires* galemp)
    : m_galemp(galemp)
{
}

bool NewGameState::handleEvent(const sf::Event& e)
{
    return false;
}

void NewGameState::update(float dt)
{
    m_galemp->getStateManager()->pop();
    m_galemp->getStateManager()->push<GameState>(m_galemp);
}

void NewGameState::draw(sf::RenderWindow& window) const
{

}

void NewGameState::onActive()
{
}

void NewGameState::onInactive()
{
}
