#ifndef _SENSDUMMY_H_
#define _SENSDUMMY_H_

#include "sensor.h"

class sensDummy : public Sensor
{
public:
	sensDummy(int v):val(v) {}
protected:
	virtual void run();
	int val;
};

#endif
