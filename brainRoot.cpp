#include "brainRoot.h"
#include "debug.h"
#include "emitter.h"
#include "sensor.h"
#include "sensClock.h"

void BrainRoot::run()
{
	DEBUG.print("Brain thread started!\r\n");
	while(1)
	{
		Mbox::Message msg = MailBox->pendMail();
		int d = msg.data;
		if(msg.SenderPtr->getEmitterType() == EMITTER_TYPE_SENSOR)
		{
			Sensor* sens = dynamic_cast<Sensor*>(msg.SenderPtr);
			switch(sens->getSensorID())
			{
			case SENSOR_ID_HUMIDITY:
				if(d > (_targetHumi + _humiHyst/2))
					humidityActuator.setValue(ACTHUMI_DEHUMIDIFY);
				else if(d < (_targetHumi - _humiHyst/2))
					humidityActuator.setValue(ACTHUMI_HUMIDIFY);
				else
					humidityActuator.setValue(ACTHUMI_TURN_OFF);
				//DEBUG.print("Got humidity %d\r\n",d);
				break;
			case SENSOR_ID_TEMPERATURE:
				if(d > (_targetTemp + _tempHyst/2))
					temperatureActuator.setValue(ACTTEMP_COOL_ON);
				else if(d < (_targetTemp - _tempHyst/2))
					temperatureActuator.setValue(ACTTEMP_HEAT_ON);
				else
					temperatureActuator.setValue(ACTTEMP_TURN_OFF);
				//DEBUG.print("Got temperature %d\r\n",d);
				break;
			case SENSOR_ID_CLOCK:
			{
				struct tm t = sensClock::Time_ConvUnixToCalendar((time_t)msg.data);
				DEBUG.print("hr=%d, min=%d\r\n",t.tm_hour,t.tm_min);
				if ((t.tm_hour*60 + t.tm_min) >= (_hrOn*60 + _minOn) &&
					(t.tm_hour*60 + t.tm_min) < (_hrOff*60 + _minOff))
				{
					DEBUG.print("LED ON\r\n");
					ledActuator.setValue(ACTLED_ON);
				}
				else
				{
					DEBUG.print("LED OFF\r\n");
					ledActuator.setValue(ACTLED_OFF);
				}
			}
				break;
			default:
				DEBUG.print("Got something unknown %d\r\n",d);
			}

		}

	}
}

