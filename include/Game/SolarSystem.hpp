#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

#include <unordered_map>
#include <tuple>

#include <SFML/Graphics.hpp>

typedef std::tuple<int, int> coordinates;

struct key_hash : public std::unary_function<coordinates, std::size_t>
{
    std::size_t operator()(const coordinates& coord) const
    {
        return std::get<0>(coord) ^ std::get<1>(coord);
    }
};

struct key_equal : public std::binary_function<coordinates, coordinates, bool>
{
    bool operator()(const coordinates& v0, const coordinates& v1) const
    {
        return (std::get<0>(v0) == std::get<0>(v1) &&
              std::get<1>(v0) == std::get<1>(v1));
    }
};

typedef std::unordered_map<coordinates, sf::CircleShape, key_hash, key_equal> HexMap;

class SolarSystem : public sf::Drawable
{
public:
    SolarSystem(sf::Vector2u size);
    void handleEvent(const sf::Event& e);
    void update(double dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    void genMap(sf::Vector2u size);
    HexMap m_map;
};

#endif //SOLARSYSTEM_HPP
