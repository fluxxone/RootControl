/**
  ******************************************************************************
  * @file    EXTI/EXTI_Exp/main.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    30-October-2010
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_flash.h"
#include "misc.h"
#include "GLCD.h"
#include "TouchPanel.h"
#include "EXTIset.h"

#include <CoOS.h>

#define EXTI9_5_IRQChannel  ((u8)0x17)  // External Line[9:5] Interrupts 
#define LED_PORT GPIOB


//#include "debug.h"
//***************************************************************************
//
// Global variables
//
// **************************************************************************
GPIO_InitTypeDef GPIO_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;
ErrorStatus HSEStartUpStatus;

//***************************************************************************
//
// Declare function prototype
//
// **************************************************************************
void Delay(__IO uint32_t);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);


//***************************************************************************
//
//This example shows how to configure an external interrupt line.
//
// **************************************************************************
void EXTI_Exp(void)
{   
    //
    // System Clocks Configuration 
    //
    //RCC_Configuration();
    
    //
    // NVIC configuration 
    //
    NVIC_Configuration();

    //
    // Configure the GPIO ports 
    //
    //GPIO_Configuration();

    //
    // Connect EXTI Line9 to PC9 
    //
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource6);

    //
    // Configure EXTI Line9 to generate an interrupt on rising or falling edge
    // 
    EXTI_InitStructure.EXTI_Line = EXTI_Line6;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

//    while (1)
//    {
//    }
}

//***************************************************************************
//
//Configures the different system clocks.
//
// **************************************************************************
void RCC_Configuration(void)
{
    //  
    // RCC system reset(for debug purpose)
    // 
    RCC_DeInit();

    //
    // Enable HSE
    // 
    RCC_HSEConfig(RCC_HSE_ON);
    
    //
    // Wait till HSE is ready
    // 
    HSEStartUpStatus = RCC_WaitForHSEStartUp();

    if (HSEStartUpStatus == SUCCESS)
    {   
        //
        // HCLK = SYSCLK
        // 
        RCC_HCLKConfig(RCC_SYSCLK_Div1);

        //
        // PCLK2 = HCLK 
        //
        RCC_PCLK2Config(RCC_HCLK_Div1);

        //
        // PCLK1 = HCLK/2
        //
        RCC_PCLK1Config(RCC_HCLK_Div2);

        //
        // Flash 2 wait state 
        //
        FLASH_SetLatency(FLASH_Latency_2);
        
        //
        // Enable Prefetch Buffer
        // 
        FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

        //
        // PLLCLK = 8MHz * 9 = 72 MHz
        // 
        RCC_PLLConfig(0x00010000, RCC_PLLMul_9);

        //
        //Enable PLL
        // 
        RCC_PLLCmd(ENABLE);

        //
        //Wait till PLL is ready 
        //
        while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
        {
        }

        //
        // Select PLL as system clock source
        // 
        RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

        //
        // Wait till PLL is used as system clock source
        // 
        while (RCC_GetSYSCLKSource() != 0x08)
        {
        }
    }

    //
    // Enable GPIOB, GPIOC and AFIO clock 
    //
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC
            | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);
}

//***************************************************************************
//
//Configures the different GPIO ports.
//
//***************************************************************************
void GPIO_Configuration(void)
{
    //
    // Configure PC9 as input floating (EXTI Line9) 
    //
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

//***************************************************************************
//
//Configure the nested vectored interrupt controller.
//
//***************************************************************************
void NVIC_Configuration(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    //
    // Set the Vector Table base location at 0x08000000 
    //
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);

    //
    // Configure one bit for preemption priority 
    //
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

    //
    // Enable the EXTI9_5 Interrupt 
    //
    NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQChannel;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}

//**************************************************************************
//
//Inserts a delay time.
//
//**************************************************************************
void Delay(__IO uint32_t nCount)
{
    for (; nCount != 0; nCount--);
}

//**************************************************************************
//
//This function handles External lines 9 to 5 interrupt request.
//
//**************************************************************************

