#ifndef _ACTTEMP_H_
#define _ACTTEMP_H_
#include "actuator.h"
#include "project.h"
typedef enum
{
	ACTTEMP_TURN_OFF,
	ACTTEMP_HEAT_ON,
	ACTTEMP_COOL_ON
}
ACTTEMP_STATES;
class actTemp : public Actuator
{
public:
	actTemp()
	{
		initGPIO();
	}

	virtual void setValue(uint32_t value)
	{
		switch(value)
		{
		case ACTTEMP_TURN_OFF:
			//turn off
			heat(false);
			cool(false);
			status.setVal(COLOR_WHITE);
			break;
		case ACTTEMP_HEAT_ON:
			//heat on
			heat(true);
			status.setVal(COLOR_RED);
			break;
		case ACTTEMP_COOL_ON:
			//cool off
			cool(true);
			status.setVal(COLOR_BLUE);
			break;
		default:
			//do nothing
			break;
		}
		status.updateListeners();
	}
protected:
	static void initGPIO();
	static void heat(bool onOff);
	static void cool(bool onOff);
};

#endif // ACTTEMP

