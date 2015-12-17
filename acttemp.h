#ifndef ACTTEMP
#define ACTTEMP
#include "actuator.h"
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
		status.setVal(value);

		switch(value)
		{
		case ACTTEMP_TURN_OFF:
			//turn off
			break;
		case ACTTEMP_HEAT_ON:
			//heat on
			break;
		case ACTTEMP_COOL_ON:
			//cool off
			break;
		default:
			//do nothing
			break;
		}
	}
};

#endif // ACTTEMP

