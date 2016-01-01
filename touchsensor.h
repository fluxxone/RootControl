#ifndef _TOUCHSENSOR_H_
#define _TOUCHSENSOR_H_
#include "sensor.h"
class Display;
class TouchSensor : public Sensor
{
public:
	TouchSensor(SENSOR_ID ID, Display* display);
	void calibrate();
	static void tpinterrupt();
	static TouchSensor* current;
	uint16_t xValue;
	uint16_t yValue;
protected:
	Display* _display;
	virtual void run();

};

#endif //_TOUCHSENSOR_H_
