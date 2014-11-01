#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

#include <SFML/Graphics.hpp>

class SolarSystem : public sf::Drawable
{
public:
    SolarSystem();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::VertexArray m_grid;
};

#endif //SOLARSYSTEM_HPP
