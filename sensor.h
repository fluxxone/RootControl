#ifndef _SENSOR_H_
#define _SENSOR_H_
#include "emitter.h"
#include "cothread.h"
#include "debug.h"
#include "project.h"

#define EMITTER_TYPE_SENSOR 1
class Listener;
class Sensor : public Emitter,public CoThread
{
public:
	Sensor(SENSOR_ID sensID);
	virtual void addListener(Listener* listener);
	SENSOR_ID getSensorID(){return _sensID;}
	virtual int getEmitterType(){return EMITTER_TYPE_SENSOR;}
	uint32_t getValue(){return _value;}
protected:
	virtual void run() = 0;
	uint32_t _value;
	Listener* _listeners[20];
	uint8_t _numListeners;
	SENSOR_ID _sensID;
};
#endif //_SENSOR_H_
