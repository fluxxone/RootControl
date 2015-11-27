#include "widget.h"

class wgVerGauge : public Widget
{
public:
	wgVerGauge(int xarg, int yarg, int w, int h) : Widget(xarg, yarg) {width = w; height = h;}
	virtual void setValue(int val);
	virtual uint16_t getPixel(int xcoord, int ycoord);
	virtual uint8_t getValueWhenClicked(uint16_t ax, uint16_t ay);
protected:
	unsigned char buffer[16*3];
};
