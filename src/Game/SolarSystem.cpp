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
        target.draw(hex.second, states);
    }
}

void SolarSystem::genMap(sf::Vector2u size)
{
    float radius = 64;
    float height = 2 * radius; //top to bottom
    float width = Vector::degToVector(60).x * radius * 2; //left to right
    unsigned numHexes = 2;

    sf::CircleShape hexTemplate(radius, 6);
    hexTemplate.setOrigin(radius, radius);
    hexTemplate.setFillColor(sf::Color(255, 0, 0, 255));
    hexTemplate.setOutlineColor(sf::Color::White);
    hexTemplate.setOutlineThickness(-2);
    hexTemplate.setPosition(size.x / 2.f, size.y / 2.f);

    for (unsigned i = 0; i < numHexes; ++i)
    {
        std::cout << i << "\n";
        auto hex = hexTemplate;
        sf::Vector2f offset;

        hex.move(offset);
        m_map[coordinates(0, 0)] = hex;
        offset = sf::Vector2f(32, 32);
        hex.move(offset);
        m_map[coordinates(0, 1)] = hex;
    }
}
