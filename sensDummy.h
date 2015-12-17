#ifndef _SENSDUMMY_H_
#define _SENSDUMMY_H_

#include "sensor.h"

class sensDummy : public Sensor
{
public:
	sensDummy(SENSOR_ID ID,int v):Sensor(ID) {_value = v;}
protected:
	virtual void run();
};

#endif
