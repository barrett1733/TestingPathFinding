#include "nodemap.h"

NodeMap::NodeMap(int x_size, int y_size) : 
	x_size(x_size), 
	y_size(y_size)
{
	graph.alloc(x_size, y_size);
	existsGraph.alloc(x_size, y_size);
	clear();
}

NodeMap::~NodeMap() { }

void NodeMap::clear()
{
	for (int x = 0; x < x_size; x++)
	for (int y = 0; y < y_size; y++)
	{
		existsGraph.at(x, y) = false;
	}
}

bool NodeMap::checkExist(Position pos)
{
	return existsGraph.at(pos);
}

void NodeMap::markExist(Position pos)
{
	existsGraph.at(pos) = true;
}

Node& NodeMap::at(Position pos)
{
	return graph.at(pos);
}

Node& NodeMap::at(Node* node)
{
	return graph.at(node->pos);
}
