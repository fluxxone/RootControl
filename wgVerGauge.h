#include "widget.h"
#define MAX_NUM_CHARS	6
class wgVerGauge : public Widget
{
public:
	wgVerGauge(uint8_t xarg, uint8_t yarg, uint8_t w, uint8_t h, uint32_t max_val, uint32_t min_val) : Widget(xarg, yarg, h, w),numChars(0),_multiplier(1),_divider(1),maxVal(max_val), minVal(min_val),_unitSymbol('%') {}
	virtual void setValue(Emitter* emitter, uint32_t val);
	virtual uint16_t getPixel(int xcoord, int ycoord);
	virtual uint32_t getValueWhenClicked(uint16_t ax, uint16_t ay);
	void setUnit(char unitSymbol){_unitSymbol = unitSymbol;}
	void setScaleFactor(uint32_t divider, uint32_t multiplier){_divider=divider;_multiplier=multiplier;}
protected:
	unsigned char buffer[16*MAX_NUM_CHARS];
	uint8_t numChars;
	uint32_t maxVal;
	uint32_t minVal;
	uint32_t _divider;
	uint32_t _multiplier;
	char _unitSymbol;
};
