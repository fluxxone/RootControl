#ifndef ACTHUMI_H
#define ACTHUMI_H
#include "actuator.h"
typedef enum
{
	ACTHUMI_TURN_OFF,
	ACTHUMI_HUMIDIFY,
	ACTHUMI_DEHUMIDIFY
}
ACTHUMI_STATES;
class actHumi : public Actuator
{
public:
	virtual void setValue(uint32_t value)
	{


		switch(value)
		{
		case ACTHUMI_TURN_OFF:
			//turn off
			status.setVal(COLOR_WHITE);
			break;
		case ACTHUMI_HUMIDIFY:
			//humidify
			status.setVal(COLOR_RED);
			break;
		case ACTHUMI_DEHUMIDIFY:
			//dehumidify
			status.setVal(COLOR_BLUE);
			break;
		default:
			//do nothing
			break;
		}
		status.updateListeners();
	}
};

#endif // ACTHUMI_H
