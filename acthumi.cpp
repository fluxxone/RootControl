#include "acthumi.h"
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#define GPIO_HUMIDIFY	GPIO_Pin_4
#define GPIO_DEHUMIDIFY	GPIO_Pin_6

void actHumi::initGPIO()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE , ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_HUMIDIFY | GPIO_DEHUMIDIFY;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	//GPIO_SetBits(GPIOE,GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_6);

}
void actHumi::humidify(bool onOff)
{
	if (onOff)
	{
		GPIO_ResetBits(GPIOE, GPIO_DEHUMIDIFY);
		GPIO_SetBits(GPIOE,GPIO_HUMIDIFY);
	}
	else
	{
		GPIO_ResetBits(GPIOE,GPIO_HUMIDIFY);
	}
}

void actHumi::dehumidify(bool onOff)
{
	if (onOff)
	{
		GPIO_ResetBits(GPIOE, GPIO_HUMIDIFY);
		GPIO_SetBits(GPIOE,GPIO_DEHUMIDIFY);
	}
	else
	{
		GPIO_ResetBits(GPIOE,GPIO_DEHUMIDIFY);
	}
}
