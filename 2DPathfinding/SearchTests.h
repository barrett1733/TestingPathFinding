#pragma once

#include "pathfinding.h"
#include "entity.h"
#include "Movement.h"
#include "timer.h"
#include "PrintData.h"

static int mapSizeX = 10;
static int mapSizeY = 10;

enum SearchFlags
{
	SEARCH_NONE = 0,
	SEARCH_ALL = 1,
	SEARCH_ASTAR = 2,
	SEARCH_ASTARMOD = 4,
	SEARCH_HUMAN = 8,
	SEARCH_ASTAREXP = 16
};

void runAStarTest(Position start, Position goal, ObstructionMap* obsMap, int pf)
{
	cout << endl << "A* Test" << endl;

	Pathfinding test(mapSizeX, mapSizeY);

	Timer timer;
	timer.start();

	Path path = test.findPathAStar(start, goal, obsMap);

	timer.stop();

	print(path, obsMap, timer, pf);
}

void runAStarModifiedTest(Position start, Position goal, ObstructionMap* obsMap, int pf)
{
	cout << endl << "A* Modified Test" << endl;

	Pathfinding test(mapSizeX, mapSizeY);

	Timer timer;
	timer.start();

	Path path = test.findPathAStarModified(start, goal, obsMap);

	timer.stop();

	print(path, obsMap, timer, pf);
}

void runAStarExperTest(Position start, Position goal, ObstructionMap* obsMap, int pf)
{
	cout << endl << "A* Experimental Test" << endl;

	Pathfinding test(mapSizeX, mapSizeY);

	Timer timer;
	timer.start();

	Path path = test.findPathAStarExper(start, goal, obsMap);

	timer.stop();

	print(path, obsMap, timer, pf);
}

void runHumanTest(Position start, Position goal, ObstructionMap* obsMap, int pf)
{
	cout << endl << "Human Test" << endl;

	Human human(start); // human starting at starting position
	Human target(goal); // the target at the target position

	human.setTarget(&target); // set the target for the human

	int forceQuitLimit = mapSizeX * mapSizeY;
	int forceQuitCounter = 0;

	Timer timer;
	timer.start();

	do // do while loop needed to finish the path
	{
		Movement::moveMobileEntity(&human, obsMap);
		forceQuitCounter++;

	} while (human.onPath() && forceQuitCounter < forceQuitLimit);

	timer.stop();
	Path path = human.pathMemories.at(0)->path; // the first path in the path memory

	print(path, obsMap, timer, pf);
}

void runTests(Position start, Position goal, ObstructionMap* obsMap, int printflags, int searchFlag)
{
	if (searchFlag & SEARCH_ASTAR || searchFlag & SEARCH_ALL)
		runAStarTest(start, goal, obsMap, printflags);
	if (searchFlag & SEARCH_ASTARMOD || searchFlag & SEARCH_ALL)
		runAStarModifiedTest(start, goal, obsMap, printflags);
	if (searchFlag & SEARCH_HUMAN || searchFlag & SEARCH_ALL)
		runHumanTest(start, goal, obsMap, printflags);
	if (searchFlag & SEARCH_ASTAREXP || searchFlag & SEARCH_ALL)
		runAStarExperTest(start, goal, obsMap, printflags);

	std::cout << std::endl << "Tests finished" << std::endl;
}
