#ifndef _THREAD_H_
#define _THREAD_H_

#include "OsConfig.h"
#include "debug.h"
#define MAX_NUM_THREADS CFG_MAX_USER_TASKS
class Mbox;
class Thread
{
public:
	Thread()
	{
		threadID=numThreads++;
//		if(numThreads > MAX_NUM_THREADS)
//			DEBUG.print("WARNING: Maximum number of threads exceeded (%d). Some threads may not start!\r\n",MAX_NUM_THREADS);
	}
	virtual void run() = 0;
	virtual void start() = 0;
	Mbox* MailBox;

protected:
	int threadID;
	static void runThread(void* threadToRun); //for universality, Thread* is replaced with void*
	static Thread* threads[MAX_NUM_THREADS];
	static int numThreads;
};
#endif //_THREAD_H_
