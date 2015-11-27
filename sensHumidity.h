#ifndef _SENS_HUMIDITY_H_
#define _SENS_HUMIDITY_H_
#include "sensor.h"

class sensHumidity : public Sensor
{
public:
	sensHumidity();
protected:
	virtual void run();
};


#endif //_SENS_HUMIDITY_H_
