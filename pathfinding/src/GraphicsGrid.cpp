#include "GraphicsGrid.h"
#include "GraphicsTile.h"

void GraphicsGrid::draw(IGrid* grid, cinder::Rectf rect, cinder::ColorA color)
{
	int tileWidth = rect.getWidth() / grid->size_x;
	int tileHeight = rect.getHeight() / grid->size_y;
	
	for (int i = rect.x1; i < rect.x2; i += tileWidth)
		for (int j = rect.y1; j < rect.y2; j += tileHeight)
		{
			cinder::Rectf tile(i, j, i + tileWidth - 1, j + tileHeight - 1);
			GraphicsTile::draw(tile, color, 1, cinder::ColorA(0, 0, 0));
		}
}

void GraphicsGrid::drawGrid()
{

}