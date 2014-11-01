#include "State/SplashState.hpp"

SplashState::SplashState(GalacticEmpires* galpires)
    : m_galpires(galpires)
    , m_guiWindow(sfg::Window::Create(sfg::Window::NO_STYLE))
    , m_guiProgBar(sfg::ProgressBar::Create())
{
    m_guiWindow->Add(m_guiProgBar);
    m_guiWindow->SetAllocation(sf::FloatRect(30, 720/2 - 30, 1280 - 60, 60));
}

void SplashState::handleEvent(const sf::Event& e)
{
    m_guiWindow->HandleEvent(e);
}

void SplashState::update(float dt)
{
    m_guiProgBar->SetFraction(m_clock.getElapsedTime().asSeconds() / 4.f);
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
