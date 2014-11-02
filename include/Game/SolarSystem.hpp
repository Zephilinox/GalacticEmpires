#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

#include <SFML/Graphics.hpp>

class SolarSystem : public sf::Drawable
{
public:
    SolarSystem(sf::Vector2u size);
    void handleEvent(const sf::Event& e);
    void update(double dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    void genMap(sf::Vector2u size);
    std::vector<sf::CircleShape> m_map;
    sf::ConvexShape m_shape;
};

#endif //SOLARSYSTEM_HPP
