#ifndef _SENS_HUMIDITY_H_
#define _SENS_HUMIDITY_H_
#include "sensor.h"
#include "listener.h"
#include "senspassthru.h"
class sensHumidityTemperature : public CoThread
{
public:
	sensPassthru sensHumi;
	sensPassthru sensTemp;
	sensHumidityTemperature();
protected:
	virtual void run();
	uint16_t currentHumidity;
	uint16_t currentTemperature;
	uint8_t buffer[8];
};


#endif //_SENS_HUMIDITY_H_
