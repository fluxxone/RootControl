#include "thread.h"

Thread* Thread::threads[MAX_NUM_THREADS]={0};
int Thread::numThreads = 0;

void Thread::runThread(void* threadToRun)
{
	((Thread*)threadToRun)->run();
}
