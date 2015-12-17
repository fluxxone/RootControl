#include "sensClock.h"
#include "stm32f10x_rtc.h"
#include "listener.h"
void sensClock::run()
{
	while(1)
	{
		for(int i = 0; i < _numListeners; i++)
		{
			_listeners[i]->update(this, 0);
		}
		CoTimeDelay(0,0,1,0);
	}
}

sensClock::sensClock(SENSOR_ID ID) : Sensor(ID)
{
//	NVIC_InitTypeDef NVIC_InitStructure;

//	/* Configure one bit for preemption priority */
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

//	/* Enable the RTC Interrupt */
//	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
//	NVIC_Init(&NVIC_InitStructure);

//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

//	PWR_BackupAccessCmd(ENABLE);
//	RCC_LSEConfig(RCC_LSE_ON);
//	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET);
//	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
//	RCC_RTCCLKCmd(ENABLE);

//	RTC_WaitForSynchro();
//	RTC_WaitForLastTask();
//	RTC_ITConfig(RTC_IT_SEC, ENABLE);
//	RTC_WaitForLastTask();
//	RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */
//	RTC_WaitForLastTask();
}

extern "C"
{
	void RTC_IRQHandler(void)
	{
		if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
		{
			RTC_ClearITPendingBit(RTC_IT_SEC);
			RTC_WaitForLastTask();
		}
	}
}
