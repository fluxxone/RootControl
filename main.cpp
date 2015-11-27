#include "widget.h"
#include "wgVerGauge.h"
#include "brainRoot.h"
#include "display.h"
#include "sensDummy.h"
#include "cothread.h"
#include "cothreadtest.h"
#include "CoOS.h"
#include "CoOS/OsConfig.h"
#include "touchsensor.h"

int main(void)
{
	CoThread::InitCoOS();
	BrainRoot brain;
	Display display;
	sensDummy dummySensor1(2);
	sensDummy dummySensor2(20);
	wgVerGauge gauge1(10, 10, 40, 220);
	wgVerGauge gauge2(270, 10, 40, 220);

	TouchSensor touchsensor(&display);
	touchsensor.calibrate();
	touchsensor.addListener(&brain);
	//touchsensor.calibrate();
	dummySensor1.addListener(&brain);
	//dummySensor1.addListener(&gauge1);

	dummySensor2.addListener(&brain);
	dummySensor2.addListener(&gauge2);

	display.addWidget(&gauge1);
	display.addWidget(&gauge2);

	dummySensor1.start();
	dummySensor2.start();
	touchsensor.start();
	brain.start();
	display.start();

	CoThread::StartCoOS();
    while(1)
    {
    }
}

