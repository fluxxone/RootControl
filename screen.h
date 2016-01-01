#ifndef _SCREEN_H_
#define _SCREEN_H_
#include <stdint.h>
#include "cothread.h"
#include "listener.h"
#include "display.h"
#include "project.h"
#define LISTENER_TYPE_SCREEN 3


#define SCREEN_MAX_NUM_WIDGETS	10
class Widget;
class Screen
{
public:
	Widget* widgets[SCREEN_MAX_NUM_WIDGETS];
	virtual uint16_t getPixels(int x, int y);
	virtual void addWidget(Widget* widget);
	Screen();
	Widget* getTargetWidget(uint16_t x, uint16_t y);
	int getNumWidgets() { return numWidgets;}
protected:
	int numWidgets;
//	uint8_t widgetMask[DISPLAY_WIDTH*DISPLAY_HEIGHT/8 + DISPLAY_HEIGHT];
//	void SetPixelMask(uint16_t x, uint16_t y);
//	bool GetPixelMask(uint16_t x, uint16_t y);
};


#endif //_SCREEN_H_
