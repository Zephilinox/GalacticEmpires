#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

//STD

//3RD
#include <SFML/Graphics.hpp>

//SELF

class SolarSystem : public sf::Drawable
{
public:
    SolarSystem();
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::VertexArray m_grid;
};

#endif //SOLARSYSTEM_HPP
