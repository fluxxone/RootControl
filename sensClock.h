#ifndef _SENSCLOCK_H_
#define _SENSCLOCK_H_

#include "sensor.h"

class sensClock : public Sensor
{
public:
	sensClock();
protected:
	virtual void run();
};


#endif //_SENSCLOCK_H_
