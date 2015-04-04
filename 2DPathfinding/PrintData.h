#pragma once

#include "Obstruction-Map.h"
#include "pathfinding.h"
#include "timer.h"

enum PrintFlags
{
	PRINT_NONE = 0x0,
	PRINT_ALL = 0x1,
	PRINT_GRID = 0x2,
	PRINT_COORDS = 0x4,
	PRINT_TOTAL_TIME = 0x8,
	PRINT_AVERAGE_TIME = 0x10
};

static void print(Path& path, ObstructionMap *obsMap, Timer& timer, int pf)
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

