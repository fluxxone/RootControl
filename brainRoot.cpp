#include "brainRoot.h"
#include "debug.h"
#include "emitter.h"
#include "sensor.h"
#include "sensClock.h"

#include <stdarg.h>
#include <stdio.h>

void BrainRoot::run()
{

	DEBUG.print("Brain thread started!\r\n");
	writeLog("Brain log starting\r\n");
	while(1)
	{
		Mbox::Message msg = MailBox->pendMail();
		int d = msg.data;
		if(msg.SenderPtr->getEmitterType() == EMITTER_TYPE_SENSOR)
		{
			struct tm t = sensClock::Time_ConvUnixToCalendar(SENSCLOCK.getTimeDateUnix());
			Sensor* sens = dynamic_cast<Sensor*>(msg.SenderPtr);
			switch(sens->getSensorID())
			{
			case SENSOR_ID_HUMIDITY:
				if(d > (_targetHumi + _humiHyst/2))
					humidityActuator.setValue(ACTHUMI_DEHUMIDIFY);
				else if(d < (_targetHumi - _humiHyst/2))
					humidityActuator.setValue(ACTHUMI_HUMIDIFY);
				else if ( d >= (_targetHumi - _humiHyst/4) && d <= (_targetHumi + _humiHyst/4))
					humidityActuator.setValue(ACTHUMI_TURN_OFF);
				writeLog("%d.%d.%d. %02d:%02d:%02d: ", t.tm_mday, \
						 t.tm_mon+1, t.tm_year,\
						 t.tm_hour, t.tm_min, t.tm_sec);
				writeLog("HUM=%d\r\n",d);
				break;
			case SENSOR_ID_TEMPERATURE:
				if(d > (_targetTemp + _tempHyst/2))
					temperatureActuator.setValue(ACTTEMP_COOL_ON);
				else if(d < (_targetTemp - _tempHyst/2))
					temperatureActuator.setValue(ACTTEMP_HEAT_ON);
				else if (d >= (_targetTemp - _tempHyst/4) && d <= (_targetTemp + _tempHyst/4))
					temperatureActuator.setValue(ACTTEMP_TURN_OFF);
				writeLog("%d.%d.%d. %02d:%02d:%02d: ", t.tm_mday, \
						 t.tm_mon+1, t.tm_year,\
						 t.tm_hour, t.tm_min, t.tm_sec);
				writeLog("TEMP=%d\r\n",d);
				break;
			case SENSOR_ID_CLOCK:
			{
				struct tm _time = sensClock::Time_ConvUnixToCalendar((time_t)msg.data);
				if ((_time.tm_hour*60 + _time.tm_min) >= (_hrOn*60 + _minOn) &&
					(_time.tm_hour*60 + _time.tm_min) < (_hrOff*60 + _minOff))
				{
					if (_LedFlag == false)
					{
						writeLog("%d.%d.%d. %02d:%02d:%02d: ", t.tm_mday, \
								 t.tm_mon+1, t.tm_year,\
								 t.tm_hour, t.tm_min, t.tm_sec);
						writeLog("LED ON\r\n");
						ledActuator.setValue(ACTLED_ON);
						_LedFlag = true;
					}
				}
				else
				{
					if (_LedFlag == true)
					{
						writeLog("%d.%d.%d. %02d:%02d:%02d: ", t.tm_mday, \
								 t.tm_mon+1, t.tm_year,\
								 t.tm_hour, t.tm_min, t.tm_sec);
						writeLog("LED OFF\r\n");
						ledActuator.setValue(ACTLED_OFF);
						_LedFlag = false;
					}
				}
			}
				break;
			default:
				DEBUG.print("Got something unknown %d\r\n",d);
			}

		}

	}
}
void BrainRoot::writeLog(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	vsnprintf(_logbuffer,sizeof(_logbuffer),format,args);

	va_end(args);

	_brainfile.Write(_logbuffer,strlen(_logbuffer));
	_brainfile.Sync();
}
