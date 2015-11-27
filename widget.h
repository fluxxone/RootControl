#ifndef _WIDGET_H_
#define _WIDGET_H_
#include "listener.h"

#define LISTENER_TYPE_WIDGET 1
#include <stdint-gcc.h>

//#define uint16_t unsigned int

class Display;
class Sensor;
class Emitter;
class Widget : public Listener
{
public:
	int x;
	int y;
	Widget(int xarg, int yarg);
	virtual void setValue(int val) = 0;
	virtual uint16_t getPixel(int xcoord, int ycoord) = 0;
	int getWidth() {return width;}
	int getHeight() {return height;}
	virtual void addToDisplay(Display* display);
	virtual void listen(Sensor* sensor);
	virtual void update(Emitter* emitter, uint32_t value);
	bool isInside(uint16_t ax, uint16_t ay);
	virtual uint8_t getValueWhenClicked(uint16_t ax, uint16_t ay)=0;
protected:
	int width;
	int height;
	int value;
};

#endif //_WIDGET_H_
