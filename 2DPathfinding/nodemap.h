#ifndef NODEMAP_H_
#define NODEMAP_H_

#include "grid.h"
#include "node.h"

class NodeMap
{
	int x_size, y_size;
	Grid<Node> graph;
	Grid<bool> existsGraph;
public:
	NodeMap(int x_size, int y_size);
	~NodeMap();
	void clear();
	bool exists(Position);
	void set(Position, Node*, double g, double h);
	Node get(Position);
	Node get(Node*);
};


#endif