#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

class GraphicsObject
{
public:
	//virtual void setup() = 0;
	//virtual void update() = 0;
	virtual void draw() = 0;
};

