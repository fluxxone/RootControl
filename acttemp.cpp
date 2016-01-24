#include "acttemp.h"

#include "acthumi.h"
#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#define GPIO_HEAT	GPIO_Pin_1
#define GPIO_COOL	GPIO_Pin_3

void actTemp::initGPIO()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOC , ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_HEAT | GPIO_COOL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	//GPIO_SetBits(GPIOE,GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_4 | GPIO_Pin_6);

}
void actTemp::heat(bool onOff)
{
	if (onOff)
	{
		GPIO_ResetBits(GPIOC, GPIO_COOL);
		GPIO_SetBits(GPIOC,GPIO_HEAT);
	}
	else
	{
		GPIO_ResetBits(GPIOC,GPIO_HEAT);
	}
}

void actTemp::cool(bool onOff)
{
	if (onOff)
	{
		GPIO_ResetBits(GPIOC, GPIO_HEAT);
		GPIO_SetBits(GPIOC,GPIO_COOL);
	}
	else
	{
		GPIO_ResetBits(GPIOC,GPIO_COOL);
	}
}

