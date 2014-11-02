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
    int mapRadius = 3;
    for (int i = -mapRadius; i <= mapRadius; ++i)
    {
        genHexLine(i, mapRadius);
    }

    std::cout << "hexes: " << m_map.size() << "\n";
}

void SolarSystem::genHexLine(int lineHeight, int radius)
{
    int lineWidth = radius*2 + 1 - std::abs(lineHeight);

    for (int i = 0; i < lineWidth; ++i)
    {
        sf::Vector2f coords(-radius + i, lineHeight);

        if (lineHeight < 0)
        {
            coords.x -= lineHeight;
        }

        std::cout << "[" << coords.x << ", " << coords.y << "], ";
    }
    std::cout << "\n";
    /*float radius = 64;
    float height = 2 * radius; //top to bottom
    float width = Vector::degToVector(60).x * radius * 2; //left to right

    sf::CircleShape hexTemplate(radius, 6);
    hexTemplate.setOrigin(radius, radius);
    hexTemplate.setFillColor(sf::Color(255, 0, 0, 50));
    hexTemplate.setOutlineColor(sf::Color::White);
    hexTemplate.setOutlineThickness(-2);
    hexTemplate.setPosition(size.x / 2.f, size.y / 2.f);

    int mapRadius = 2;
    for (int i = 0; i <= mapRadius; ++i)
    {
        for (int y = -i; y <= i; ++y)
        {
            for (int x = -i; x <= i; ++x)
            {
                std::cout << i << ", " << y << ", " << x << "\n";
                auto hex = hexTemplate;
                coordinates coords(x, y);
                sf::Vector2f offset;
                if (y == 0)
                {
                    offset = sf::Vector2f(coords.x * width, coords.y * height);
                }
                else
                {
                    offset = sf::Vector2f(coords.x * width * 0.5, coords.y * height);
                }
                std::cout << offset.x << ", " << offset.y << "\n\n";

                hex.move(offset);
                m_map[coords] = hex;
            }
        }
        std::cout << "\n";
    }*/
}
