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
	//Lua stuff
    LuaState luaState;

    luaState.loadFile("data/scripts/SolarSystem.lua");
    luaState.execute();

    m_systemRadius = luaState.getGlobal("SolarSystem.systemRadius").cast<int>();

	//Automatically generate hexagonal texture
	//This probably shouldn't be in the source, just for easily generating hex images
	sf::CircleShape hexPic(m_hexRadius, 6);
	hexPic.setOrigin(m_hexRadius, m_hexRadius);
	hexPic.setFillColor(sf::Color::White);
	hexPic.setOutlineColor(sf::Color::Black);
	hexPic.setOutlineThickness(-2 * SIZE_FACTOR);
	hexPic.setPosition(0, 0);

	sf::RenderTexture rt;
	rt.create(m_hexRadius * 2, m_hexRadius * 2);
	rt.setView(sf::View(sf::Vector2f(0, 0), sf::Vector2f(m_hexRadius * 2, m_hexRadius * 2)));
	rt.clear(sf::Color::Transparent);
	rt.draw(hexPic);
	rt.display();
	rt.getTexture().copyToImage().saveToFile("data/textures/hex.png");

	m_hexTex.loadFromFile("data/textures/hex.png");

	//Gen the hexes
    genMap();

	//Gen the solar system shape
	m_shape.setRadius(std::abs(m_map[coordinates(-m_systemRadius, 0)].getPosition().x) + m_hexRadius * 2);
	m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());
	m_shape.setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256, 50 + std::rand() % 50));
	m_shape.setOutlineColor(sf::Color(0, 0, 0, 200));
	m_shape.setOutlineThickness(8 * SIZE_FACTOR);
    m_shape.setPosition(0, 0);
    m_shape.rotate(30);

	//Define an invalid hex in the map
	sf::Sprite cs;

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

                m_map[m_clickHex].setColor(sf::Color(0, 0, 0, 100));
                m_clickHex = findClosestHex(mousePos);
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
                m_map[m_hoverHex].setColor(sf::Color(0, 0, 0, 100));
                m_hoverHex = findClosestHex(mousePos);
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
                m_map[m_hoverHex].setColor(sf::Color(0, 0, 0, 100));
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
	//'Circular' Hexagonal map consists of several lines of hexagons, equal to 2x the width of the system plus one for the center line.
	//In order to achieve this we loop from -width to +width, with 0 counting as the center line, eliminating the need to plus one.
    for (int i = -m_systemRadius; i <= m_systemRadius; ++i)
    {
        genHexLine(i, m_systemRadius);
    }
}

void SolarSystem::genHexLine(int lineHeight, int radius) //I don't know why we use radius instead of just using m_systemRadius
{
	//set the height (pointy vertex to center * 2) and add some extra pixels for padding
	float hexHeight = m_hexRadius * 2 + (16 * SIZE_FACTOR);
	//The width of the hex has to be multiplied by the vectorised x-component of 60 degrees in order to be accurate
    float hexWidth = hexHeight * Vector::degToVector(60).x;

	//Sort of a prototype pattern, use this template to initialise all hexes for this line
	sf::Sprite hexTemplate(m_hexTex);
    hexTemplate.setOrigin(m_hexRadius, m_hexRadius);
    hexTemplate.setColor(sf::Color(0, 0, 0, 100));
    hexTemplate.setPosition(0, 0);

	//The longest line is  the center, each line above or below it has one less hex in said line
	//We can find the max # of hexes in a line by doubling the radius and adding one for the center hex
	//We then simply subtract one per lineHeight, since it can be negative we need to std::abs it
    int lineWidth = radius*2 + 1 - std::abs(lineHeight);

    for (int i = 0; i < lineWidth; ++i)
	{
		//The x coord starts off at the left and goes right by adding the i which represents which hex in the line we are.
		//These coordinates are the axial coordinates of the hex
		coordinates coords(-radius + i, lineHeight); 

		//This code ensures that the x-axial coord is flipped when going below 0 (i.e. the top half of our hex map) in order to produce a hex-shaped hex map, rather than a trapezoid
        if (lineHeight < 0)
        {
            coords.x -= lineHeight;
        }

        auto hex = hexTemplate;
        sf::Vector2f offset(hexWidth, hexHeight);
		//We want to move each hex from the center by multiplying their axial coordinates by the offset, which is simply the width and height of a hex
		//We multiply the y-offset by 0.75 because of the staggering, two hexes on separate lines are not one hex away in height, they are 0.75 away as they are positioned to the left or right of the one above
        hex.move(coords.x * offset.x, coords.y * offset.y * 0.75);

		//If the line height is odd then we need to shift the x-position of the hexes to stagger them
        if (lineHeight % 2)
        {
            offset.x /= 2; //shift by half a hex, not a full one

			//Trial & Error, not sure how it works
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
			//Trial & Error, not sure how it works
            if (lineHeight > 2)
            {
                hex.move(offset.x * (lineHeight/2 - 1), 0);
            }
            else if (lineHeight < -2)
            {
                hex.move(offset.x * (lineHeight/2 + 1), 0);
            }
        }

		//Stagger the x-pos of the hexes at the top/bottom of the map in order for them to align correctly
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
	//The hover hex acts as the "last hex that we were closest to", which works nicely for optimisation
    if (m_hoverHex != invalidHexCoordinates &&
        Vector(m_map[m_hoverHex].getPosition() - pos).lengthSquared() < m_hexRadius*m_hexRadius)
    {
        return m_hoverHex;
    }

    float shortestHexDistance = std::numeric_limits<float>::max();
    coordinates closestHexCoord = invalidHexCoordinates;

    for (const auto hexPair : m_map)
    {
        float hexDistance = Vector(hexPair.second.getPosition() - pos).lengthSquared();
        if (hexDistance < m_hexRadius*m_hexRadius)
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
