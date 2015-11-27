#include "sensDummy.h"

#include "listener.h"
void sensDummy::run()
{
	while(1)
	{

		for(int i = 0; i < numListeners; i++)
		{
			listeners[i]->update(this, val);
		}
		if(++val>255)
			val=0;
		CoTimeDelay(0,0,0,200);
	}
}
