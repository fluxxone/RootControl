#include "sensor.h"
#include "listener.h"
Sensor::Sensor()
{
	numListeners = 0;
}
void Sensor::addListener(Listener* listener)
{
	listeners[numListeners++] = listener;
}
