#ifndef OBSTRUCTION_MAP_H_
#define OBSTRUCTION_MAP_H_

#include "position.h"
#include "grid.h"

enum ObstructionType
{
	OT_EMPTY,
	OT_OBSTRUCTED,
	OT_CONSIDERED
};

class ObstructionMap : public Grid<ObstructionType>
{
public:
	ObstructionMap(int size_x, int size_y);

	bool isObstructed(Position);
	bool isConsidered(Position);
	bool isOpen(Position);

	friend std::ostream& operator<<(std::ostream & os, const ObstructionMap & map)
	{
		for (int y = 0; y < map.size_y; y++)
		{
			for (int x = 0; x < map.size_x; x++)
			{
				if (map.grid[y][x] == OT_EMPTY)
					os << ".";
				else if (map.grid[y][x] == OT_OBSTRUCTED)
					os << "X";
				else if (map.grid[y][x] == OT_CONSIDERED)
					os << "o";
			}
			os << std::endl;
		}
		return os;
	}
};

#endif
