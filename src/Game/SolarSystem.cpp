#include "Game/SolarSystem.hpp"

SolarSystem::SolarSystem(sf::Vector2u size)
    : m_grid(sf::Quads, (size.x / 32.f) * (size.y / 32.f) * 4)
{
    genMap(sf::Vector2u(size.x, size.y));
}

void SolarSystem::handleEvent(const sf::Event& e)
{

}

void SolarSystem::update(double dt)
{

}

void SolarSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(m_grid, states);
}

void SolarSystem::genMap(sf::Vector2u size)
{
    for (unsigned i = 0; i < size.x / 32; ++i)
    {
        for (unsigned j = 0; j < size.y / 32; ++j)
        {
            sf::Vertex* quad = &m_grid[(i + j * (size.x / 32.f)) * 4];
            quad[0].position = sf::Vector2f(i*32, j*32);
            quad[1].position = sf::Vector2f(i*32 + 32, j*32);
            quad[2].position = sf::Vector2f(i*32 + 32, j*32 + 32);
            quad[3].position = sf::Vector2f(i*32, j*32 + 32);

            quad[0].texCoords = sf::Vector2f(0, 0);
            quad[1].texCoords = sf::Vector2f(32, 0);
            quad[2].texCoords = sf::Vector2f(32, 32);
            quad[3].texCoords = sf::Vector2f(0, 32);

            quad[0].color = sf::Color(255, 0, 0);
            quad[1].color = sf::Color(0, 255, 0);
            quad[2].color = sf::Color(0, 0, 255);
            quad[3].color = sf::Color(255, 255, 0);
        }
    }
}
