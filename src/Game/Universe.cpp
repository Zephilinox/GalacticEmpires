#include "Game/Universe.hpp"

#include <cmath>

Universe::Universe(GalacticEmpires* galemp)
    : m_galemp(galemp)
{
    for (int i = 0; i < 10; ++i)
    {
        std::shared_ptr<SolarSystem> sys(std::make_shared<SolarSystem>(galemp));
        m_solarSystems.push_back(sys);
    }

    m_curSolarSystem = m_solarSystems[0];
}

void Universe::handleEvent(const sf::Event& e)
{
    if (m_curSolarSystem)
    {
        m_curSolarSystem->handleEvent(e);
    }
}

void Universe::update(float dt)
{
    if (m_curSolarSystem)
    {
        m_curSolarSystem->update(dt);
    }
}

void Universe::draw(sf::RenderWindow& window) const
{
    if (m_curSolarSystem)
    {
        window.draw(*m_curSolarSystem);
    }
}
