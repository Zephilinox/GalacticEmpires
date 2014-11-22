#include "Helper/Pathfinder.hpp"

#include <iostream>
#include <limits>

Pathfinder::Pathfinder(SolarSystemMap* map)
	: m_movementCost(10)
	, m_sourceNodePosition(invalidCoordinates)
	, m_targetNodePosition(invalidCoordinates)
	, m_pathFound(false)
	, m_map(map)
{
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
	int distance =	std::abs(sourceCubeCoordinates.x - targetCubeCoordinates.x) +
					std::abs(sourceCubeCoordinates.y - targetCubeCoordinates.y) +
					std::abs(sourceCubeCoordinates.z - targetCubeCoordinates.z);

	//divide by 2 for hex distance
	distance /= 2;

	return distance * m_movementCost;
}

unsigned Pathfinder::calculateMovementCost(coordinates source, coordinates target)
{
	return m_movementCost;
}

void Pathfinder::step(coordinates source, coordinates target)
{
	auto nodes = getAdjacentNodes(source);
	auto index = getLowestScoreNodeIndex(nodes, target);
	m_map->getHexMap()[nodes[index]].setColor(sf::Color::Black);

	while (nodes[index] != target)
	{
		nodes = getAdjacentNodes(nodes[index]);
		index = getLowestScoreNodeIndex(nodes, target);
		m_map->getHexMap()[nodes[index]].setColor(sf::Color::Black);
	}
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

unsigned Pathfinder::getLowestScoreNodeIndex(std::vector<coordinates> nodes, coordinates target)
{
	unsigned lowestScore = std::numeric_limits<unsigned>::max();
	unsigned lowestScoreNode = 0;

	for (unsigned i = 0; i < nodes.size(); ++i)
	{
		if (calculateHeuristicCost(nodes[i], target) < lowestScore) //heuristic + move cost < lowest score
		{
			//set lowest score to heuristic + move cost
			lowestScore = calculateHeuristicCost(nodes[i], target);
			lowestScoreNode = i;
		}
	}

	return lowestScoreNode;
}
