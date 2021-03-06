#ifndef _BRAINROOT_H_
#define _BRAINROOT_H_
#include "brain.h"
#include "senspassthru.h"
#include "acthumi.h"
#include "acttemp.h"
#include "actled.h"
#include "sdfile.h"
#include <string.h>

/*Setting are here (temporarily)*/
#include "rootcontrolsettings.h"

class Emitter;
class BrainRoot : public Brain
{
public:
	BrainRoot() : refHumi(SENSOR_ID_REF_HUMIDITY),refTemp(SENSOR_ID_REF_TEMPERATURE)
	{
		_LedFlag = false;
		_targetHumi = HUMIDITY_THRESHOLD;
		_targetTemp = TEMPERATURE_THRESHOLD;
		refHumi.setVal(_targetHumi);
		refTemp.setVal(_targetTemp);

		_tempHyst = TEMPERATURE_HYSTERESIS;
		_humiHyst = HUMIDITY_HYSTERESIS;

		_hrOn = HRS_TURN_ON;
		_minOn = MINS_TURN_ON;
		_hrOff = HRS_TURN_OFF;
		_minOff = MINS_TURN_OFF;
		memset(_logbuffer,0,sizeof(_logbuffer));

		if(!_brainfile.Open("0:/BRAINLOG.TXT"))
			DEBUG.print("ERROR: Brain LOG file not opened!\r\n");
		else
			DEBUG.print("Brain LOG file successfully opened\r\n");

	}
	virtual void run();
	void setTargetHumidity(uint16_t val) { _targetHumi = val;refHumi.setVal(_targetHumi);}
	void setTargetTemperature(uint16_t val) { _targetTemp = val;refTemp.setVal(_targetTemp);}
	sensPassthru refHumi;
	sensPassthru refTemp;
	actHumi humidityActuator;
	actTemp temperatureActuator;
	actLed ledActuator;
	SDFile _brainfile;
protected:
	void writeLog(const char* format, ...);
	uint16_t _targetHumi;
	uint16_t _targetTemp;
	uint32_t _humiHyst;
	uint32_t _tempHyst;
	uint32_t _hrOn;
	uint32_t _minOn;
	uint32_t _hrOff;
	uint32_t _minOff;
	bool _LedFlag;
	char _logbuffer[255];
};
#endif //_BRAINROOT_H_
