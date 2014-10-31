#include "States/SplashState.hpp"

SplashState::SplashState(sf::RenderWindow& window, zge::StateCollection& stateCollection)
    : BaseState(window, stateCollection)
    , m_guiWindow(sfg::Window::Create(sfg::Window::Style::TOPLEVEL))
    , m_guiSpinner(sfg::Spinner::Create())
{
    m_stateID = "SplashState";
    m_guiWindow->SetTitle("SplashState");
    m_guiWindow->SetAllocation(sf::FloatRect(1280/8, 720/8, 1280/4, 720/4));
    m_guiWindow->Add(m_guiSpinner);
    m_guiSpinner->Start();
}

void SplashState::handleEvent(const sf::Event& event)
{
    m_guiWindow->HandleEvent(event);
}

void SplashState::update(float dt)
{
    m_guiWindow->Update(dt);
}

void SplashState::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RectangleShape rs({100, 100});
    rs.setPosition(200, 200);
    rs.setFillColor(sf::Color::Red);
    target.draw(rs, states);
}

void SplashState::postDraw()
{
    if (m_clock.getElapsedTime().asSeconds() > 1.f)
    {
        m_stateCollection.pop();
    }
}
