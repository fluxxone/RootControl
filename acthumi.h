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
	actHumi()
	{
		initGPIO();
	}

	virtual void setValue(uint32_t value)
	{
		switch(value)
		{
		case ACTHUMI_TURN_OFF:
			//turn off
			humidify(false);
			dehumidify(false);
			status.setVal(COLOR_WHITE);
			break;
		case ACTHUMI_HUMIDIFY:
			//humidify
			humidify(true);
			status.setVal(COLOR_RED);
			break;
		case ACTHUMI_DEHUMIDIFY:
			//dehumidify
			dehumidify(true);
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
	static void humidify(bool onOff);
	static void dehumidify(bool onOff);
};

#endif // ACTHUMI_H
