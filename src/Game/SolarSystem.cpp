#include "Game/SolarSystem.hpp"

#include <iostream>

#include "Math/Vector.hpp"

SolarSystem::SolarSystem(sf::Vector2u size)
{
    genMap(sf::Vector2u(size.x, size.y));
}

void SolarSystem::handleEvent(const sf::Event& e)
{

}

void SolarSystem::update(double dt)
{

}

void SolarSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& hex : m_map)
    {
        target.draw(hex, states);
    }

    target.draw(m_shape, states);
}

void SolarSystem::genMap(sf::Vector2u size)
{
    sf::CircleShape hex(64, 6);
    hex.setOrigin(64, 64);
    hex.setFillColor(sf::Color(0, 0, 0, 0));
    hex.setOutlineColor(sf::Color::White);
    hex.setOutlineThickness(-2);

    float height = 128; //top to bottom
    float width = Vector::degToVector(60).x*(height/2)*2; //left to right

    hex.setPosition(size.x / 2.f, size.y / 2.f);
    hex.setOutlineColor(sf::Color::White);
    m_map.push_back(hex);

    auto hex2 = hex;
    hex2.setOutlineColor(sf::Color::Blue);
    hex2.move(-0.5*width, height*0.75);
    m_map.push_back(hex2);

    auto hex3 = hex;
    hex3.setOutlineColor(sf::Color::Green);
    hex3.move(0.5*width, height*0.75);
    m_map.push_back(hex3);

    auto hex4 = hex;
    hex4.setOutlineColor(sf::Color::Yellow);
    hex4.move(-0.5*width, height*-0.75);
    m_map.push_back(hex4);

    auto hex5 = hex;
    hex5.setOutlineColor(sf::Color::Magenta);
    hex5.move(-width, 0);
    m_map.push_back(hex5);

    auto hex6 = hex;
    hex6.setOutlineColor(sf::Color::Cyan);
    hex6.move(0.5*width, height*-0.75);
    m_map.push_back(hex6);

    auto hex7 = hex;
    hex7.setOutlineColor(sf::Color::Red);
    hex7.move(width, 0);
    m_map.push_back(hex7);

    m_shape.setPointCount(6);
    float exteriorAngle = 60;
    m_shape.setOrigin(0, 0);
    m_shape.setFillColor(sf::Color(0, 0, 0, 0));
    m_shape.setOutlineColor(sf::Color::Black);
    m_shape.setOutlineThickness(2);

    for (unsigned i = 0; i < 6; ++i)
    {
        Vector angleDir = Vector::degToVector(exteriorAngle * i);
        std::cout << angleDir.x*32 << ", " << angleDir.y*32 << "\n";
        m_shape.setPoint(i, sf::Vector2f(angleDir.x, angleDir.y) * 32.f);
    }

    m_shape.setPosition(size.x/2 + width, size.y/2);

}
