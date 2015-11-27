#include "thread.h"

Thread* Thread::threads[10]{0};
int Thread::numThreads = 0;

void Thread::runThread(void* threadToRun)
{
	((Thread*)threadToRun)->run();
}
