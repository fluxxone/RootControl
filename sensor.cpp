#include "sensor.h"
#include "listener.h"
Sensor::Sensor(SENSOR_ID sensID) : _sensID(sensID)
{
	_numListeners = 0;
}
void Sensor::addListener(Listener* listener)
{
	_listeners[_numListeners++] = listener;
}
