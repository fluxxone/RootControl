#ifndef _MBOX_H_
#define _MBOX_H_
#include <stdint-gcc.h>

class Emitter;
class Mbox
{
public:
	struct Message
	{
		Emitter* SenderPtr;
		uint32_t data;
	};
	virtual bool sendMail(Message & msg, bool fromInterrup = false) = 0;
	virtual Message pendMail() = 0;
};

#endif //_MBOX_H_
