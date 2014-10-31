#include "States/SplashState.hpp"

SplashState::SplashState(sf::RenderWindow& window, zge::StateCollection& stateCollection)
    : BaseState(window, stateCollection)
{
    m_stateID = "SplashState";
}

void SplashState::handleEvent(const sf::Event& event)
{

}

void SplashState::update(float dt)
{
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

}
