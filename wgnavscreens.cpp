#include "wgnavscreens.h"
#include "display.h"
#define CHAR_WIDTH	8
#define CHAR_HEIGHT	16
uint16_t wgNavScreens::getPixel(int xcoord, int ycoord)
{
	int xc = xcoord - _x;
	int yc = ycoord - _y;
//	if(value < 0 || value > 255)
//		return 0;
	uint16_t pix = 0;
	if((yc>=(_height/2 - CHAR_HEIGHT/2) && yc < (_height/2 - CHAR_HEIGHT/2 + CHAR_HEIGHT)) && (xc >= (_width - CHAR_WIDTH*_numChars)/2) && (xc < ((_width - CHAR_WIDTH*_numChars)/2)+CHAR_WIDTH*_numChars))
	{
		int xl = xc - (_width - CHAR_WIDTH*_numChars)/2;
		int yl = yc - _height/2 + CHAR_HEIGHT/2;
		if(_buffer[yl+CHAR_HEIGHT*(xl/8)]>>(7-(xl%8)) & 0x01)
			pix = 0xFFFF;
	}
	if (yc !=0 && yc != _height && xc !=0 && xc != _width)
		return COLOR_RED ^ pix;
	else
		return 0 ^ pix;
}

uint32_t wgNavScreens::getValueWhenClicked(uint16_t ax, uint16_t ay)
{
	(void)ax;
	(void)ay;
	switch (_type) {
	case WGNAVSCREENS_TYPE_MOVE_FIRST:
		DEBUG.print("Going to first screen\r\n");
		DISPLAY.setActiveScreen(0);
		break;
	case WGNAVSCREENS_TYPE_MOVE_LAST:
		DEBUG.print("Going to last screen\r\n");
		DISPLAY.setActiveScreen(DISPLAY.getNumScreens()-1);
		break;
	case WGNAVSCREENS_TYPE_MOVE_NEXT:
		DEBUG.print("Going to next screen\r\n");
		DISPLAY.setActiveScreen((DISPLAY.getActiveScreen()+1) % DISPLAY.getNumScreens());
		break;
	case WGNAVSCREENS_TYPE_MOVE_PREV:
		DEBUG.print("Going to prev screen\r\n");
		DISPLAY.setActiveScreen((DISPLAY.getActiveScreen()+DISPLAY.getNumScreens()-1) % DISPLAY.getNumScreens());
		break;
	default:
		break;
	}


	return 1;
}

