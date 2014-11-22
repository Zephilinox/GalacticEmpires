#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include <memory>

#include <SFML/Graphics.hpp>

#include "Game/SolarSystemMap.hpp"

class Pathfinder
{
public:
    Pathfinder(SolarSystemMap* map);
    bool handleEvent(const sf::Event& e);
    void update(float dt);

    unsigned calculateHeuristicCost(coordinates source, coordinates target);
    unsigned calculateMovementCost(coordinates source, coordinates target);

    void step(coordinates source, coordinates target);

private:
    std::vector<coordinates> getAdjacentNodes(coordinates pos);
    unsigned getLowestScoreNodeIndex(std::vector<coordinates> nodes, coordinates target);

    const unsigned m_movementCost;

    coordinates m_sourceNodePosition;
    coordinates m_targetNodePosition;

    std::vector<coordinates> m_openList;
    std::vector<coordinates> m_closedList;

    bool m_pathFound;

	SolarSystemMap* m_map;
};

#endif //PATHFINDER_HPP
