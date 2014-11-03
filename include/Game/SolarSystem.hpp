#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

#include <unordered_map>
#include <tuple>

#include <SFML/Graphics.hpp>

#include "GalacticEmpires.hpp"

typedef sf::Vector2i coordinates;

struct key_hash : public std::unary_function<coordinates, std::size_t>
{
    std::size_t operator()(const coordinates& coord) const
    {
        return coord.x ^ coord.y;
    }
};

struct key_equal : public std::binary_function<coordinates, coordinates, bool>
{
    bool operator()(const coordinates& v0, const coordinates& v1) const
    {
        return (v0.x == v1.x &&
                v0.y == v1.y);
    }
};

typedef std::unordered_map<coordinates, sf::CircleShape, key_hash, key_equal> HexMap;

class SolarSystem : public sf::Drawable
{
public:
    SolarSystem(GalacticEmpires* galemp, sf::Vector2u center);
    void handleEvent(const sf::Event& e);
    void update(double dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    void genMap(sf::Vector2u center);
    void genHexLine(int lineHeight, int radius, sf::Vector2u center);

    GalacticEmpires* m_galemp;

    int m_systemRadius;
    float m_hexRadius;

    HexMap m_map;
    sf::CircleShape m_shape;
};

#endif //SOLARSYSTEM_HPP
