#include "Game/SolarSystem.hpp"

#include <iostream>
#include <cmath>

#include "Math/Vector.hpp"
#include "Helper/LuaState.hpp"
#include "Helper/Utility.hpp"
#include "Helper/Constants.hpp"

SolarSystem::SolarSystem(GalacticEmpires* galemp)
    : m_galemp(galemp)
    , m_systemRadius(16)
	, m_hexRadius(32 * SIZE_FACTOR)
    , m_shape(0, 6)
    , m_hoverHex(invalidHexCoordinates)
    , m_clickHex(invalidHexCoordinates)
{
    LuaState luaState;

    luaState.loadFile("data/scripts/SolarSystem.lua");
    luaState.execute();

    m_systemRadius = luaState.getGlobal("SolarSystem.systemRadius").cast<int>();
    m_hexRadius = luaState.getGlobal("SolarSystem.hexRadius").cast<int>();
	m_hexRadius *= SIZE_FACTOR;

    genMap();

    m_shape.setRadius(std::abs(m_map[coordinates(-m_systemRadius, 0)].getPosition().x) + m_hexRadius*2);

    m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());
    m_shape.setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256, 50 + std::rand() % 50));
    m_shape.setOutlineColor(sf::Color(0, 0, 0, 200));
	m_shape.setOutlineThickness(8 * SIZE_FACTOR);
    m_shape.setPosition(0, 0);
    m_shape.rotate(30);

    sf::CircleShape cs(m_hexRadius, 6);
    cs.setPosition(sf::Vector2f(std::numeric_limits<float>::max(), std::numeric_limits<float>::max()));
    m_map[invalidHexCoordinates] = cs;
}

bool SolarSystem::handleEvent(const sf::Event& e)
{
    switch (e.type)
    {
        case sf::Event::MouseButtonPressed:
        {
            if (e.mouseButton.button == sf::Mouse::Left)
            {
                Vector mousePos = m_galemp->getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*m_galemp->getWindow()));

                m_map[m_clickHex].setFillColor(sf::Color(0, 0, 0, 100));
                m_clickHex = findClosestHex(mousePos);
                m_map[m_clickHex].setFillColor(sf::Color(100, 100, 255, 255));
            }

            break;
        }

        case sf::Event::MouseMoved:
        {
            Vector mousePos = m_galemp->getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*m_galemp->getWindow()));

            float solDistance = Vector(m_shape.getPosition() - mousePos).length();

            if (solDistance < m_shape.getRadius())
            {
                m_map[m_hoverHex].setFillColor(sf::Color(0, 0, 0, 100));
                m_hoverHex = findClosestHex(mousePos);
                m_map[m_hoverHex].setFillColor(sf::Color(100, 255, 100, 255));

                if (m_hoverHex == m_clickHex)
                {
                    m_map[m_clickHex].setFillColor(sf::Color(255, 100, 100, 255));
                }
                else
                {
                    m_map[m_clickHex].setFillColor(sf::Color(100, 100, 255, 255));
                }
            }
            else
            {
                m_map[m_hoverHex].setFillColor(sf::Color(0, 0, 0, 100));
            }
        }

        default:
        {
            break;
        }
    }
    return false;
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

void SolarSystem::genMap()
{
    for (int i = -m_systemRadius; i <= m_systemRadius; ++i)
    {
        genHexLine(i, m_systemRadius);
    }
}

void SolarSystem::genHexLine(int lineHeight, int radius)
{
	float hexHeight = m_hexRadius * 2 + (16 * SIZE_FACTOR);
    float hexWidth = hexHeight * Vector::degToVector(60).x;

    sf::CircleShape hexTemplate(m_hexRadius, 6);
    hexTemplate.setOrigin(m_hexRadius, m_hexRadius);
    hexTemplate.setFillColor(sf::Color(0, 0, 0, 100));
    hexTemplate.setOutlineColor(sf::Color(0, 0, 0, 200));
	hexTemplate.setOutlineThickness(4 * SIZE_FACTOR);
    hexTemplate.setPosition(0, 0);

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

coordinates SolarSystem::findClosestHex(sf::Vector2f pos)
{
    //If the distance to the hover hex is less than the hex radius then we're still in the same hex, so we don't need to bother finding the new closest one.
    if (m_hoverHex != invalidHexCoordinates &&
        Vector(m_map[m_hoverHex].getPosition() - pos).length() < m_hexRadius)
    {
        return m_hoverHex;
    }

    float shortestHexDistance = std::numeric_limits<float>::max();
    coordinates closestHexCoord = invalidHexCoordinates;

    for (const auto hexPair : m_map)
    {
        float hexDistance = Vector(hexPair.second.getPosition() - pos).length();
        if (hexDistance < m_hexRadius)
        {
            if (hexDistance < shortestHexDistance)
            {
                shortestHexDistance = hexDistance;
                closestHexCoord = hexPair.first;
            }
        }
    }

    return closestHexCoord;
}
