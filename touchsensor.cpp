#include "touchsensor.h"
#include "TouchPanel.h"
#include "EXTIset.h"
#include "stm32f10x_exti.h"
#include "listener.h"
#include "display.h"
#include "widget.h"
TouchSensor* TouchSensor::current = 0;
TouchSensor::TouchSensor(Display* arg):disp(arg)
{
	TP_Init();
	//EXTI_Exp();
	current = this;
}
void TouchSensor::calibrate()
{
	TouchPanel_Calibrate();
}

void TouchSensor::run()
{
	Coordinate *co;
	while(1)
	{
		co = Read_Ads7846();
		if(co != 0)
		{
			//uint32_t data = (co->x << 16) | co->y;
			uint16_t x = (co->x * DISPLAY_WIDTH)/4095-20;
			uint16_t y = (co->y * DISPLAY_HEIGHT)/4095;
			Widget* w = disp->getTargetWidget(x,y);
			if(w)
			{
				uint8_t val = w->getValueWhenClicked(x,y);
				w->update(this,val);
				for(int i = 0; i < numListeners; i++)
				{
					listeners[i]->update(this, val);
				}
			}

		}
		CoTimeDelay(0,0,0,100);
	}
}
Coordinate *co = 0;
void TouchSensor::tpinterrupt()
{
	Mbox::Message msg;
	msg.SenderPtr = current;
	msg.data = (co->x << 16) | co->y;
	current->MailBox->sendMail(msg, true);
}

void (*tpintp)()=TouchSensor::tpinterrupt;

extern "C"
{
	void EXTI9_5_IRQHandler(void)
	{
		if (EXTI_GetITStatus(EXTI_Line6) != RESET)
		{
			//Here, handle the interrupt
//			uint32_t cnt = 0;
//			do
//			{
//				co = Read_Ads7846();
//				cnt++;
//			}
//			while( (co == (void*)0) && (cnt < 65535*100) );
////			if(cnt < 65535*100)
////				(*tpintp)();
			EXTI_ClearITPendingBit(EXTI_Line6);
		}
	}
}
