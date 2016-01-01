#ifndef _BRAIN_H_
#define _BRAIN_H_
#include "listener.h"
#include "cothread.h"

#define LISTENER_TYPE_BRAIN 2
class Brain : public Listener, public CoThread
{
public:
	Brain():Listener(LISTENER_TYPE_BRAIN){}
	virtual void update(Emitter* emitter, void* data, DATA_TYPE data_type)
	{
		Mbox::Message msg;
		switch (data_type) {
		case DATA_TYPE_UINT32:
			msg.SenderPtr = emitter;
			msg.data = *((uint32_t*)data);
			MailBox->sendMail(msg);
			break;
		default:
			break;
		}
	}
protected:
	virtual void run() = 0;
};

#endif //_BRAIN_H_
