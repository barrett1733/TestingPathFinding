#ifndef PATHFINDING_H_
#define PATHFINDING_H_

#include <iostream>
#include <math.h>
#include <vector>
#include <map>
#include <queue>
#include "obstruction-map.h"
#include "nodelist.h"
#include "nodemap.h"
#include "distance.h"

typedef std::vector<Position> Path;
typedef std::vector<Node> NodeVector;
typedef std::priority_queue<Node, NodeVector, NodeCompare> NodeQueue;

class Pathfinding
{
	typedef Node* NodeRef;
	int size_x, size_y;

	NodeMap indexGraph;
	bool goalReached;
	NodeRef curNode;
	Position neighborPos;

	// A* Modified variables
	bool searchLimiter;
	NodeList searchList;
	NodeQueue searchQueue;
	int searchMax, searchCounter;
	NodeRef closestToGoalNode;

	// A* variables
	NodeList openList, closedList;

	double pathCost(Position a, Position b);
	double heursticCost(Position a, Position b);
	Path constructPath(Node*);

public:
	Pathfinding(int x, int y) :
		size_x(x), size_y(y),
		searchLimiter(false),
		indexGraph(x, y),
		searchMax((x * y) / 8)
	{};
	Pathfinding(int x, int y, bool limitSearch, int numOfNodesToSearch) :
		size_x(x), size_y(y),
		searchLimiter(limitSearch),
		indexGraph(x, y),
		searchMax(numOfNodesToSearch)
	{};
	Path findPathAStarExper(Position start, Position goal, ObstructionMap* obstructionMap);
	Path findPathAStarModified(Position start, Position goal, ObstructionMap* obstructionMap);
	Path findPathAStar(Position start, Position goal, ObstructionMap* obstructionMap);
	Position findNextPositionAStarExper(Position start, Position goal, ObstructionMap* obstructionMap);
	Position findNextPositionAStarModified(Position start, Position goal, ObstructionMap* obstructionMap);
	Position findNextPositionAStar(Position start, Position goal, ObstructionMap* obstructionMap);
	static void printPathAsCoordinates(Path& poslist);
	static void printPathAsGrid(Path& poslist);
	static void printPathAsGrid(Path& poslist, ObstructionMap* obsMap);
};


#endif
