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
#include "debug.h"
#include "sensHumidity.h"
#include "wg2dplot.h"
int main(void)
{
	CoThread::InitCoOS();

	Debug debugger;
	debugger.print("Welcome to RootControl!\r\n");

	BrainRoot brain;
	Display display;



	wgVerGauge gauge1(10, 10, 60, 220, 400, 100);
	wgVerGauge gauge2(250, 10, 60, 220, 1000, 0);
	gauge1.setScaleFactor(10,1);
	gauge2.setScaleFactor(10,1);
	gauge1.setUnit('C');
	gauge2.setUnit('%');

	wg2DPlot Plot(80,10,160,220,8);

	TouchSensor touchsensor(&display);
	touchsensor.calibrate();
	touchsensor.addListener(&brain);

	sensHumidityTemperature humidityTempSensor;
	humidityTempSensor.sensHumi.addListener(&brain);
	humidityTempSensor.sensTemp.addListener(&brain);
	humidityTempSensor.sensHumi.addListener(&gauge2);
	humidityTempSensor.sensTemp.addListener(&gauge1);

	Plot.addTrace(&humidityTempSensor.sensHumi,0,1000,COLOR_BLUE);
	Plot.addTrace(&humidityTempSensor.sensTemp,100,400,COLOR_RED);

	display.addWidget(&gauge1);
	display.addWidget(&gauge2);
	display.addWidget(&Plot);

	humidityTempSensor.start();
	touchsensor.start();
	brain.start();
	display.start();

	CoThread::StartCoOS();
	debugger.print("Major error! CoOS died!\r\n");
	while(1)
	{
	}
}

