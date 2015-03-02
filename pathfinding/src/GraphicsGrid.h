#pragma once
#include "GraphicsObject.h"
#include "IGrid.h"

class GraphicsGrid : public GraphicsObject
{
public:
	static void draw(IGrid*, cinder::Rectf, cinder::ColorA);
};