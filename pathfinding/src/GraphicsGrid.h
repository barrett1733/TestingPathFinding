#pragma once
#include "GraphicsObject.h"
#include "ObstructionMap.h"

class GraphicsGrid : public GraphicsObject
{
public:
	static void drawGrid();
	static void draw(ObstructionMap&, cinder::Rectf, cinder::ColorA);
};