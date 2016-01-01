#include "wgindicator.h"

uint16_t wgIndicator::getPixel(int xcoord, int ycoord)
{
	uint16_t xc = xcoord - _x;
	uint16_t yc = ycoord - _y;
	if(xc == 0 || yc == 0 || xc == _width || yc == _height)
		return ~_color;
	else
		return _color;
}
