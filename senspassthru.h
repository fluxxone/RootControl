#ifndef SENSPASSTHRU
#define SENSPASSTHRU
#include "sensor.h"
#include "listener.h"
class sensPassthru : public Sensor
{
public:
	sensPassthru(SENSOR_ID id):Sensor(id){}
	void setVal(uint16_t arg){_value = arg;}
	void updateListeners()
	{
		for(int i = 0; i < _numListeners; i++)
		{
			_listeners[i]->update(this, _value);
		}
	}

protected:
	virtual void run()
	{
	}
};
#endif // SENSPASSTHRU

