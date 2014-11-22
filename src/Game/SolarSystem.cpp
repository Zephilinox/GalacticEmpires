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
    , m_hoverHex(invalidCoordinates)
    , m_clickHex(invalidCoordinates)
{
	//Lua stuff
    LuaState luaState;

    luaState.loadFile("data/scripts/SolarSystem.lua");
    luaState.execute();

    m_systemRadius = luaState.getGlobal("SolarSystem.systemRadius").cast<int>();

	//Colour stuff
	m_darkerHexCol = sf::Color(std::rand() % 200, std::rand() % 200, std::rand() % 200, 255);
	m_lighterHexCol = m_darkerHexCol;
	m_lighterHexCol.r += 56;
	m_lighterHexCol.g += 56;
	m_lighterHexCol.b += 56;

    //Automatically generate hexagonal texture
	//This probably shouldn't be in the source, just for easily generating hex images
	sf::Texture hexTex;
	hexTex.loadFromFile("data/textures/hex.png");
    if (m_hexRadius*2 != hexTex.getSize().x)
    {
        std::cout << "Could not find valid hex texture, automatically generating...\n";
        sf::CircleShape hexPic(m_hexRadius, 6);
        hexPic.setOrigin(m_hexRadius, m_hexRadius);
        hexPic.setFillColor(sf::Color::White);
        hexPic.setOutlineColor(sf::Color::Black);
        hexPic.setOutlineThickness(-4 * SIZE_FACTOR);
        hexPic.setPosition(0, 0);

        sf::RenderTexture rt;
        rt.create(m_hexRadius * 2, m_hexRadius * 2);
        rt.setView(sf::View(sf::Vector2f(0, 0), sf::Vector2f(m_hexRadius * 2, m_hexRadius * 2)));
        rt.clear(sf::Color::Transparent);
        rt.draw(hexPic);
        rt.display();
        rt.getTexture().copyToImage().saveToFile("data/textures/hex.png");
    }

	//Gen the hexes
    m_map.genMap(m_systemRadius, m_hexRadius);
    m_map.setColor(m_darkerHexCol);

	//Gen the solar system shape
	m_shape.setRadius(std::abs(m_map[coordinates(-m_systemRadius, 0)].getPosition().x) + m_hexRadius * 2);
	m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());
	sf::Color c = m_lighterHexCol;
	c.a = 100 + std::rand() % 156;
	m_shape.setFillColor(c);
	m_shape.setOutlineColor(sf::Color(0, 0, 0, 255));
	m_shape.setOutlineThickness(8 * SIZE_FACTOR);
    m_shape.setPosition(0, 0);
    m_shape.rotate(30);
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

				m_map[m_clickHex].setColor(m_darkerHexCol);
                m_clickHex = m_map.findClosestHex(mousePos);
                m_map[m_clickHex].setColor(sf::Color(100, 100, 255, 255));
            }

            break;
        }

        case sf::Event::MouseMoved:
        {
            Vector mousePos = m_galemp->getWindow()->mapPixelToCoords(sf::Mouse::getPosition(*m_galemp->getWindow()));

            float solDistance = Vector(m_shape.getPosition() - mousePos).length();

            if (solDistance < m_shape.getRadius())
            {
				m_map[m_hoverHex].setColor(m_darkerHexCol);
                m_hoverHex = m_map.findClosestHex(mousePos);
                m_map[m_hoverHex].setColor(sf::Color(100, 255, 100, 255));

                if (m_hoverHex == m_clickHex)
                {
                    m_map[m_clickHex].setColor(sf::Color(255, 100, 100, 255));
                }
                else
                {
                    m_map[m_clickHex].setColor(sf::Color(100, 100, 255, 255));
                }
            }
            else
            {
				m_map[m_hoverHex].setColor(m_darkerHexCol);
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
    target.draw(m_map, states);
}
