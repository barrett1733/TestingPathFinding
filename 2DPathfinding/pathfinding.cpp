#include "pathfinding.h"

double Pathfinding::heursticCost(Position a, Position b)
{
	return ManhattanDistance(a, b);
}

double Pathfinding::pathCost(Position a, Position b)
{
	return EuclideanDistance(a, b);
}

Path Pathfinding::findPathAStarExper(Position start, Position goal, ObstructionMap* obstructionMap)
{
	goalReached = false;
	searchCounter = 0;

	indexGrid.add(Node(start, NULL, 0, heursticCost(neighborPos, goal)));

	searchList.push(&indexGrid.get(start));

	closestToGoalNode = &indexGrid.get(start);
	curNode = NULL;

	while (!goalReached && (!searchLimiter || searchCounter <= searchMax))
	{
		searchCounter++;

		if (searchList.empty())
			return constructPath(closestToGoalNode);

		curNode = searchList.pop();

		// this is questionable
		if (curNode->fcost < closestToGoalNode->fcost)
			closestToGoalNode = curNode;

		if (curNode->pos == goal)
		{
			goalReached = true;
		}
		else
		{
			for (Direction dir = D_NORTH; dir < D_COUNT; dir++)
			{
				neighborPos = curNode->pos;
				neighborPos.moveUnchecked(dir);
				if (neighborPos.checkSanity() && obstructionMap->isOpen(neighborPos))
				{
					if (indexGrid.checkExists(neighborPos))
					{
						if (curNode->gcost < indexGrid.get(neighborPos).gcost)
						{
							indexGrid.add(Node(neighborPos, curNode, curNode->gcost, heursticCost(neighborPos, goal)));
						}
					}
					else
					{
						double travelCost = pathCost(curNode->pos, neighborPos);
						double newgcost = curNode->gcost + travelCost;
						double hcost = heursticCost(neighborPos, goal);

						indexGrid.add(Node(neighborPos, curNode, newgcost, newgcost + hcost));
						searchList.push(&indexGrid.get(neighborPos));
					}
				}
			}
		}
	}
	return constructPath(curNode);
}

Path Pathfinding::findPathAStarModified(Position start, Position goal, ObstructionMap* obstructionMap)
{
	goalReached = false;
	searchCounter = 0;

	indexGraph.at(start) = Node(start, NULL, 0, heursticCost(neighborPos, goal));
	indexGraph.markExist(start);

	searchList.push(&indexGraph.at(start));

	closestToGoalNode = &indexGraph.at(start);
	curNode = NULL;

	while (!goalReached && (!searchLimiter || searchCounter <= searchMax))
	{
		searchCounter++;

		if (searchList.empty())
			return constructPath(closestToGoalNode);

		curNode = searchList.pop();

		// this is questionable
		if (curNode->fcost < closestToGoalNode->fcost)
			closestToGoalNode = curNode;

		if (curNode->pos == goal)
		{
			goalReached = true;
		}
		else
		{
			for (Direction dir = D_NORTH; dir < D_COUNT; dir++)
			{
				neighborPos = curNode->pos;
				neighborPos.moveUnchecked(dir);
				if (neighborPos.checkSanity() && obstructionMap->isOpen(neighborPos))
				{
					if (indexGraph.checkExist(neighborPos))
					{
						if (curNode->gcost < indexGraph.at(neighborPos).gcost)
						{
							indexGraph.at(neighborPos) = Node(neighborPos, curNode, curNode->gcost, heursticCost(neighborPos, goal));
							indexGraph.markExist(neighborPos);
						}
					}
					else
					{
						double travelCost = pathCost(curNode->pos, neighborPos);
						double newgcost = curNode->gcost + travelCost;
						double hcost = heursticCost(neighborPos, goal);

						indexGraph.at(neighborPos) = Node(neighborPos, curNode, newgcost, newgcost + hcost);
						indexGraph.markExist(neighborPos);
						searchList.push(&indexGraph.at(neighborPos));
							indexGraph.markExist(neighborPos);
					}
				}
			}
		}
	}
	return constructPath(curNode);
}

Path Pathfinding::findPathAStar(Position start, Position goal, ObstructionMap* obstructionMap)
{
	goalReached = false;

	indexGraph.at(start) = Node(start, NULL, 0, heursticCost(neighborPos, goal));
	indexGraph.markExist(start);

	openList.push(&indexGraph.at(start));

	closestToGoalNode = &indexGraph.at(start);
	curNode = NULL;

	while (!openList.empty())
	{
		curNode = openList.pop();

		if (curNode->pos == goal)
			return constructPath(curNode);
		closedList.push(curNode);
		for (int dir = D_NORTH; dir < D_COUNT; dir++)
		{
			neighborPos = curNode->pos.getNeighbor(dir);

			if (closedList.exists(neighborPos))
				continue;
			double tempGCost = curNode->gcost + EuclideanDistance(curNode->pos, neighborPos);

			if (neighborPos.checkSanity() && obstructionMap->isOpen(neighborPos))
			{
				if (!openList.exists(neighborPos) || tempGCost < pathCost(neighborPos, goal))
				{
					indexGraph.at(neighborPos) = Node(neighborPos, curNode, tempGCost, heursticCost(neighborPos, goal));
					indexGraph.markExist(neighborPos);

					if (!openList.exists(neighborPos))
					{
						double travelCost = pathCost(curNode->pos, neighborPos);
						double newgcost = curNode->gcost + travelCost;
						double hcost = heursticCost(neighborPos, goal);

						indexGraph.at(neighborPos) = Node(neighborPos, curNode, newgcost, newgcost + hcost);
						indexGraph.markExist(neighborPos);
						openList.push(&indexGraph.at(neighborPos));
					}
				}
			}
		}
	}
	return constructPath(curNode);
}

// Does not include original position
Path Pathfinding::constructPath(Node* goal)
{
	Node* node = goal;
	Path path;
	path.reserve(Position::max_x * Position::max_y);

	if (node->parentNode == NULL)
	{
		path.push_back(node->pos);
		return path;
	}

	while (node->parentNode != NULL)
	{
		path.push_back(node->pos);
		node = node->parentNode;
	}
	std::reverse(path.begin(), path.end());

	clear();
	return path;
}

void Pathfinding::clear()
{
	searchList.clear();
	indexGraph.clear();
	indexGrid.clear();
}

Position Pathfinding::findNextPositionAStarModified(Position start, Position goal, ObstructionMap* obstructionMap)
{
	return findPathAStarModified(start, goal, obstructionMap)[0];
}

Position Pathfinding::findNextPositionAStar(Position start, Position goal, ObstructionMap* obstructionMap)
{
	return findPathAStar(start, goal, obstructionMap)[0];
}

