#ifndef _SENSOR_H_
#define _SENSOR_H_
#include "emitter.h"
#include "cothread.h"

class Listener;
class Sensor : public Emitter,public CoThread
{
public:
	Sensor();
	virtual void addListener(Listener* listener);
protected:
	virtual void run() = 0;
	Listener* listeners[100];
	int numListeners;
};
#endif //_SENSOR_H_
