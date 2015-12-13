#ifndef _SENSOR_H_
#define _SENSOR_H_
#include "emitter.h"
#include "cothread.h"
#include "debug.h"

class Listener;
class Sensor : public Emitter,public CoThread
{
public:
	Sensor();
	virtual void addListener(Listener* listener);
protected:
	virtual void run() = 0;
	Listener* _listeners[20];
	uint8_t _numListeners;
};
#endif //_SENSOR_H_
