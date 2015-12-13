#include "brainRoot.h"
#include "debug.h"
void BrainRoot::run()
{
	DEBUG.print("Brain thread started!\r\n");

	while(1)
	{
		Mbox::Message msg = MailBox->pendMail();
		int d = msg.data;
	}
}

//void BrainRoot::update(Emitter* emitter, int value)
//{
//	Mbox::Message msg;
//	msg.SenderPtr = emitter;
//	msg.data = value;
//	MailBox->sendMail(msg);
//}
