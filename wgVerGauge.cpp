#include "wgVerGauge.h"
#include "AsciiLib.h"
void wgVerGauge::setValue(int val)
{
	value = val;
	uint8_t third = val /100;
	uint8_t second = (val /10) % 10;
	uint8_t first = val % 10;
	GetASCIICode(buffer,third+'0');
	GetASCIICode(buffer+16,second+'0');
	GetASCIICode(buffer+32,first+'0');
}
uint16_t wgVerGauge::getPixel(int xcoord, int ycoord)
{
	int xc = xcoord - x;
	int yc = ycoord - y;
	if(value < 0 || value > 255)
		return 0;
	int yval = (255-value)*height/255;
	uint16_t pix = 0;
	if((yc>=height/2 && yc < (height/2 + 15)) && (xc >= (width - 24)/2) && (xc < ((width - 24)/2)+24))
	{
		int xl = xc - (width - 24)/2;
		int yl = yc - height/2;
		if(buffer[yl+16*(xl/8)]>>(7-(xl%8)) & 0x01)
			pix = 0xFFFF;
	}
	if(((yval > yc)&& yc !=0 && yc != height && xc !=0 && xc != width) || yc == 1 || yc == height - 1 || xc == 1 || xc == width - 1)
		return 0xFFFF ^ pix;
	else
		return 0 ^ pix;
}

uint8_t wgVerGauge::getValueWhenClicked(uint16_t ax, uint16_t ay)
{
	int xc = ax - x;
	int yc = ay - y;

	return 255-yc*255/(height);
}
