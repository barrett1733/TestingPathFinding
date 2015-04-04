#include "GraphicsGrid.h"
#include "GraphicsTile.h"
#include "GridColors.h"

void GraphicsGrid::draw(ObstructionMap& grid, cinder::Rectf rect, cinder::ColorA color)
{
	int tileWidth = rect.getWidth() / grid.size_x;
	int tileHeight = rect.getHeight() / grid.size_y;
	
	for (int i = rect.x1; i < rect.x2; i += tileWidth)
		for (int j = rect.y1; j < rect.y2; j += tileHeight)
		{
			cinder::Rectf tile(i, j, i + tileWidth - 1, j + tileHeight - 1);
			cinder::ColorA gridSpaceColor = GridColors::getColorFromGridSpace(grid.get(Position(i,j)));
			GraphicsTile::draw(tile, gridSpaceColor, 1, cinder::ColorA(0, 0, 0));
		}
}

void GraphicsGrid::drawGrid()
{

}