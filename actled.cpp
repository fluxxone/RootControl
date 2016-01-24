#include "actled.h"

#include <stm32f10x_gpio.h>
#include <stm32f10x_rcc.h>

#define GPIO_LED	GPIO_Pin_1
#define PORT_LED	GPIOA
#define PERIF_LED	RCC_APB2Periph_GPIOA

void actLed::initGPIO()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_APB2PeriphClockCmd( PERIF_LED , ENABLE);

	GPIO_InitStructure.GPIO_Pin = GPIO_LED;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init(PORT_LED, &GPIO_InitStructure);

}
void actLed::LED(bool onOff)
{
	if (onOff)
	{
		GPIO_SetBits(PORT_LED,GPIO_LED);
	}
	else
	{
		GPIO_ResetBits(PORT_LED,GPIO_LED);
	}
}

