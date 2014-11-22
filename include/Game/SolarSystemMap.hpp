#ifndef SOLARSYSTEMMAP_HPP
#define SOLARSYSTEMMAP_HPP

#include <unordered_map>
#include <tuple>
#include <limits>

#include <SFML/Graphics.hpp>

typedef sf::Vector2i coordinates;

namespace std
{
    template <>
    struct hash<coordinates>
    {
        std::size_t operator()(const coordinates& coord) const
        {
            return coord.x ^ coord.y;
        }
    };
}

const coordinates invalidCoordinates = coordinates(std::numeric_limits<int>::max(), std::numeric_limits<int>::max());

typedef std::unordered_map<coordinates, sf::Sprite> HexMap;

class SolarSystemMap : public sf::Drawable
{
public:
    SolarSystemMap();
    sf::Sprite& operator[](coordinates coord);

    bool handleEvent(const sf::Event& e);
    void update(double dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

    void genMap(unsigned systemRadius, unsigned hexRadius);

    coordinates findClosestHex(sf::Vector2f pos);

    void setColor(sf::Color c);

    HexMap& getHexMap();

private:
    void genHexLine(int lineHeight);

    sf::Texture m_hexTex;

    unsigned m_systemRadius;
    unsigned m_hexRadius;

    HexMap m_map;
};

#endif //SOLARSYSTEMMAP_HPP
