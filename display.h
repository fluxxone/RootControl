#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include <stdint.h>
#include "cothread.h"
#include "listener.h"
#define DISPLAY_HEIGHT	240
#define DISPLAY_WIDTH	320
#define LISTENER_TYPE_SCREEN 3

#define COLOR_RED	0xF800
#define COLOR_GREEN	0x07E0
#define COLOR_BLUE	0x001F

class Widget;
class Display : public CoThread
{
public:
	Widget* widgets[1000];
	virtual uint16_t getPixels(int x, int y);
	virtual void addWidget(Widget* widget);
	Display();
	virtual void run();
	Widget* getTargetWidget(uint16_t x, uint16_t y);
protected:
	int numWidgets;
	uint8_t widgetMask[DISPLAY_WIDTH*DISPLAY_HEIGHT/8 + DISPLAY_HEIGHT];
	void SetPixelMask(uint16_t x, uint16_t y);
	bool GetPixelMask(uint16_t x, uint16_t y);
};


#endif //_DISPLAY_H_
