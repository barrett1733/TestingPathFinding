#include "nodemap.h"

NodeMap::NodeMap(int x_size, int y_size) : 
	x_size(x_size), 
	y_size(y_size)
{
	graph.alloc(x_size, y_size);
	existsGraph.alloc(x_size, y_size);
}

NodeMap::~NodeMap() { }

void NodeMap::clear()
{
	for (int x = 0; x < x_size; x++)
	for (int y = 0; y < y_size; y++)
	{
		existsGraph.at(Position(x, y)) = false;
	}
}

bool NodeMap::exists(Position pos)
{
	return existsGraph.at(pos);
}

void NodeMap::set(Position pos, Node* par, double g, double h)
{
	int x = pos.getX();
	int y = pos.getY();
	if (!existsGraph.at(pos))
	{
		existsGraph.at(pos) = true;
		graph.at(pos) = Node(pos, par, g, h);
	}
}

Node NodeMap::get(Position pos)
{
	return graph.at(pos);
}

Node NodeMap::get(Node* node)
{
	return graph.at(node->pos);
}
