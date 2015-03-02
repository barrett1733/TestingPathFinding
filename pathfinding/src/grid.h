#pragma once
#include "position.h"
#include "IGrid.h"

template <typename T>
class Grid : public IGrid
{
protected:
	T ** grid;

public:
	Grid(int size_x, int size_y) : size_x(size_x), size_y(size_y)
	{
		grid = new T*[size_y];
		for (int y = 0; y < size_y; y++)
			grid[y] = new T[size_x];
	}

	void set(Position position, T value)
	{
		int x = position.getX();
		int y = position.getY();

		if (x >= 0 && x < size_x && y >= 0 && y < size_y)
			grid[y][x] = value;
	}

	const T get(Position pos)
	{
		int x = pos.getX();
		int y = pos.getY();
		if (x >= 0 && x < size_x && y >= 0 && y < size_y)
			return grid[pos.getY()][pos.getX()];
	}

	friend std::ostream& operator<<(std::ostream & os, const Grid & map)
	{
		for(int y = 0; y < map.size; y ++)
		{
			for(int x = 0; x < map.size; x ++)
				os << map.grid[y][x];
			os << std::endl;
		}
		return os;
	}
};
