#ifndef _COTHREAD_H_
#define _COTHREAD_H_
#include "thread.h"
#include "CoOS.h"
#include "CoOSMbox.h"

#define MAX_COTASK_QUEUE 10
#define MAX_COTASK_STACK 768
#define MAX_COTASK_THREADS CFG_MAX_USER_TASKS
class CoThread : public Thread
{
public:
	CoThread();
	virtual void start();
	static void StartCoOS();
	static void InitCoOS();
protected:
	//OS_TID threadID;
	CoOSMbox mbox;
	virtual void run() = 0;
	static OS_STK CoTaskStack[MAX_COTASK_STACK*MAX_COTASK_THREADS];
	static uint8_t numStarted;
	static bool isInitialized;
};
#endif
