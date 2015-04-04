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

	indexGraph.set(start, NULL, 0, heursticCost(neighborPos, goal));

	//searchList.push(&indexGraph[start]);
	searchQueue.push(indexGraph[start]);

	closestToGoalNode = &indexGraph[start];
	curNode = NULL;

	while (!goalReached && (!searchLimiter || searchCounter <= searchMax))
	{
		searchCounter++;

		//if (searchList.empty())
		if (searchQueue.empty())
			return constructPath(closestToGoalNode);

		//curNode = searchList.pop();
		curNode = &searchQueue.top();
		searchQueue.pop();

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
					if (indexGraph.exists(neighborPos))
					{
						if (curNode->gcost < indexGraph[neighborPos].gcost)
						{
							indexGraph[neighborPos].gcost = curNode->gcost;
							indexGraph[neighborPos].fcost = indexGraph[neighborPos].gcost + heursticCost(neighborPos, goal);
							indexGraph[neighborPos].parentNode = curNode;
						}
					}
					else
					{
						indexGraph.set(
							neighborPos,
							curNode,
							curNode->gcost + pathCost(curNode->pos, neighborPos),
							curNode->gcost + pathCost(curNode->pos, neighborPos) + heursticCost(neighborPos, goal)
							);
						//searchList.push(&indexGraph[neighborPos]);
						searchQueue.push(indexGraph[neighborPos]);
					}
				}
			}
		}
	}
	std::cout << "finished one" << std::endl;
	return constructPath(curNode);
}

Path Pathfinding::findPathAStarModified(Position start, Position goal, ObstructionMap* obstructionMap)
{
	goalReached = false;
	searchCounter = 0;

	indexGraph.set(start, NULL, 0, heursticCost(neighborPos, goal));

	searchList.push(&indexGraph[start]);

	closestToGoalNode = &indexGraph[start];
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
					if (indexGraph.exists(neighborPos))
					{
						if (curNode->gcost < indexGraph[neighborPos].gcost)
						{
							indexGraph[neighborPos].gcost = curNode->gcost;
							indexGraph[neighborPos].fcost = indexGraph[neighborPos].gcost + heursticCost(neighborPos, goal);
							indexGraph[neighborPos].parentNode = curNode;
						}
					}
					else
					{
						indexGraph.set(
							neighborPos,
							curNode,
							curNode->gcost + pathCost(curNode->pos, neighborPos),
							curNode->gcost + pathCost(curNode->pos, neighborPos) + heursticCost(neighborPos, goal)
							);
						searchList.push(&indexGraph[neighborPos]);
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

	indexGraph.set(start, NULL, 0, heursticCost(neighborPos, goal));

	openList.push(&indexGraph[start]);

	closestToGoalNode = &indexGraph[start];
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
					indexGraph[neighborPos].gcost = tempGCost;
					indexGraph[neighborPos].fcost = indexGraph[neighborPos].gcost + heursticCost(neighborPos, goal);
					indexGraph[neighborPos].parentNode = curNode;
					if (!openList.exists(neighborPos))
					{
						indexGraph.set(
							neighborPos,
							curNode,
							curNode->gcost + pathCost(curNode->pos, neighborPos),
							curNode->gcost + pathCost(curNode->pos, neighborPos) + heursticCost(neighborPos, goal)
							);
						openList.push(&indexGraph[neighborPos]);
					}
				}
			}
		}
	}
	return constructPath(&Node());
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

	for (int i = 0; i < searchQueue.size(); i++)
		searchQueue.pop();
	searchList.clear();
	indexGraph.clear();
	return path;
}

Position Pathfinding::findNextPositionAStarModified(Position start, Position goal, ObstructionMap* obstructionMap)
{
	return findPathAStarModified(start, goal, obstructionMap)[0];
}

Position Pathfinding::findNextPositionAStar(Position start, Position goal, ObstructionMap* obstructionMap)
{
	return findPathAStar(start, goal, obstructionMap)[0];
}

void Pathfinding::printPathAsGrid(Path& poslist, ObstructionMap* obsMap)
{
	int size_x = obsMap->size_x;
	int size_y = obsMap->size_y;

	ObstructionMap grid(size_x, size_y);

	for (int i = 0; i < poslist.size(); i++)
	{
		grid.set(poslist[i], OT_CONSIDERED);
	}
	for (int i = 0; i < size_x; i++)
		for (int j = 0; j < size_y; j++)
			if (obsMap->isObstructed(Position(i, j)))
				grid.set(Position(i, j), OT_OBSTRUCTED);

	std::cout << grid << std::endl;
}

void Pathfinding::printPathAsCoordinates(Path& poslist)
{
	for (int i = 0; i < poslist.size(); i++)
	{
		std::cout << poslist[i] << ", ";
	}
	std::cout << std::endl;
}
