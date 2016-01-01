#ifndef WGNAVSCREENS_H
#define WGNAVSCREENS_H
#include "widget.h"
#include "AsciiLib.h"
#include "project.h"
#define WGNAVSCREENS_MAX_NUM_CHARS 2
typedef enum
{
	WGNAVSCREENS_TYPE_MOVE_NEXT,
	WGNAVSCREENS_TYPE_MOVE_PREV,
	WGNAVSCREENS_TYPE_MOVE_FIRST,
	WGNAVSCREENS_TYPE_MOVE_LAST
}
WGNAVSCREENS_TYPE;

class Display;
class wgNavScreens : public Widget
{
public:
	wgNavScreens(WGNAVSCREENS_TYPE type, uint16_t x, uint16_t y,uint16_t h, uint16_t w):_type(type), Widget(x,y,h,w)
	{
		_color = COLOR_RED;
		switch (_type) {
		case WGNAVSCREENS_TYPE_MOVE_FIRST:
			GetASCIICode(&_buffer[0],'<');
			GetASCIICode(&_buffer[1],'<');
			_numChars = 2;
			break;
		case WGNAVSCREENS_TYPE_MOVE_LAST:
			GetASCIICode(&_buffer[0],'>');
			GetASCIICode(&_buffer[1],'>');
			_numChars = 2;
			break;
		case WGNAVSCREENS_TYPE_MOVE_NEXT:
			GetASCIICode(&_buffer[0],'>');
			_numChars = 1;
			break;
		case WGNAVSCREENS_TYPE_MOVE_PREV:
			GetASCIICode(&_buffer[0],'<');
			_numChars = 1;
			break;
		default:
			break;
		}
	}
	virtual void setValue(Emitter* emitter,uint32_t val) {}
	virtual uint32_t getValueWhenClicked(uint16_t ax, uint16_t ay);
	virtual uint16_t getPixel(int xcoord, int ycoord);
protected:
	unsigned char _buffer[16*WGNAVSCREENS_MAX_NUM_CHARS];
	uint8_t _numChars;
	WGNAVSCREENS_TYPE _type;
	uint16_t _color;
};

#endif // WGNAVSCREENS_H
