#include "TestState.hpp"

//STD
#include <cmath>
#include <iostream>

//3RD

//SELF

TestState::TestState(GalacticEmpires* galpires)
    : m_galpires(galpires)
    , rs(sf::Vector2f(std::rand()%200, std::rand()%200))
{
    rs.setFillColor(sf::Color(std::rand()%255, std::rand()%255, std::rand()%255));
    std::cout << "Window width = " << m_galpires->getWindow()->getSize().x << "\n";
}

void TestState::handleEvent(const sf::Event& e)
{
    switch(e.type)
    {
        default:
        {
            break;
        }
    }
}

void TestState::update(float dt)
{
    rs.move(1*dt, 1*dt);
}

void TestState::draw(sf::RenderWindow& window) const
{
    window.draw(rs);
}
