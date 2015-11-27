#include "cothread.h"
#include <CoOS.h>
OS_STK CoThread::CoTaskStack[MAX_COTASK_STACK*MAX_COTASK_THREADS] = {0};
void CoThread::start()
{
	CoCreateTask (Thread::runThread,(void*)this,0,&((CoThread::CoTaskStack)[MAX_COTASK_STACK + MAX_COTASK_STACK*threadID-1]),MAX_COTASK_STACK);
}

CoThread::CoThread()
{
//	if(!isInitialized)
//	{
//		InitCoOS();
//	}
	MailBox = &mbox;
}

void CoThread::StartCoOS()
{
	CoStartOS();
}

bool CoThread::isInitialized = false;

void CoThread::InitCoOS()
{
	isInitialized = true;
	CoInitOS();
}
