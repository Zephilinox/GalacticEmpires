#include "Game/SolarSystem.hpp"

#include <iostream>

#include "Math/Vector.hpp"
#include "Helper/LuaState.hpp"
#include "Helper/Utility.hpp"

SolarSystem::SolarSystem(sf::Vector2u center)
    : m_systemRadius(16)
    , m_hexRadius(32)
    , m_shape(0, 6)
{
    LuaState luaState;
    int error = luaState.doFile("data/Lua/SolarSystem.lua");
    std::cout << "data/lua/SolarSystem.lua: " << luaErrorAsString(error) << "\n";

    luabridge::LuaRef solSys = luabridge::getGlobal(luaState.getRawState(), "SolarSystem");
    if (solSys["systemRadius"].isNumber())
    {
        m_systemRadius = solSys["systemRadius"].cast<int>();
    }

    if (solSys["hexRadius"].isNumber())
    {
        m_hexRadius = solSys["hexRadius"].cast<int>();
    }

    genMap(sf::Vector2u(center.x, center.y));

    m_shape.setRadius(m_hexRadius * (m_systemRadius * 2 + 2));

    m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());
    m_shape.setFillColor(sf::Color(255, 80, 0, 40));
    m_shape.setOutlineColor(sf::Color::Black);
    m_shape.setOutlineThickness(-2);
    m_shape.setPosition(center.x / 2.f, center.y / 2.f);
    m_shape.rotate(30);
}

void SolarSystem::handleEvent(const sf::Event& e)
{

}

void SolarSystem::update(double dt)
{

}

void SolarSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_shape, states);

    for (const auto& hex : m_map)
    {
        target.draw(hex.second, states);
    }
}

void SolarSystem::genMap(sf::Vector2u center)
{
    for (int i = -m_systemRadius; i <= m_systemRadius; ++i)
    {
        genHexLine(i, m_systemRadius, center);
    }

    std::cout << "hexes: " << m_map.size() << "\n";
}

void SolarSystem::genHexLine(int lineHeight, int radius, sf::Vector2u center)
{
    float hexHeight = m_hexRadius * 2;
    float hexWidth = hexHeight * Vector::degToVector(60).x;

    sf::CircleShape hexTemplate(m_hexRadius, 6);
    hexTemplate.setOrigin(m_hexRadius, m_hexRadius);
    hexTemplate.setFillColor(sf::Color(0, 0, 0, 0));
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
    }
}
