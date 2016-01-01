#ifndef WGLABEL_H
#define WGLABEL_H
#include "widget.h"
#include <string.h>
#include "project.h"
#define WGLABEL_MAX_LENGTH 24
class wgLabel : public Widget
{
public:
	wgLabel(uint16_t x, uint16_t y,uint16_t h, uint16_t w):Widget(x,y,h,w)
	{
		memset(_text,0,WGLABEL_MAX_LENGTH);
		_textLen = 0;
		_foregroundColor = COLOR_GREEN;
		_backgroundColor = COLOR_BLACK;

	}
	virtual void setValue(Emitter* emitter,uint32_t val) {}
	void setText(char* text)
	{
		_textLen = strlen(text);
		if(_textLen > WGLABEL_MAX_LENGTH)
			_textLen = WGLABEL_MAX_LENGTH;
		strncpy(_text,text,WGLABEL_MAX_LENGTH);

	}
	virtual void update(Emitter* emitter, void* data, DATA_TYPE data_type);
	virtual uint32_t getValueWhenClicked(uint16_t ax, uint16_t ay) { return 0;}
	virtual uint16_t getPixel(int xcoord, int ycoord);
protected:
	char _text[WGLABEL_MAX_LENGTH];
	uint8_t _textLen;
	uint16_t _foregroundColor;
	uint16_t _backgroundColor;
};

#endif // WGLABEL_H
