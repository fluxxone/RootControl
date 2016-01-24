#include "sensClock.h"
#include "stm32f10x_rtc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_pwr.h"
#include "stm32f10x_bkp.h"
#include "stm32f10x_gpio.h"
#include "misc.h"
#include "listener.h"
#include "debug.h"
#include <string.h>
#include <time.h>
#include <stdio.h>

static void RTC_Configuration(void);
struct tm Time_GetCalendarTime(void);
time_t Time_GetUnixTime(void);
void RTC_Init(void);

sensClock& sensClock::getInstance()
{
	static sensClock instance(SENSOR_ID_CLOCK);
	return instance;
}
void sensClock::run()
{
	DEBUG.print("sensClock thread started!\r\n");
	while(1)
	{
		struct tm time;
		_timeUnix = Time_GetUnixTime();
		time = Time_GetCalendarTime();
		sprintf(_timeDate,"%d.%d.%d. %02d:%02d:%02d", time.tm_mday, \
			time.tm_mon+1, time.tm_year,\
			time.tm_hour, time.tm_min, time.tm_sec);
		for(int i = 0; i < _numListeners; i++)
		{
			_listeners[i]->update(this, 0, DATA_TYPE_INVALID);
			_listeners[i]->update(this, _timeDate, DATA_TYPE_STRING);
			_listeners[i]->update(this,(void*)(&_timeUnix),DATA_TYPE_INT32);

		}
		CoTimeDelay(0,0,1,0);
	}
}

sensClock::sensClock(SENSOR_ID ID) : Sensor(ID)
{
	_timeDate[0]=0;
//	static bool setClock = true;
//	if(setClock)
//	{
//		struct tm t;
//		t.tm_hour = 22;
//		t.tm_min = 5;
//		t.tm_sec = 0;
//		t.tm_isdst = 0;
//		t.tm_mday = 22;
//		t.tm_mon = 0;
//		t.tm_year = 2016;
//		RTC_Configuration();
//		DEBUG.print("Setting the clock!\r\n");
//		CoSchedLock();
//		sensClock::Time_SetCalendarTime(t);
//		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
//		CoSchedUnlock();
//		DEBUG.print("The clock is set!\r\n");
//		setClock = false;
//	}
	RTC_Init();
}



struct tm sensClock::Time_ConvUnixToCalendar(time_t t)
{
	struct tm *t_tm;
	t_tm = localtime(&t);
	t_tm->tm_year += 1900;
	return *t_tm;
}

struct tm Time_ConvUnixToCalendar(time_t t)
{
	struct tm *t_tm;
	t_tm = localtime(&t);
	t_tm->tm_year += 1900;
	return *t_tm;
}

time_t Time_ConvCalendarToUnix(struct tm t)
{
	t.tm_year -= 1900;  /* Íâ²¿tmœá¹¹ÌåŽæŽ¢µÄÄê·ÝÎª2008žñÊœ	*/
						/* ¶øtime.hÖÐ¶šÒåµÄÄê·ÝžñÊœÎª1900Äê¿ªÊŒµÄÄê·Ý */
						/* ËùÒÔ£¬ÔÚÈÕÆÚ×ª»»Ê±Òª¿ŒÂÇµœÕâžöÒòËØ¡£*/
	return mktime(&t);
}


time_t Time_GetUnixTime(void)
{
	return (time_t)RTC_GetCounter();
}

struct tm Time_GetCalendarTime(void)
{
	time_t t_t;
	struct tm t_tm;

	t_t = (time_t)RTC_GetCounter();
	t_tm = Time_ConvUnixToCalendar(t_t);
	return t_tm;
}


void Time_SetUnixTime(time_t t)
{
	RTC_WaitForLastTask();
	RTC_SetCounter((u32)t);
	RTC_WaitForLastTask();
	return;
}


void sensClock::Time_SetCalendarTime(struct tm t)
{
	Time_SetUnixTime(Time_ConvCalendarToUnix(t));
	return;
}


static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

  /* Enable the RTC Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void GPIO_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;

  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB , ENABLE);
/**
 *	LED1 -> PB0   LED2 -> PB1
 */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
}

static void RTC_Configuration(void)
{
	GPIO_Configuration();
  /* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Reset Backup Domain */
  BKP_DeInit();

  /* Enable LSE */
  RCC_LSEConfig(RCC_LSE_ON);
  /* Wait till LSE is ready */
  while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {}

  /* Select LSE as RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);

  /* Enable RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC registers synchronization */
  RTC_WaitForSynchro();

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Enable the RTC Second */
  RTC_ITConfig(RTC_IT_SEC, ENABLE);

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();

  /* Set RTC prescaler: set RTC period to 1sec */
  RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) */

  /* Wait until last write operation on RTC registers has finished */
  RTC_WaitForLastTask();
}

//static uint16_t USART_Scanf(uint32_t min_value,uint32_t max_value,uint8_t lenght)
//{
//  uint16_t index = 0;
//  uint32_t tmp[4] = {0, 0, 0, 0};

//  while (index < lenght)
//  {
//    /* Loop until RXNE = 1 */
//    while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET)
//    {}
//    tmp[index++] = (USART_ReceiveData(USART1));

//	if( tmp[index - 1] == 0x0D ) { index--; continue; }

//    if ((tmp[index - 1] < 0x30) || (tmp[index - 1] > 0x39))
//    {
//      DEBUG.print("Please enter valid number between 0 and 9\r\n");
//      index--;
//    }
//  }
//  /* Calculate the Corresponding value */
//  if( lenght ==2 )
//  index = (tmp[1] - 0x30) + ((tmp[0] - 0x30) * 10 );

//  else  /* lenght ==4 */
//  index = (tmp[3] - 0x30) + ((tmp[2] - 0x30) * 10 ) + ((tmp[1] - 0x30) * 100 ) + ((tmp[0] - 0x30) * 1000 );
//  /* Checks */
//  if (index > max_value || index < min_value)
//  {
//	DEBUG.print("Please enter valid number between %d and %d\r\n", min_value, max_value);
//    return 0;
//  }


//  return index;
//}


//void Time_Regulate(void)
//{
//  struct tm time;

//  memset(&time, 0 , sizeof(time) );	/* Çå¿Õœá¹¹Ìå */

//  DEBUG.print("=======================Time Settings==========================\r\n");
//  DEBUG.print("Please Set Years between 1970 to 2037\r\n");

//  while ( time.tm_year>2037  || time.tm_year<1970)
//  {
//    time.tm_year =1970;
//  }
//  DEBUG.print("Set Years:  %d\r\n", time.tm_year);

//  DEBUG.print("Please Set Months between 01 to 12\r\n");
//  while (time.tm_mon >12 || time.tm_mon < 1 )
//  {
//    time.tm_mon= 1;
//  }
//  DEBUG.print("Set Months:  %d\r\n", time.tm_mon);

//  DEBUG.print("Please Set Days between 01 to 31\r\n");
//  while (time.tm_mday >31 ||time.tm_mday <1 )
//  {
//    time.tm_mday =1;
//  }
//  DEBUG.print("Set Days:  %d\r\n", time.tm_mday);

//  DEBUG.print("Please Set Hours between 01 to 23\r\n");
//  while (time.tm_hour >23 ||time.tm_hour <1 )
//  {
//    time.tm_hour = 12;
//  }
//  DEBUG.print("Set Hours:  %d\r\n", time.tm_hour);

//  DEBUG.print("Please Set Minutes between 01 to 59\r\n");
//  while (time.tm_min >59 || time.tm_min <1 )
//  {
//    time.tm_min = 1;
//  }
//  DEBUG.print("Set Minutes:  %d\r\n", time.tm_min);

//  DEBUG.print("Please Set Seconds between 01 to 59\r\n");
//  while (time.tm_sec >59 || time.tm_sec <1 )
//  {
//    time.tm_sec = 1;
//  }
//  DEBUG.print("Set Seconds:  %d\r\n", time.tm_sec);
//  /* Return the value to store in RTC counter register */
//  Time_SetCalendarTime(time);
//}

void RTC_Init(void)
{

  if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
  {
    /* Backup data register value is not correct or not yet programmed (when
       the first time the program is executed) */

    DEBUG.print("RTC not yet configured....\r\n");

    /* RTC Configuration */
    RTC_Configuration();

	//Time_Regulate();

	/* Adjust time by values entred by the user on the hyperterminal */

    DEBUG.print("RTC configured....\r\n");

    BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
  }
  else
  {
    /* Check if the Power On Reset flag is set */
    if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
    {
      DEBUG.print("Power On Reset occurred....\r\n");
    }
    /* Check if the Pin Reset flag is set */
    else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
    {
      DEBUG.print("External Reset occurred....\r\n");
    }

    DEBUG.print("No need to configure RTC....\r\n");
    /* Wait for RTC registers synchronization */
    RTC_WaitForSynchro();
DEBUG.print("Synced RTC....\r\n");
    /* Enable the RTC Second */
    RTC_ITConfig(RTC_IT_SEC, ENABLE);
    /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();

  }

   /* NVIC configuration */
   NVIC_Configuration();

#ifdef RTCClockOutput_Enable
  /* Enable PWR and BKP clocks */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);

  /* Disable the Tamper Pin */
  BKP_TamperPinCmd(DISABLE); /* To output RTCCLK/64 on Tamper pin, the tamper
				 functionality must be disabled */

  /* Enable RTC Clock Output on Tamper Pin */
  BKP_RTCOutputConfig(BKP_RTCOutputSource_CalibClock);
#endif

   /* Clear reset flags */
  RCC_ClearFlag();
  DEBUG.print("Configured RTC!\r\n");
  return;
}


extern "C"
{
void RTC_IRQHandler(void)
{
	static uint8_t Display;
	if (RTC_GetITStatus(RTC_IT_SEC) != RESET)
	{
		/* Clear the RTC Second interrupt */
		RTC_ClearITPendingBit(RTC_IT_SEC);
	}
}
}
