#pragma once
#include "node.h"
#include "grid.h"

class SearchGrid
{
	int x_size, y_size;
	Grid<Node> graph;
	Grid<bool> existsGraph;
	Node* start;
	Node* current;
public:
	SearchGrid(int x_size, int y_size);
	~SearchGrid();
	void clear();
	bool checkExist(Position);
	void markExist(Position);
	Node& at(Position);
	Node& at(Node*);
};

