#ifndef SOLARSYSTEM_HPP
#define SOLARSYSTEM_HPP

#include <unordered_map>
#include <tuple>
#include <limits>

#include <SFML/Graphics.hpp>

#include "GalacticEmpires.hpp"
#include "Game/SolarSystemMap.hpp"

class SolarSystem : public sf::Drawable
{
public:
    SolarSystem(GalacticEmpires* galemp);
    bool handleEvent(const sf::Event& e);
    void update(double dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    GalacticEmpires* m_galemp;

    SolarSystemMap m_map;

    unsigned m_systemRadius;
    unsigned m_hexRadius;

    sf::CircleShape m_shape;

	sf::Color m_darkerHexCol = sf::Color::Black;
	sf::Color m_lighterHexCol = sf::Color::White;
    coordinates m_hoverHex;
    coordinates m_clickHex;
};

#endif //SOLARSYSTEM_HPP
