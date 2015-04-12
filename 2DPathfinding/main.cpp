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
	mapSizeX = 10;
	mapSizeY = 10;

	Position::max_x = mapSizeX;
	Position::max_y = mapSizeY;

	Position start(0, 0);
	Position goal(9, 0);

	ObstructionMap testmap1(mapSizeX, mapSizeY);
	for (int i = 0; i < mapSizeY - 1; i++)
	{
		testmap1.at(Position(5, i)) = OT_OBSTRUCTED;
	}

	runTests(start, goal, &testmap1, PRINT_GRID | PRINT_TOTAL_TIME, SEARCH_ASTAR | SEARCH_ASTARMOD);

	/////////////////// Small Test
	mapSizeX = 10;
	mapSizeY = 10;

	Position::max_x = mapSizeX;
	Position::max_y = mapSizeY;

	start = Position(0, 4);
	goal = Position(9, 4);

	ObstructionMap testmap3(mapSizeX, mapSizeY);
	std::vector<std::pair<int, int>> obs = {
			{ 2, 2 }, { 2, 3 }, { 2, 5 }, { 2, 6 }, 
			{ 3, 1 }, { 3, 2 }, { 3, 6 }, { 3, 7 }, 
			{ 4, 1 }, { 4, 7 }, 
			{ 5, 1 }, { 5, 2 }, { 5, 6 }, { 5, 7 }, 
			{ 6, 2 }, { 6, 3 }, { 6, 4 }, { 6, 5 }, { 6, 6 }
	};
	for (int i = 0; i < obs.size(); i++)
		testmap3.at(Position(obs[i].first, obs[i].second)) = OT_OBSTRUCTED;

	runTests(start, goal, &testmap3, PRINT_GRID | PRINT_TOTAL_TIME, SEARCH_ASTAR | SEARCH_ASTARMOD);

	////////////////// Large Test

	mapSizeX = 2500; // map size x
	mapSizeY = 2500; // map size y

	Position::max_x = mapSizeX;
	Position::max_y = mapSizeY;

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


	runTests(start, goal, &testmap2, PRINT_TOTAL_TIME, SEARCH_ASTAREXP | SEARCH_ASTARMOD);

	/////////////////
	
	std::cin.ignore();

}

int main()
{
	testingPathfinding();
}
