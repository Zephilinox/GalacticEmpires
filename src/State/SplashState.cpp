#include "State/SplashState.hpp"

#include "State/MainMenuState.hpp"

SplashState::SplashState(GalacticEmpires* galpires)
    : m_galpires(galpires)
    , m_guiWindow(sfg::Window::Create(sfg::Window::NO_STYLE))
    , m_guiProgBar(sfg::ProgressBar::Create())
{
    m_guiWindow->Add(m_guiProgBar);

    sf::Vector2u windowSize = m_galpires->getWindow()->getSize();
    m_guiWindow->SetAllocation(sf::FloatRect(windowSize.x * 0.02, windowSize.y/2 - windowSize.x * 0.02,
                                             windowSize.x - windowSize.x * 0.04, windowSize.x * 0.04));
}

void SplashState::handleEvent(const sf::Event& e)
{
    m_guiWindow->HandleEvent(e);
}

void SplashState::update(float dt)
{
    if (m_clock.getElapsedTime().asSeconds() >= 0.5f)
    {
        m_galpires->getStateManager()->pop();
        m_galpires->getStateManager()->push<MainMenuState>(m_galpires);
    }
    else
    {
        m_guiProgBar->SetFraction(m_clock.getElapsedTime().asSeconds() / 0.5f);
    }

    m_guiWindow->Update(dt);
}

void SplashState::draw(sf::RenderWindow& window) const
{

}

void SplashState::onActive()
{
    m_guiWindow->Show(true);
}

void SplashState::onInactive()
{
    m_guiWindow->Show(false);
}
