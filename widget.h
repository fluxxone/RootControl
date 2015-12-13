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
	virtual void setValue(Emitter* emitter,uint32_t val) = 0;
	virtual uint16_t getPixel(int xcoord, int ycoord) = 0;
	int getWidth() {return _width;}
	int getHeight() {return _height;}
	virtual void addToDisplay(Display* display);
	virtual void listen(Sensor* sensor);
	virtual void update(Emitter* emitter, uint32_t _value);
	bool isInside(uint16_t ax, uint16_t ay);
	virtual uint32_t getValueWhenClicked(uint16_t ax, uint16_t ay)=0;
protected:
	int _width;
	int _height;
	uint32_t _value;
};

#endif //_WIDGET_H_
