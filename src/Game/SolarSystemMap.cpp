#include "Game/SolarSystemMap.hpp"

#include "Helper/Math/Vector.hpp"
#include "Helper/Constants.hpp"

SolarSystemMap::SolarSystemMap()
{
    //Define an invalid hex in the map
    m_map[invalidCoordinates].setPosition(sf::Vector2f(std::numeric_limits<float>::max(), std::numeric_limits<float>::max()));
}

sf::Sprite& SolarSystemMap::operator[](coordinates coord)
{
    return m_map[coord];
}

bool SolarSystemMap::handleEvent(const sf::Event& e)
{
    return false;
}

void SolarSystemMap::update(double dt)
{

}

void SolarSystemMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& hexPair : m_map)
    {
        target.draw(hexPair.second, states);
    }
}

void SolarSystemMap::genMap(unsigned systemRadius, unsigned hexRadius)
{
    m_hexTex.loadFromFile("data/textures/hex.png");

    m_systemRadius = systemRadius;
    m_hexRadius = hexRadius;

    //'Circular' Hexagonal map consists of several lines of hexagons, equal to 2x the width of the system plus one for the center line.
    //In order to achieve this we loop from -width to +width, with 0 counting as the center line, eliminating the need to plus one.
    for (int i = -m_systemRadius; i <= int(m_systemRadius); ++i)
    {
        genHexLine(i);
    }
}

coordinates SolarSystemMap::findClosestHex(sf::Vector2f pos)
{
    static coordinates lastHex = invalidCoordinates;

    if (lastHex != invalidCoordinates &&
        Vector(m_map[lastHex].getPosition() - pos).lengthSquared() < m_hexRadius*m_hexRadius)
    {
        return lastHex;
    }

    float shortestHexDistance = std::numeric_limits<float>::max();
    coordinates closestHexCoord = invalidCoordinates;

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

bool SolarSystemMap::validCoordinate(coordinates coord)
{
	if (coord == invalidCoordinates)
	{
		return false;
	}

	if (m_map.count(coord))
	{
		return true;
	}

	return false;
}

void SolarSystemMap::setColor(sf::Color c)
{
    for (auto& hexPair : m_map)
    {
        hexPair.second.setColor(c);
    }
}

HexMap& SolarSystemMap::getHexMap()
{
    return m_map;
}

void SolarSystemMap::genHexLine(int lineHeight)
{
    //set the height (pointy vertex to center * 2) and add some extra pixels for padding
    float hexHeight = m_hexRadius * 2 + (16 * SIZE_FACTOR);
    //The width of the hex has to be multiplied by the vectorised x-component of 60 degrees in order to be accurate
    float hexWidth = hexHeight * Vector::degToVector(60).x;

    //Sort of a prototype pattern, use this template to initialise all hexes for this line
    sf::Sprite hexTemplate(m_hexTex);
    hexTemplate.setOrigin(m_hexRadius, m_hexRadius);
    hexTemplate.setPosition(0, 0);

    //The longest line is  the center, each line above or below it has one less hex in said line
    //We can find the max # of hexes in a line by doubling the radius and adding one for the center hex
    //We then simply subtract one per lineHeight, since it can be negative we need to std::abs it
    int lineWidth = m_systemRadius*2 + 1 - std::abs(lineHeight);

    for (int i = 0; i < lineWidth; ++i)
    {
        //The x coord starts off at the left and goes right by adding the i which represents which hex in the line we are.
        //These coordinates are the axial coordinates of the hex
        coordinates coords(-m_systemRadius + i, lineHeight);

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
