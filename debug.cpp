#include "debug.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_usart.h"
#include "misc.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

void USART_init(void){

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_1);
//	GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_1);

	GPIO_InitTypeDef GPIO_InitStructure;

	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART1 Rx (PA.10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	USART_InitTypeDef USART_InitStructure;
	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	USART_Cmd(USART1,ENABLE);
}


void USART_print(char* StringPtr)
{
	uint16_t ulCount = 0xFFFF;
	while(ulCount-- && *StringPtr)
	{
		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
		{
		}
		USART_SendData(USART1, *StringPtr);// Last Version USART_SendData(USART1,(uint16_t) *pucBuffer++);
		StringPtr++;
	}
}


Debug::Debug()
{
	USART_init();
	if(!_logfile.Open("0:/DBGLOG.TXT"))
		print("ERROR: LOG file not opened!\r\n");
	else
		print("LOG file successfully opened\r\n");

}

Debug& Debug::getInstance()
{
	static Debug instance;
	return instance;
}

void Debug::print(const char* format, ...)
{
	va_list args;
	va_start(args, format);

	vsnprintf(_buffer,sizeof(_buffer),format,args);

	va_end(args);

	USART_print(_buffer);
	_logfile.Write(_buffer,strlen(_buffer));
	_logfile.Sync();
}

