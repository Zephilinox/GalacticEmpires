#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

#include <SFML/Graphics.hpp>

class SolarSystem : public sf::Drawable
{
public:
    SolarSystem();
    void handleEvent(const sf::Event& e);
    void update(double dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::VertexArray m_grid;
};

#endif //SOLARSYSTEM_HPP
