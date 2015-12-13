#ifndef _SENS_HUMIDITY_H_
#define _SENS_HUMIDITY_H_
#include "sensor.h"
#include "listener.h"
class sensHumidityTemperature : public CoThread
{
public:
	class sensPassthru : public Sensor
	{
	public:
		void setVal(uint16_t arg){_value = arg;}
		void updateListeners()
		{
			for(int i = 0; i < _numListeners; i++)
			{
				_listeners[i]->update(this, _value);
			}
		}

	protected:
		uint32_t _value;
		virtual void run()
		{
		}
	};
	sensPassthru sensHumi;
	sensPassthru sensTemp;
	sensHumidityTemperature();

	//virtual void addListener(Listener* HumiListener, Listener* TempListener);
protected:
	virtual void run();
	uint16_t currentHumidity;
	uint16_t currentTemperature;
	uint8_t buffer[8];
};


#endif //_SENS_HUMIDITY_H_
