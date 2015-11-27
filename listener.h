#ifndef _LISTENER_H_
#define _LISTENER_H_
#include <stdint-gcc.h>

class Emitter;
class Listener
{
public:
	virtual void update(Emitter* emitter, uint32_t value) = 0;
	Listener(int type):listenerType(type){}
	int getListenerType(){return listenerType;}
protected:
	int listenerType;

};

#endif //_LISTENER_H_
