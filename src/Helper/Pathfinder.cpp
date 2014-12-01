#include "Helper/Pathfinder.hpp"

#include <iostream>
#include <limits>

Pathfinder::Pathfinder(SolarSystemMap* map)
    : m_movementCost(10000)
    , m_sourceNodePosition(invalidCoordinates)
    , m_targetNodePosition(invalidCoordinates)
    , m_pathFound(false)
    , m_map(map)
{
    if (!m_map)
    {
        throw std::runtime_error("[Pathfinder::Pathfinder] SolarSystemMap pointer is null!");
    }
}

bool Pathfinder::handleEvent(const sf::Event& e)
{
    return false;
}

void Pathfinder::update(float dt)
{

}

unsigned Pathfinder::calculateHeuristicCost(coordinates source, coordinates target)
{
    //convert from axial to cube coordinates
    sf::Vector3i sourceCubeCoordinates;
    sf::Vector3i targetCubeCoordinates;

    sourceCubeCoordinates.x = source.x;
    sourceCubeCoordinates.z = source.y;
    sourceCubeCoordinates.y = -1 * (sourceCubeCoordinates.x + sourceCubeCoordinates.z);

    targetCubeCoordinates.x = target.x;
    targetCubeCoordinates.z = target.y;
    targetCubeCoordinates.y = -1 * (targetCubeCoordinates.x + targetCubeCoordinates.z);

    //cube manhattan distance
    int distance =    std::abs(sourceCubeCoordinates.x - targetCubeCoordinates.x) +
                    std::abs(sourceCubeCoordinates.y - targetCubeCoordinates.y) +
                    std::abs(sourceCubeCoordinates.z - targetCubeCoordinates.z);

    //divide by 2 for hex distance
    distance /= 2;
    return distance * m_movementCost;
}

unsigned Pathfinder::calculateMovementCost(coordinates source, coordinates target)
{
    coordinates lastDir;

    auto parent = m_nodes[source].parentCoord;
    if (parent != invalidCoordinates)
    {
        lastDir.x = parent.x - source.x;
        lastDir.y = parent.y - source.y;
    }

    coordinates nextDir(source.x - target.x,
                        source.y - target.y);

    if (lastDir == nextDir)
    {
        return m_movementCost + 1;
    }
    else
    {
        return m_movementCost;
    }
}

void Pathfinder::step(coordinates source, coordinates target)
{
    static bool pathFound = false;
    if (pathFound)
    {
        pathFound = false;
        m_openList.clear();
        m_closedList.clear();
        m_nodes.clear();
        return;
    }
    //std::cout << "[" << source.x << ", " << source.y << "] -> [" << target.x << ", " << target.y << "]\n";

    //Fill out our node list
    for (const auto& hexPair : m_map->getHexMap())
    {
        m_nodes[hexPair.first];
    }

    if (m_openList.size() == 0 && m_closedList.size() == 0)
    {
        std::cout << "Adding the source hex to start us off\n";
        m_openList.push_back(source);
    }

    if (m_closedList.size() != 0 && m_closedList.back() == target)
    {
        std::cout << "No more hexes to explore, we found the target\n";
        for (auto& coord : m_closedList)
        {
            m_nodes[coord].h = 0;
            m_nodes[coord].g = 0;
        }

        for (auto& coord : m_openList)
        {
            m_nodes[coord].h = 0;
            m_nodes[coord].g = 0;
        }

        coordinates parentCoord = m_nodes[m_closedList.back()].parentCoord;
        while (m_map->validCoordinate(parentCoord))
        {
            m_map->getHexMap()[parentCoord].setColor(sf::Color::Yellow);
            parentCoord = m_nodes[parentCoord].parentCoord;
        }
        m_map->getHexMap()[m_closedList.front()].setColor(sf::Color(255, 200, 0, 255));

        pathFound = true;
    }
    else
    {
        unsigned lowestScoreNodeIndex = getLowestScoreNodeIndex(m_openList);
        m_closedList.push_back(m_openList[lowestScoreNodeIndex]);

        m_map->getHexMap()[m_openList[lowestScoreNodeIndex]].setColor(sf::Color::Magenta);
        m_openList.erase(m_openList.begin() + lowestScoreNodeIndex);

        auto adjNodes = getAdjacentNodes(m_closedList.back());
        for (const auto& nodeCoord : adjNodes)
        {
            if (m_map->getHexMap()[nodeCoord].getColor() != sf::Color::Black)
            {
                if (std::find(m_closedList.begin(), m_closedList.end(), nodeCoord) == m_closedList.end())
                {
                    auto& node = m_nodes[nodeCoord];

                    if (std::find(m_openList.begin(), m_openList.end(), nodeCoord) == m_openList.end())
                    {
                        node.parentCoord = m_closedList.back();
                        node.h = calculateHeuristicCost(nodeCoord, target);
                        node.g = calculateMovementCost(node.parentCoord, nodeCoord);
                        m_openList.push_back(nodeCoord);
                        m_map->getHexMap()[nodeCoord].setColor(sf::Color::White);
                    }
                }
            }
        }
    }

    step(source, target);
}

std::vector<coordinates> Pathfinder::getAdjacentNodes(coordinates pos)
{
    std::vector<coordinates> nodes;
    std::vector<coordinates> nodePositions {
        coordinates(pos.x, pos.y - 1), //top-left
        coordinates(pos.x + 1, pos.y - 1), //top-right
        coordinates(pos.x + 1, pos.y), //right
        coordinates(pos.x, pos.y + 1), //bottom-right
        coordinates(pos.x - 1, pos.y + 1), //bottom-left
        coordinates(pos.x - 1, pos.y), //left
    };

    for (coordinates pos : nodePositions)
    {
        if (m_map->validCoordinate(pos))
        {
            nodes.push_back(pos);
        }
    }

    return nodes;
}

unsigned Pathfinder::getLowestScoreNodeIndex(std::vector<coordinates> nodes)
{
    unsigned lowestScore = std::numeric_limits<unsigned>::max();
    unsigned lowestScoreNode = 0;

    for (unsigned i = 0; i < nodes.size(); ++i)
    {
        const auto& node = m_nodes[nodes[i]];

        if (node.h + node.g < lowestScore)
        {
            lowestScore = node.h + node.g;
            lowestScoreNode = i;
        }
    }

    //std::cout << "[" << nodes[lowestScoreNode].x << ", " << nodes[lowestScoreNode].y << "] = " << lowestScore << "\n";
    return lowestScoreNode;
}
