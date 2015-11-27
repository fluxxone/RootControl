#ifndef _BRAIN_H_
#define _BRAIN_H_
#include "listener.h"
#include "cothread.h"

#define LISTENER_TYPE_BRAIN 2
class Brain : public Listener, public CoThread
{
public:
	Brain():Listener(LISTENER_TYPE_BRAIN){}
	virtual void update(Emitter* emitter, uint32_t value)
	{
		Mbox::Message msg;
		msg.SenderPtr = emitter;
		msg.data = value;
		MailBox->sendMail(msg);
	}
protected:
	virtual void run() = 0;
};

#endif //_BRAIN_H_
