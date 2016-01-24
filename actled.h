#ifndef ACTLED_H
#define ACTLED_H
#include "actuator.h"

typedef enum
{
	ACTLED_OFF,
	ACTLED_ON
} ACTLED_STATES;

class actLed : public Actuator
{
public:
	actLed()
	{
		initGPIO();
	}

	virtual void setValue(uint32_t value)
	{
		if(value != ACTLED_OFF)
		{
			LED(true);
			status.setVal(COLOR_RED|COLOR_BLUE);
		}
		else
		{
			LED(false);
			status.setVal(COLOR_BLACK);
		}
		status.updateListeners();
	}
protected:
	static void initGPIO();
	static void LED(bool onOff);
};

#endif // ACTLED_H
