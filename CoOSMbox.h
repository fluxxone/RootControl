#ifndef _COOSMBOX_H_
#define _COOSMBOX_H_

#include "MBox.h"
#include <CoOS.h>
#define COOSMBOX_BUFFER_SIZE 8
class Emitter;
class CoOSMbox : public Mbox
{
public:
	CoOSMbox();
	virtual bool sendMail(Message & msg, bool fromInterrup = false);
	virtual Message pendMail();
protected:
	Message buffer[COOSMBOX_BUFFER_SIZE];
	uint8_t head, tail;
	OS_EventID MailQueue;
	void* bufferptrs[COOSMBOX_BUFFER_SIZE];

	uint8_t incHead() { return (head + 1) % COOSMBOX_BUFFER_SIZE; }
	uint8_t incTail() { return (tail + 1) % COOSMBOX_BUFFER_SIZE; }
};

#endif //_COOSMBOX_H_
