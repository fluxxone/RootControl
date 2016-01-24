#include "widget.h"
#include "wgVerGauge.h"
#include "brainRoot.h"
#include "screen.h"
#include "sensDummy.h"
#include "cothread.h"
#include "cothreadtest.h"
#include "CoOS.h"
#include "OsConfig.h"
#include "touchsensor.h"
#include "debug.h"
#include "sensHumidity.h"
#include "sensClock.h"
#include "wg2dplot.h"
#include "display.h"
#include "wgnavscreens.h"
#include "wglabel.h"
#include "wgindicator.h"
#include "sdfile.h"

#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

int main(void)
{

//	GPIO_InitTypeDef GPIO_InitStructure;


//	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE , ENABLE);

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_6;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOE, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOE,GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_6);

//	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE);

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_3;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOC, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOC,GPIO_Pin_1 | GPIO_Pin_3);

//	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA , ENABLE);

//	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
//	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//	GPIO_Init(GPIOA, &GPIO_InitStructure);
//	GPIO_SetBits(GPIOA,GPIO_Pin_1);

//	while(1)
//	;

	CoThread::InitCoOS();
	//sensClock clock(SENSOR_ID_CLOCK);
	DEBUG.print("Welcome to RootControl!\r\n");
//	SDFile testFile("0:/MIRKO.TXT");
//	DEBUG.print("File size = %d, content:\r\n",testFile.Size());
//	char buff[5];
//	buff[4] = 0;
//	testFile.Read(buff,4);
//	DEBUG.print(buff);
//	testFile.Read(buff,4);
//	DEBUG.print(buff);
//	testFile.Read(buff,4);
//	DEBUG.print(buff);

//	testFile.Write("Leba ti jebem!\r\n12345\r\n",sizeof("Leba ti jebem!\r\n12345\r\n")-1);
//	testFile.Close();
//	DEBUG.print("Finished writing the file!\r\n");
	Display display;
	BrainRoot brain;
	Screen mainScreen;
	Screen settingsScreen;


	DEBUG.print("Adding screens!\r\n");
	display.addScreen(&mainScreen);
	display.addScreen(&settingsScreen);
	DEBUG.print("Making widgets!\r\n");
	wgVerGauge gauge1(10, 10, 60, 180, 400, 100);
	wgVerGauge gauge2(250, 10, 60, 180, 1000, 0);
	gauge1.setScaleFactor(10,1);
	gauge2.setScaleFactor(10,1);
	gauge1.setUnit('C');
	gauge2.setUnit('%');

	wg2DPlot Plot(80,10,180,160,&SENSCLOCK,8);
	wgNavScreens wgNext(WGNAVSCREENS_TYPE_MOVE_PREV,20,200,30,30);
	wgNavScreens wgPrev(WGNAVSCREENS_TYPE_MOVE_NEXT,270,200,30,30);
	wgLabel wgClockLabel(80,200,30,160);
	wgIndicator wgCoolHeat(80,200,30,30);
	wgIndicator wgHumi(120,200,30,30);
	wgIndicator wgLed(160,200,30,30);

	DEBUG.print("Calibrating touch sensor!\r\n");
	TouchSensor touchsensor(SENSOR_ID_DISPLAY, &display);
	//touchsensor.calibrate();
	touchsensor.addListener(&brain);

	DEBUG.print("Adding clock listeners!\r\n");
	SENSCLOCK.addListener(&wgClockLabel);
	SENSCLOCK.addListener(&brain);

	DEBUG.print("Initializing humidity sensor!\r\n");
	sensHumidityTemperature humidityTempSensor;
	humidityTempSensor.sensHumi.addListener(&brain);
	humidityTempSensor.sensTemp.addListener(&brain);
	humidityTempSensor.sensHumi.addListener(&gauge2);
	humidityTempSensor.sensTemp.addListener(&gauge1);

	Plot.addTrace(&humidityTempSensor.sensHumi,0,1000,COLOR_BLUE);
	Plot.addTrace(&humidityTempSensor.sensTemp,100,400,COLOR_RED);
	Plot.addTrace(&brain.refTemp,100,400,COLOR_GREEN);
	Plot.addTrace(&brain.refHumi,0,1000,COLOR_BLUE|COLOR_GREEN);
	brain.humidityActuator.status.addListener(&wgHumi);
	brain.temperatureActuator.status.addListener(&wgCoolHeat);
	brain.ledActuator.status.addListener(&wgLed);
	DEBUG.print("Adding widgets to screens!\r\n");
	mainScreen.addWidget(&gauge1);
	mainScreen.addWidget(&gauge2);
	mainScreen.addWidget(&Plot);
	mainScreen.addWidget(&wgNext);
	mainScreen.addWidget(&wgPrev);
	mainScreen.addWidget(&wgCoolHeat);
	mainScreen.addWidget(&wgHumi);
	mainScreen.addWidget(&wgLed);
	settingsScreen.addWidget(&wgClockLabel);
	settingsScreen.addWidget(&wgNext);
	settingsScreen.addWidget(&wgPrev);
	DEBUG.print("Starting threads!\r\n");
	humidityTempSensor.start();
	touchsensor.start();
	brain.start();
	display.start();
	SENSCLOCK.start();

	CoThread::StartCoOS();
	DEBUG.print("Major error! CoOS died!\r\n");
	while(1)
	{
	}
}

