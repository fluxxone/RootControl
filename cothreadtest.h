#ifndef _COTHREADTEST_H_
#define _COTHREADTEST_H_
#include <stdio.h>
class CoThreadTest : public CoThread
{
public:
	int val;
protected:
	virtual void run();

};
void CoThreadTest::run()
{
	while(1)
	{
		//printf("Aaa!");
		val++;
		CoTimeDelay(0,0,1,0);
	}
}
#endif //_COTHREADTEST_H_
