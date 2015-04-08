#include "SearchGrid.h"

SearchGrid::SearchGrid(int x_size, int y_size) :
	x_size(x_size),
	y_size(y_size),
	current(NULL),
	start(NULL)
{
	graph.alloc(x_size, y_size);
	existsGraph.alloc(x_size, y_size);
	clear();
}

SearchGrid::~SearchGrid() { }

void SearchGrid::clear()
{
	for (int x = 0; x < x_size; x++)
		for (int y = 0; y < y_size; y++)
		{
		existsGraph.at(x, y) = false;
		}
}

bool SearchGrid::checkExist(Position pos)
{
	return existsGraph.at(pos);
}

void SearchGrid::markExist(Position pos)
{
	existsGraph.at(pos) = true;
}

Node& SearchGrid::at(Position pos)
{
	return graph.at(pos);
}

Node& SearchGrid::at(Node* node)
{
	return graph.at(node->pos);
}
