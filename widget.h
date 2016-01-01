#ifndef _WIDGET_H_
#define _WIDGET_H_
#include "listener.h"
#define LISTENER_TYPE_WIDGET 1
#include <stdint-gcc.h>

//#define uint16_t unsigned int

class Screen;
class Sensor;
class Emitter;
class Widget : public Listener
{
public:

	Widget(uint16_t xarg, uint16_t yarg, uint16_t height, uint16_t width);
	virtual void setValue(Emitter* emitter,uint32_t val) = 0;
	virtual uint16_t getPixel(int xcoord, int ycoord) = 0;
	uint8_t getWidth() {return _width;}
	uint8_t getHeight() {return _height;}
	uint8_t getX() {return _x;}
	uint8_t getY() {return _y;}
	virtual void addToDisplay(Screen* display);
	virtual void listen(Sensor* sensor);
	virtual void update(Emitter* emitter, void* data, DATA_TYPE data_type);
	bool isInside(uint16_t ax, uint16_t ay);
	virtual uint32_t getValueWhenClicked(uint16_t ax, uint16_t ay)=0;
protected:
	uint16_t _width;
	uint16_t _height;
	uint16_t _x;
	uint16_t _y;
	uint32_t _value;
};

#endif //_WIDGET_H_
