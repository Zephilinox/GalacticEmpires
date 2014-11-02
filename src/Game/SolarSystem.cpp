#include "Game/SolarSystem.hpp"

#include <iostream>

#include "Math/Vector.hpp"

SolarSystem::SolarSystem(sf::Vector2u center)
{
    genMap(sf::Vector2u(center.x, center.y));
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

void SolarSystem::genMap(sf::Vector2u center)
{
    int mapRadius = 3;
    for (int i = -mapRadius; i <= mapRadius; ++i)
    {
        genHexLine(i, mapRadius, center);
    }

    std::cout << "hexes: " << m_map.size() << "\n";
}

void SolarSystem::genHexLine(int lineHeight, int radius, sf::Vector2u center)
{
    float hexRadius = 16;
    float hexHeight = hexRadius * 2;
    float hexWidth = hexHeight * Vector::degToVector(60).x;

    sf::CircleShape hexTemplate(hexRadius, 6);
    hexTemplate.setOrigin(hexRadius, hexRadius);
    hexTemplate.setFillColor(sf::Color(255, 0, 0, 50));
    hexTemplate.setOutlineColor(sf::Color::White);
    hexTemplate.setOutlineThickness(-2);
    hexTemplate.setPosition(center.x / 2.f, center.y / 2.f);

    int lineWidth = radius*2 + 1 - std::abs(lineHeight);
    for (int i = 0; i < lineWidth; ++i)
    {
        coordinates coords(-radius + i, lineHeight);

        if (lineHeight < 0)
        {
            coords.x -= lineHeight;
        }

        auto hex = hexTemplate;
        sf::Vector2f offset(hexWidth, hexHeight);
        hex.move(coords.x * offset.x, coords.y * offset.y * 0.75);

        if (lineHeight % 2)
        {
            offset.x /= 2;

            if (lineHeight > 2)
            {
                hex.move(offset.x * (lineHeight - 1), 0);
            }
            else if (lineHeight < -2)
            {
                hex.move(offset.x * (lineHeight + 1), 0);
            }
        }
        else
        {
            if (lineHeight > 2)
            {
                hex.move(offset.x * (lineHeight/2 - 1), 0);
            }
            else if (lineHeight < -2)
            {
                hex.move(offset.x * (lineHeight/2 + 1), 0);
            }
        }

        if (lineHeight < 0)
        {
            hex.move(-offset.x, 0);
        }
        else if (lineHeight > 0)
        {
            hex.move(offset.x, 0);
        }

        m_map[coords] = hex;
        //std::cout << "[" << coords.x << ", " << coords.y << "], ";
    }
    //std::cout << "\n";
}
