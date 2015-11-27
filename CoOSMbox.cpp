#include "CoOSMbox.h"

CoOSMbox::CoOSMbox()
{

	MailQueue = CoCreateQueue(bufferptrs, COOSMBOX_BUFFER_SIZE, EVENT_SORT_TYPE_FIFO);
	head = tail = 0;
}


bool CoOSMbox::sendMail(Mbox::Message & msg, bool fromInterrupt)
{
	if(incHead() == tail) //fifo full
		return false;
	int err=0;
	buffer[head = incHead()] = msg;
	if(fromInterrupt)
	{
		isr_PostQueueMail(MailQueue,(void*)(&buffer[head]));
	}
	else
		switch(CoPostQueueMail(MailQueue,(void*)(&buffer[head])))
		{
		case E_OK:
			return true;
		case E_INVALID_ID:
			err=E_INVALID_ID;
			return false;
		case E_QUEUE_FULL:
			err=E_QUEUE_FULL;
			return false;
		default:
			err=255;
			return false;
		}
}
Mbox::Message CoOSMbox::pendMail()
{
	StatusType err;
	Mbox::Message tmp = *((Mbox::Message*)CoPendQueueMail(MailQueue,0,&err));
	err;
	tail = incTail();
	return tmp;
}

