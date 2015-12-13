#include "sensor.h"
#include "listener.h"
Sensor::Sensor()
{
	_numListeners = 0;
}
void Sensor::addListener(Listener* listener)
{
	_listeners[_numListeners++] = listener;
}
