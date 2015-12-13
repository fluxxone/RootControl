#include "wgVerGauge.h"
#include "AsciiLib.h"
#define CHAR_WIDTH	8
#define CHAR_HEIGHT	16
void wgVerGauge::setValue(Emitter* emitter,uint32_t val)
{
	(void) emitter;
	_value = val;
	numChars = 0;
	uint32_t valScaled = val*_multiplier/_divider;
	uint8_t third = valScaled /100;
	uint8_t second = (valScaled /10) % 10;
	uint8_t first = valScaled % 10;
	uint8_t dec = (val*10*_multiplier/_divider) % 10;
	if(third == 0)
		GetASCIICode(buffer+16*numChars,' ');
	else
	{
		GetASCIICode(buffer+16*numChars,third+'0');
		numChars++;
	}
	if((third == 0) && (second == 0))
		GetASCIICode(buffer+16*numChars,' ');
	else
	{
		GetASCIICode(buffer+16*numChars,second+'0');
		numChars++;
	}
	GetASCIICode(buffer+16*numChars,first+'0');
	numChars++;
	GetASCIICode(buffer+16*numChars,'.');
	numChars++;
	GetASCIICode(buffer+16*numChars,dec+'0');
	numChars++;
	GetASCIICode(buffer+16*numChars,_unitSymbol);
	numChars++;
}
uint16_t wgVerGauge::getPixel(int xcoord, int ycoord)
{
	int xc = xcoord - x;
	int yc = ycoord - y;
//	if(value < 0 || value > 255)
//		return 0;
	int yval = _height-(_value-minVal)*_height/(maxVal-minVal);
	uint16_t pix = 0;
	if((yc>=_height/2 && yc < (_height/2 + CHAR_HEIGHT-1)) && (xc >= (_width - CHAR_WIDTH*numChars)/2) && (xc < ((_width - CHAR_WIDTH*numChars)/2)+CHAR_WIDTH*numChars))
	{
		int xl = xc - (_width - CHAR_WIDTH*numChars)/2;
		int yl = yc - _height/2;
		if(buffer[yl+CHAR_HEIGHT*(xl/8)]>>(7-(xl%8)) & 0x01)
			pix = 0xFFFF;
	}
	if(((yval > yc)&& yc !=0 && yc != _height && xc !=0 && xc != _width) || yc == 1 || yc == _height - 1 || xc == 1 || xc == _width - 1)
		return 0xFFFF ^ pix;
	else
		return 0 ^ pix;
}

uint32_t wgVerGauge::getValueWhenClicked(uint16_t ax, uint16_t ay)
{
	int xc = ax - x;
	int yc = ay - y;

	return maxVal-yc*(maxVal-minVal)/(_height);
}
