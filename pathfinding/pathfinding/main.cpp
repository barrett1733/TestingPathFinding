#include "pathfinding.h"
#include "entity.h"
#include "Movement.h"
#include "timer.h"

//
// Notes:
// C++11 required for compile
// Human pathfinding may not work right under certain 
// circumstances do to removed functions from the
// original code.
// Human pathfinding will force quit after mapSizeX * mapSizeY amount of steps.
// Do not use excessively large sizes (>2000). Will cause crash.
//

using namespace std;

static int mapSizeX = 10;
static int mapSizeY = 10;

enum PrintFlags
{
	PRINT_NONE = 0x0,
	PRINT_ALL = 0x1,
	PRINT_GRID = 0x2,
	PRINT_COORDS = 0x4,
	PRINT_TOTAL_TIME = 0x8,
	PRINT_AVERAGE_TIME = 0x10
};

void print(Path& path, ObstructionMap *obsMap, Timer& timer, int pf)
{
	if (pf & PRINT_COORDS || pf & PRINT_ALL)
		Pathfinding::printPathAsCoordinates(path);
	if (pf & PRINT_GRID || pf & PRINT_ALL)
		Pathfinding::printPathAsGrid(path, obsMap);
	if (pf & PRINT_TOTAL_TIME || pf & PRINT_ALL)
		timer.printTotal();
	if (pf & PRINT_AVERAGE_TIME || pf & PRINT_ALL)
		timer.printAverage();
}

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

void runTests(Position start, Position goal, ObstructionMap* obsMap, int printflags)
{
	runAStarTest(start, goal, obsMap, printflags);
	runAStarModifiedTest(start, goal, obsMap, printflags);
	runHumanTest(start, goal, obsMap, printflags);
}

int main()
{
	std::cout << "Press enter to start" << std::endl;
	std::cin.ignore();
	
	mapSizeX = 10; // map size x
	mapSizeY = 10; // map size y

	// Position needs to know the max size of the world
	Position::max_x = mapSizeX;
	Position::max_y = mapSizeY;
	//

	/////////////////// Small Test
	
	Position start(0, 0);
	Position goal(5, 0);

	ObstructionMap testmap1(mapSizeX, mapSizeY);
	for (int i = 0; i < 8; i++)
	{
		testmap1.set(Position(3, i), OT_OBSTRUCTED);
	}

	runTests(start, goal, &testmap1, PRINT_GRID|PRINT_TOTAL_TIME);

	////////////////// Large Test

	mapSizeX = 100; // map size x
	mapSizeY = 100; // map size y

	// Position needs to know the max size of the world
	Position::max_x = mapSizeX;
	Position::max_y = mapSizeY;
	//

	start = Position(0, 5);
	goal = Position(50, 5);

	ObstructionMap testmap2(mapSizeX, mapSizeY);
	for (int i = 1; i < 9; i++)
	{
		testmap2.set(Position(3, i), OT_OBSTRUCTED);
	}
	testmap2.set(Position(1, 1), OT_OBSTRUCTED);
	testmap2.set(Position(1, 8), OT_OBSTRUCTED);
	testmap2.set(Position(2, 1), OT_OBSTRUCTED);
	testmap2.set(Position(2, 8), OT_OBSTRUCTED);


	runTests(start, goal, &testmap2, PRINT_TOTAL_TIME);

	/////////////////

	std::cin.ignore();
}
