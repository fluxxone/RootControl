#ifndef ACTTEMP
#define ACTTEMP
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
	virtual void setValue(uint32_t value)
	{


		switch(value)
		{
		case ACTTEMP_TURN_OFF:
			//turn off
			status.setVal(COLOR_WHITE);
			break;
		case ACTTEMP_HEAT_ON:
			//heat on
			status.setVal(COLOR_RED);
			break;
		case ACTTEMP_COOL_ON:
			//cool off
			status.setVal(COLOR_BLUE);
			break;
		default:
			//do nothing
			break;
		}
		status.updateListeners();
	}
};

#endif // ACTTEMP

