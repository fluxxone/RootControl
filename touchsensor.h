#ifndef _TOUCHSENSOR_H_
#define _TOUCHSENSOR_H_
#include "sensor.h"
class Display;
class TouchSensor : public Sensor
{
public:
	TouchSensor(Display* arg);
	void calibrate();
	static void tpinterrupt();
	static TouchSensor* current;
	uint16_t xValue;
	uint16_t yValue;
protected:
	Display* disp;
	virtual void run();

};

#endif //_TOUCHSENSOR_H_