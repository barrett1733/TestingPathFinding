#include "pathfinding.h"
#include "entity.h"
#include "Movement.h"
#include "timer.h"
#include "SearchTests.h"

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

void testingPathfinding()
{
	std::cout << "Press enter to start" << std::endl;
	std::cin.ignore();

	/////////////////// Small Test

	Position::max_x = 10;
	Position::max_y = 10;

	Position start(0, 0);
	Position goal(9, 0);

	ObstructionMap testmap1(mapSizeX, mapSizeY);
	for (int i = 0; i < 8; i++)
	{
		testmap1.at(Position(5, i)) = OT_OBSTRUCTED;
	}

	runTests(start, goal, &testmap1, PRINT_GRID | PRINT_TOTAL_TIME, SEARCH_ASTAR | SEARCH_ASTARMOD | SEARCH_ASTAREXP);

	
	////////////////// Large Test

	mapSizeX = 2500; // map size x
	mapSizeY = 2500; // map size y

	// Position needs to know the max size of the world
	Position::max_x = mapSizeX;
	Position::max_y = mapSizeY;
	//


	start = Position(0, 5);
	goal = Position(50, 5);

	ObstructionMap testmap2(mapSizeX, mapSizeY);
	for (int i = 1; i < 9; i++)
	{
		testmap2.at(Position(3, i)) = OT_OBSTRUCTED;
	}
	testmap2.at(Position(1, 1)) = OT_OBSTRUCTED;
	testmap2.at(Position(1, 8)) = OT_OBSTRUCTED;
	testmap2.at(Position(2, 1)) = OT_OBSTRUCTED;
	testmap2.at(Position(2, 8)) = OT_OBSTRUCTED;


	runTests(start, goal, &testmap2, PRINT_TOTAL_TIME, SEARCH_ASTAREXP | SEARCH_ASTARMOD | SEARCH_ASTAR);

	/////////////////
	
	std::cin.ignore();

}

int main()
{
	testingPathfinding();
}
