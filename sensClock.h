#ifndef _SENSCLOCK_H_
#define _SENSCLOCK_H_

#include "sensor.h"
#include <time.h>
#define SENSCLOCK (static_cast<sensClock&>(sensClock::getInstance()))
class sensClock : public Sensor
{
public:
	static sensClock& getInstance();
	const char* getTimeDateStr() { return _timeDate;}
	time_t getTimeDateUnix() { return _timeUnix;}
	static struct tm Time_ConvUnixToCalendar(time_t t);
	static void Time_SetCalendarTime(struct tm t);
protected:
	sensClock(SENSOR_ID ID);
	virtual void run();
	char _timeDate[24];
	time_t _timeUnix;
};


#endif //_SENSCLOCK_H_
