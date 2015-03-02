#include "GraphicsTile.h"


GraphicsTile::GraphicsTile(cinder::Rectf rect, cinder::ColorA color, int outlineThickness, cinder::ColorA outlineColor) :
	rect(rect), 
	color(color), 
	outlineThickness(outlineThickness), 
	outlineColor(outlineColor)
{
}

void GraphicsTile::setup()
{
}

void GraphicsTile::update()
{
}

void GraphicsTile::draw(cinder::Rectf rect, cinder::ColorA color, int outlineThickness, cinder::ColorA outlineColor)
{
	float x1 = rect.x1;
	float x2 = rect.x2;
	float y1 = rect.y1;
	float y2 = rect.y2;

	cinder::gl::color(color);
	cinder::gl::drawSolidRect(rect);
	cinder::gl::color(outlineColor);

	cinder::gl::drawSolidRect(cinder::Rectf(x1, y1, x2, y1 + outlineThickness)); // top
	cinder::gl::drawSolidRect(cinder::Rectf(x1, y2, x2, y2 - outlineThickness)); // bottom
	cinder::gl::drawSolidRect(cinder::Rectf(x1, y1, x1 + outlineThickness, y2)); // left
	cinder::gl::drawSolidRect(cinder::Rectf(x2, y1, x2 - outlineThickness, y2)); // right
}
