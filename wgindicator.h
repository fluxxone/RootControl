#ifndef WGINDICATOR_H
#define WGINDICATOR_H
#include "widget.h"
#include "project.h"
class wgIndicator : public Widget
{
public:
	wgIndicator(uint16_t x, uint16_t y,uint16_t h, uint16_t w, uint16_t initColor = COLOR_WHITE):Widget(x,y,h,w)
	{
		_color = initColor;
	}
	virtual void setValue(Emitter* emitter,uint32_t val) {_color = val;}
	virtual uint32_t getValueWhenClicked(uint16_t ax, uint16_t ay) { return 0;}
	virtual uint16_t getPixel(int xcoord, int ycoord);
protected:
	uint16_t _color;
};

#endif // WGINDICATOR_H
