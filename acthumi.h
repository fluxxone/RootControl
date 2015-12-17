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
		status.setVal(value);

		switch(value)
		{
		case ACTHUMI_TURN_OFF:
			//turn off
			break;
		case ACTHUMI_HUMIDIFY:
			//humidify
			break;
		case ACTHUMI_DEHUMIDIFY:
			//dehumidify
			break;
		default:
			//do nothing
			break;
		}
	}
};

#endif // ACTHUMI_H
