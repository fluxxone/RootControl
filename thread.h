#ifndef _THREAD_H_
#define _THREAD_H_
class Mbox;
class Thread
{
public:
	Thread()
	{
		threadID=numThreads++;
	}
	virtual void run() = 0;
	virtual void start() = 0;
	Mbox* MailBox;

protected:
	int threadID;
	static void runThread(void* threadToRun); //for universality, Thread* is replaced with void*
	static Thread* threads[10];
	static int numThreads;
};
#endif //_THREAD_H_
