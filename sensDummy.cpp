#include "sensDummy.h"
#include "debug.h"
#include "listener.h"
void sensDummy::run()
{
	DEBUG.print("sensDummy thread started!\r\n");
	while(1)
	{

		for(int i = 0; i < _numListeners; i++)
		{
			_listeners[i]->update(this, val);
		}
		if(++val>255)
			val=0;
		CoTimeDelay(0,0,0,200);
	}
}
