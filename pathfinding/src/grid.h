#pragma once
#include "position.h"

template <typename T>
class Grid
{
protected:
	T ** grid;
	int sizeX, sizeY;

public:
	Grid(int sizeX, int sizeY)
	{
		this->sizeX = sizeX;
		this->sizeY = sizeY;

		grid = new T*[sizeY];
		for (int y = 0; y < sizeY; y++)
			grid[y] = new T[sizeX];
	}

	void set(Position position, T value)
	{
		int x = position.getX();
		int y = position.getY();

		if (x >= 0 && x < sizeX && y >= 0 && y < sizeY)
			grid[y][x] = value;
	}

	const T get(Position pos)
	{
		int x = pos.getX();
		int y = pos.getY();
		if (x >= 0 && x < sizeX && y >= 0 && y < sizeY)
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
