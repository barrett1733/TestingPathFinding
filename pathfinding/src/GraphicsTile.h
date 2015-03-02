#pragma once
#include "GraphicsObject.h"
#include "cinder/gl/gl.h"

class GraphicsTile : public GraphicsObject
{
	cinder::Rectf rect;
	cinder::ColorA color;
	int outlineThickness;
	cinder::ColorA outlineColor;

public:
	GraphicsTile(cinder::Rectf, cinder::ColorA, int, cinder::ColorA);
	void setup();
	void update();
	static void draw(cinder::Rectf, cinder::ColorA, int, cinder::ColorA);
};

