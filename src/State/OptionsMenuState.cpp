#include "State/OptionsMenuState.hpp"

OptionsMenuState::OptionsMenuState(GalacticEmpires* galemp)
    : m_galemp(galemp)
{
}

void OptionsMenuState::handleEvent(const sf::Event& e)
{
}

void OptionsMenuState::update(float dt)
{
}

void OptionsMenuState::draw(sf::RenderWindow& window) const
{

}

void OptionsMenuState::onActive()
{
}

void OptionsMenuState::onInactive()
{
}

void OptionsMenuState::exit()
{
    m_galemp->getStateManager()->pop();
}
