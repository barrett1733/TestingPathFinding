#include "ObstructionMap.h"

ObstructionMap::ObstructionMap(int size_x, int size_y) :
	Grid<ObstructionType>(size_x, size_y)
{
	grid = new ObstructionType*[size_y];
	for (int y = 0; y < size_y; y++)
	{
		grid[y] = new ObstructionType[size_x];
		for (int x = 0; x < size_x; x++)
			grid[y][x] = OT_EMPTY;
	}
}

bool ObstructionMap::isObstructed(Position position)
{
	return get(position) == OT_OBSTRUCTED;
}

bool ObstructionMap::isConsidered(Position position)
{
	return get(position) == OT_CONSIDERED;
}

bool ObstructionMap::isOpen(Position position)
{
	return get(position) == OT_EMPTY;
}
