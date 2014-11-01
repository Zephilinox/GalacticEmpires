#include "TestState.hpp"

TestState::TestState()
    : rs(sf::Vector2f(100, 100))
{

}

void TestState::handleEvent(const sf::Event& e)
{

}

void TestState::update(float dt)
{

}

void TestState::draw(sf::RenderWindow& window) const
{
    window.draw(rs);
}
