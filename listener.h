#ifndef _LISTENER_H_
#define _LISTENER_H_
#include <stdint-gcc.h>
typedef enum
{
	DATA_TYPE_INVALID,
	DATA_TYPE_UINT32,
	DATA_TYPE_INT32,
	DATA_TYPE_STRING,

}
DATA_TYPE;
class Emitter;
class Listener
{
public:
	virtual void update(Emitter* emitter, void* data, DATA_TYPE data_type) = 0;
	Listener(int type):listenerType(type){}
	int getListenerType(){return listenerType;}
protected:
	int listenerType;

};

#endif //_LISTENER_H_
