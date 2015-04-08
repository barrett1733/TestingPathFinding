#ifndef GRID_H_
#define GRID_H_

#include "position.h"

template <typename T>
class Grid
{
	T ** grid;
	int sizeX, sizeY;

public:
	Grid() : grid(NULL), sizeX(0), sizeY(0)  {}
	Grid(int x, int y) { alloc(x, y); }
	~Grid() { dealloc(); }
	Grid(Grid& grid)
	{
		alloc(grid.getWidth(), grid.getHeight());
		for (int x = 0; x < grid.getWidth(); x++)
			for (int y = 0; y < grid.getHeight(); y++)
				at(x, y) = grid.at(x, y);
	}

	int getWidth() const { return sizeX; }
	int getHeight() const { return sizeY; }

	void alloc(int x, int y)
	{
		if (!grid)
		{
			sizeX = x;
			sizeY = y;
			grid = new T*[sizeY];
			for (int y = 0; y < sizeY; y++)
				grid[y] = new T[sizeX];
		}
	}

	void dealloc()
	{
		if (grid)
		{
			for (int y = 0; y < sizeY; y++)
			{
				delete[] grid[y];
				grid[y] = NULL;
			}
			delete[] grid;
			grid = NULL;
		}
	}

	T& at(Position pos)
	{
		return at(pos.getX(), pos.getY());
	}

	T& at(int x, int y)
	{
		if (x >= 0 && x < sizeX && y >= 0 && y < sizeY)
			return grid[y][x];
		else
			throw std::out_of_range("Grid<>::at() : Out of Range");
	}

	const T& at(Position pos) const
	{
		return at(pos.getX(), pos.getY())
	}

	const T& at(int x, int y) const
	{
		if (x >= 0 && x < sizeX && y >= 0 && y < sizeY)
			return grid[y][x];
		else
			throw std::out_of_range("Grid<>::at() : Out of Range");
	}

	// TODO
	void resize(int x, int y)
	{
		/*
		if (graph == NULL)
		alloc(x, y);
		else if (x != sizeX && y != sizeY)
		{

		}
		*/
	}

};
#endif