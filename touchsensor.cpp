#include "touchsensor.h"
#include "TouchPanel.h"
#include "EXTIset.h"
#include "stm32f10x_exti.h"
#include "listener.h"
#include "display.h"
#include "widget.h"
#include "debug.h"
#include "sensClock.h"
TouchSensor* TouchSensor::current = 0;
TouchSensor::TouchSensor(SENSOR_ID ID, Display* display):Sensor(ID),_display(display)
{
	TP_Init();
	//EXTI_Exp();
	current = this;
}
void TouchSensor::calibrate()
{
	DEBUG.print("TouchSensor calibration starting!\r\n");
	TouchPanel_Calibrate();
}

void TouchSensor::run()
{
	DEBUG.print("TouchSensor thread started!\r\n");
	Coordinate *co;
	while(1)
	{
		co = Read_Ads7846();
		if(co != 0)
		{
			//uint32_t data = (co->x << 16) | co->y;
			DEBUG.print("Touch!\r\n");
			uint16_t x = (co->x * DISPLAY_WIDTH)/4095-20;
			uint16_t y = (co->y * DISPLAY_HEIGHT)/4095;
			Widget* w = _display->getTargetWidget(x,y);
			if(w)
			{
				_value = w->getValueWhenClicked(x,y);
				w->update(this, &_value, DATA_TYPE_UINT32);
				for(int i = 0; i < _numListeners; i++)
				{
					_listeners[i]->update(this, &_value, DATA_TYPE_UINT32);
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
