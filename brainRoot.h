#ifndef _BRAINROOT_H_
#define _BRAINROOT_H_
#include "brain.h"
#include "senspassthru.h"
#include "acthumi.h"
#include "acttemp.h"
class Emitter;
class BrainRoot : public Brain
{
public:
	BrainRoot() : refHumi(SENSOR_ID_REF_HUMIDITY),refTemp(SENSOR_ID_REF_TEMPERATURE)
	{
		_targetHumi = 800;
		_targetTemp = 250;
		refHumi.setVal(_targetHumi);
		refTemp.setVal(_targetTemp);

	}
	virtual void run();
	void setTargetHumidity(uint16_t val) { _targetHumi = val;refHumi.setVal(_targetHumi);}
	void setTargetTemperature(uint16_t val) { _targetTemp = val;refTemp.setVal(_targetTemp);}
	sensPassthru refHumi;
	sensPassthru refTemp;
	actHumi humidityActuator;
	actTemp temperatureActuator;
protected:

	uint16_t _targetHumi;
	uint16_t _targetTemp;
};
#endif //_BRAINROOT_H_
