#include "State/SplashState.hpp"

#include "State/MainMenuState.hpp"

SplashState::SplashState(GalacticEmpires* galemp)
    : m_galemp(galemp)
{
}

void SplashState::handleEvent(const sf::Event& e)
{
}

void SplashState::update(float dt)
{
    if (m_clock.getElapsedTime().asSeconds() >= 0.5f)
    {
        m_galemp->getStateManager()->pop();
        m_galemp->getStateManager()->push<MainMenuState>(m_galemp);
    }
}

void SplashState::draw(sf::RenderWindow& window) const
{

}

void SplashState::onActive()
{
}

void SplashState::onInactive()
{
}
