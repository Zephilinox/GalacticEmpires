#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP

#include <memory>
#include <vector>

#include "GalacticEmpires.hpp"
#include "Game/SolarSystem.hpp"

class Universe
{
public:
    Universe(GalacticEmpires* galemp);
    bool handleEvent(const sf::Event& e);
    void update(float dt);
    void draw(sf::RenderWindow& window) const;

private:
    void genSolarSystems();

    GalacticEmpires* m_galemp;
    std::vector<std::shared_ptr<SolarSystem>> m_solarSystems;
    std::shared_ptr<SolarSystem> m_curSolarSystem;
};

#endif //UNIVERSE_HPP
