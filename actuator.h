#ifndef ACTUATOR_H
#define ACTUATOR_H
#include "sensor.h"
#include "senspassthru.h"
class Actuator
{
public:
	Actuator() : status(SENSOR_ID_DUMMY) {}
	virtual void setValue(uint32_t) = 0;
	sensPassthru status;
	virtual uint32_t getValue()
	{
		return status.getValue();
	}
};

#endif // ACTUATOR_H
