#ifndef _SENSCLOCK_H_
#define _SENSCLOCK_H_

#include "sensor.h"
#define SENSCLOCK (static_cast<sensClock&>(sensClock::getInstance()))
class sensClock : public Sensor
{
public:
	static sensClock& getInstance();
	const char* getTimeDate() { return _timeDate;}
protected:
	sensClock(SENSOR_ID ID);
	virtual void run();
	char _timeDate[24];
};


#endif //_SENSCLOCK_H_
