#include "wglabel.h"
#include "AsciiLib.h"
#include "project.h"
#include "stdio.h"
#define CHAR_WIDTH	8
#define CHAR_HEIGHT	16
uint16_t wgLabel::getPixel(int xcoord, int ycoord)
{
	int xc = xcoord - _x;
	int yc = ycoord - _y;
//	if(value < 0 || value > 255)
//		return 0;
	uint16_t pix = 0;
	unsigned char buffer[16];
	if((yc>=(_height/2 - CHAR_HEIGHT/2) && yc < (_height/2 - CHAR_HEIGHT/2 + CHAR_HEIGHT)) && (xc >= (_width - CHAR_WIDTH*_textLen)/2) && (xc < ((_width - CHAR_WIDTH*_textLen)/2)+CHAR_WIDTH*_textLen))
	{
		int xl = xc - (_width - CHAR_WIDTH*_textLen)/2;
		int yl = yc - _height/2 + CHAR_HEIGHT/2;
		uint8_t ind = xl/8;
		GetASCIICode(buffer,_text[ind]);
		if(buffer[yl]>>(7-(xl%CHAR_WIDTH)) & 0x01)
			pix = _foregroundColor;
	}
	if( yc !=0 && yc != _height && xc !=0 && xc != _width)
		return _backgroundColor ^ pix;
	else
		return 0 ^ pix;
}
void wgLabel::update(Emitter* emitter, void* data, DATA_TYPE data_type)
{
	switch (data_type) {
	case DATA_TYPE_UINT32:
		char number[9];
		snprintf(number,9,"%d",*((uint32_t*)data));
		setText(number);
		break;
	case DATA_TYPE_STRING:
		setText((char*)data);
	default:
		break;
	}

}
