#include "brainRoot.h"
#include "debug.h"
#include "emitter.h"
#include "sensor.h"
void BrainRoot::run()
{
	DEBUG.print("Brain thread started!\r\n");
	uint32_t humiHyst = 10;
	uint32_t tempHyst = 4;
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
				if(d > (_targetHumi + humiHyst/2))
					humidityActuator.setValue(ACTHUMI_DEHUMIDIFY);
				else if(d < (_targetHumi - humiHyst/2))
					humidityActuator.setValue(ACTHUMI_HUMIDIFY);
				else
					humidityActuator.setValue(ACTHUMI_TURN_OFF);
				//DEBUG.print("Got humidity %d\r\n",d);
				break;
			case SENSOR_ID_TEMPERATURE:
				if(d > (_targetTemp + tempHyst/2))
					temperatureActuator.setValue(ACTTEMP_COOL_ON);
				else if(d < (_targetTemp - tempHyst/2))
					temperatureActuator.setValue(ACTTEMP_HEAT_ON);
				else
					temperatureActuator.setValue(ACTTEMP_TURN_OFF);
				//DEBUG.print("Got temperature %d\r\n",d);
				break;
			default:
				DEBUG.print("Got something %d\r\n",d);
			}
		}

	}
}

