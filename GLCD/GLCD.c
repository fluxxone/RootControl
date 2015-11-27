
/* Includes ------------------------------------------------------------------*/
#include "GLCD.h" 
#include "HzLib.h"
#include "AsciiLib.h"
#include <math.h>
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_fsmc.h"
#include "stm32f10x_tim.h"
//#include "TouchPanel.h"
//#include "flappymimi.h"
//#include "cev.h"
//#include "defs.h"
//#include "brojevi.h"
/* Private variables ---------------------------------------------------------*/
static uint16_t DeviceCode;
static uint16_t TimerPeriod = 0;
static uint16_t Channel2Pulse = 1000;
uint8_t PMode=1;
uint8_t PSize=1;
uint8_t activeSeg=0;
/* Private define ------------------------------------------------------------*/
#define LCD_REG              (*((volatile unsigned short *) 0x60000000)) /* RS = 0 */
#define LCD_RAM              (*((volatile unsigned short *) 0x60020000)) /* RS = 1 */
																				
/*******************************************************************************
* Function Name  : LCD_FormatSet
*******************************************************************************/
void LCD_FormatSet(uint8_t dato) 
{
	PMode=dato;	 /*Pmode=1 Portrait, Pmode=0 Landscape */ 
}

/*******************************************************************************
* Function Name  : LCD_FormatRead
*******************************************************************************/
uint8_t LCD_FormatRead(void)
{
	uint8_t value;
	value=PMode;
	return(value);
}

/*******************************************************************************
* Function Name  : LCD_PSizeSet
*******************************************************************************/
void LCD_PSizeSet(uint8_t dato) 
{
	PSize=dato;
}

/*******************************************************************************
* Function Name  : LCD_PSizeRead
*******************************************************************************/
uint8_t LCD_PSizeRead(void)
{
	uint8_t value;
	value=PSize;
	return(value);
}

/*******************************************************************************
* Function Name  : LCD_CtrlLinesConfig
*******************************************************************************/
static void LCD_CtrlLinesConfig(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC, ENABLE);
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 |
                                 GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | 
                                 GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOE, &GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 | 
                                 GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | 
                                 GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_Init(GPIOD, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : LCD_FSMCConfig
*******************************************************************************/
static void LCD_FSMCConfig(void)
{
  FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
  FSMC_NORSRAMTimingInitTypeDef FSMC_NORSRAMTimingInitStructure;
  FSMC_NORSRAMTimingInitStructure.FSMC_AddressSetupTime = 30;
  FSMC_NORSRAMTimingInitStructure.FSMC_AddressHoldTime = 0;	   
  FSMC_NORSRAMTimingInitStructure.FSMC_DataSetupTime = 30;
  FSMC_NORSRAMTimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
  FSMC_NORSRAMTimingInitStructure.FSMC_CLKDivision = 0x00;
  FSMC_NORSRAMTimingInitStructure.FSMC_DataLatency = 0x00;
  FSMC_NORSRAMTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_A;
  FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM1;
  FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable;
  FSMC_NORSRAMInitStructure.FSMC_MemoryType = FSMC_MemoryType_SRAM;
  FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;
  FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode = FSMC_BurstAccessMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
  FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;
  FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;
  FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;
  FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait = FSMC_AsynchronousWait_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Disable;
  FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable;
  FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;
  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
  FSMC_NORSRAMTimingInitStructure.FSMC_AddressSetupTime = 2;
  FSMC_NORSRAMTimingInitStructure.FSMC_AddressHoldTime = 0;	   
  FSMC_NORSRAMTimingInitStructure.FSMC_DataSetupTime = 2;
  FSMC_NORSRAMTimingInitStructure.FSMC_BusTurnAroundDuration = 0x00;
  FSMC_NORSRAMTimingInitStructure.FSMC_CLKDivision = 0x00;
  FSMC_NORSRAMTimingInitStructure.FSMC_DataLatency = 0x00;
  FSMC_NORSRAMTimingInitStructure.FSMC_AccessMode = FSMC_AccessMode_A;
  FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &FSMC_NORSRAMTimingInitStructure;	  
  FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure); 
  FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM1, ENABLE);  
}

/*******************************************************************************
* Function Name  : LCD_Configuration
*******************************************************************************/
static void LCD_Configuration(void)
{
  LCD_CtrlLinesConfig();
  LCD_FSMCConfig();
}

/*******************************************************************************
* Function Name  : LCD_WriteReg
*******************************************************************************/
void LCD_WriteReg(uint8_t LCD_Reg,uint16_t LCD_RegValue)
{
  LCD_REG = LCD_Reg;
  LCD_RAM = LCD_RegValue;
}

/*******************************************************************************
* Function Name  : LCD_ReadReg
*******************************************************************************/
uint16_t LCD_ReadReg(uint8_t LCD_Reg)
{
  LCD_REG = LCD_Reg;
  return (LCD_RAM);
}

/*******************************************************************************
* Function Name  : LCD_WriteRAM_Prepare
*******************************************************************************/
__inline void LCD_WriteRAM_Prepare(void)
{
  LCD_REG = R34;
}

/*******************************************************************************
* Function Name  : LCD_WriteRAM
*******************************************************************************/
__inline void LCD_WriteRAM(uint16_t RGB_Code)
{
  LCD_RAM = RGB_Code;
}

/*******************************************************************************
* Function Name  : LCD_ReadRAM
*******************************************************************************/
static __inline uint16_t LCD_ReadRAM(void)
{
  volatile uint16_t dummy; 
  LCD_REG = R34;
  dummy = LCD_RAM;
  return LCD_RAM;
}

/*******************************************************************************
* Function Name  : LCD_Delay
*******************************************************************************/
static void LCD_Delay(uint16_t nCount)
{
 uint16_t TimingDelay; 
 while(nCount--)
   {
    for(TimingDelay=0;TimingDelay<10000;TimingDelay++);
   }
}

/*******************************************************************************
* Function Name  : LCD_Initializtion
*******************************************************************************/
void LCD_Initializtion()
{
  LCD_Configuration();
  LCD_Delay(5);
  DeviceCode = LCD_ReadReg(0x0000);		
  if(DeviceCode==0x9325 || DeviceCode==0x9328)	
   {
    LCD_WriteReg(0x00e7,0x0010);      
    LCD_WriteReg(0x0000,0x0001);
    LCD_WriteReg(0x0001,0x0100);     
    LCD_WriteReg(0x0002,0x0700);
	LCD_WriteReg(0x0003,(1<<12)|(1<<5)|(1<<4)|(0<<3) );
    LCD_WriteReg(0x0004,0x0000);                                   
    LCD_WriteReg(0x0008,0x0207);	           
    LCD_WriteReg(0x0009,0x0000);         
    LCD_WriteReg(0x000a,0x0000);
    LCD_WriteReg(0x000c,0x0001);
    LCD_WriteReg(0x000d,0x0000); 			        
    LCD_WriteReg(0x000f,0x0000);
    LCD_WriteReg(0x0010,0x0000);   
    LCD_WriteReg(0x0011,0x0007);
    LCD_WriteReg(0x0012,0x0000);                                                                 
    LCD_WriteReg(0x0013,0x0000);                 
    LCD_Delay(5);
    LCD_WriteReg(0x0010,0x1590);   
    LCD_WriteReg(0x0011,0x0227);
    LCD_Delay(5);
    LCD_WriteReg(0x0012,0x009c);                  
    LCD_Delay(5);
    LCD_WriteReg(0x0013,0x1900);   
    LCD_WriteReg(0x0029,0x0023);
    LCD_WriteReg(0x002b,0x000e);
    LCD_Delay(5);
    LCD_WriteReg(0x0020,0x0000);                                                            
    LCD_WriteReg(0x0021,0x0000);           
    LCD_Delay(5);
    LCD_WriteReg(0x0030,0x0007); 
    LCD_WriteReg(0x0031,0x0707);   
    LCD_WriteReg(0x0032,0x0006);
    LCD_WriteReg(0x0035,0x0704);
    LCD_WriteReg(0x0036,0x1f04); 
    LCD_WriteReg(0x0037,0x0004);
    LCD_WriteReg(0x0038,0x0000);        
    LCD_WriteReg(0x0039,0x0706);     
    LCD_WriteReg(0x003c,0x0701);
    LCD_WriteReg(0x003d,0x000f);
    LCD_Delay(5);
    LCD_WriteReg(0x0050,0x0000);        
    LCD_WriteReg(0x0051,0x00ef);   
    LCD_WriteReg(0x0052,0x0000);     
    LCD_WriteReg(0x0053,0x013f);
    LCD_WriteReg(0x0060,0xa700);        
    LCD_WriteReg(0x0061,0x0001); 
    LCD_WriteReg(0x006a,0x0000);
    LCD_WriteReg(0x0080,0x0000);
    LCD_WriteReg(0x0081,0x0000);
    LCD_WriteReg(0x0082,0x0000);
    LCD_WriteReg(0x0083,0x0000);
    LCD_WriteReg(0x0084,0x0000);
    LCD_WriteReg(0x0085,0x0000);
    LCD_WriteReg(0x0090,0x0010);     
    LCD_WriteReg(0x0092,0x0000);  
    LCD_WriteReg(0x0093,0x0003);
    LCD_WriteReg(0x0095,0x0110);
    LCD_WriteReg(0x0097,0x0000);        
    LCD_WriteReg(0x0098,0x0000);
    LCD_WriteReg(0x0007,0x0133);
    LCD_WriteReg(0x0020,0x0000);                                                           
    LCD_WriteReg(0x0021,0x0000);       
  }

  else if(DeviceCode==0x9320 || DeviceCode==0x9300)	
  {
    LCD_WriteReg(0x00,0x0000);
	LCD_WriteReg(0x01,0x0100);
	LCD_WriteReg(0x02,0x0700);
	LCD_WriteReg(0x03,0x1030);
	LCD_WriteReg(0x04,0x0000);
	LCD_WriteReg(0x08,0x0202);
	LCD_WriteReg(0x09,0x0000);
	LCD_WriteReg(0x0a,0x0000);
	LCD_WriteReg(0x0c,(1<<0));
	LCD_WriteReg(0x0d,0x0000);
	LCD_WriteReg(0x0f,0x0000);
    LCD_Delay(10);
	LCD_WriteReg(0x07,0x0101);
    LCD_Delay(10);
	LCD_WriteReg(0x10,(1<<12)|(0<<8)|(1<<7)|(1<<6)|(0<<4));
	LCD_WriteReg(0x11,0x0007);
	LCD_WriteReg(0x12,(1<<8)|(1<<4)|(0<<0));
	LCD_WriteReg(0x13,0x0b00);
	LCD_WriteReg(0x29,0x0000);
	LCD_WriteReg(0x2b,(1<<14)|(1<<4));
	LCD_WriteReg(0x50,0);
	LCD_WriteReg(0x51,239);
	LCD_WriteReg(0x52,0);
	LCD_WriteReg(0x53,319);
	LCD_WriteReg(0x60,0x2700);
	LCD_WriteReg(0x61,0x0001);
	LCD_WriteReg(0x6a,0x0000);
	LCD_WriteReg(0x80,0x0000);
	LCD_WriteReg(0x81,0x0000);
	LCD_WriteReg(0x82,0x0000);
	LCD_WriteReg(0x83,0x0000);
	LCD_WriteReg(0x84,0x0000);
	LCD_WriteReg(0x85,0x0000);
    LCD_WriteReg(0x90,(0<<7)|(16<<0));
	LCD_WriteReg(0x92,0x0000);
	LCD_WriteReg(0x93,0x0001);
    LCD_WriteReg(0x95,0x0110);
	LCD_WriteReg(0x97,(0<<8));	
	LCD_WriteReg(0x98,0x0000);
    LCD_WriteReg(0x07,0x0173);
  }
  else if(DeviceCode==0x9331)
  {
	LCD_WriteReg(0x00E7, 0x1014);
	LCD_WriteReg(0x0001, 0x0100);
	LCD_WriteReg(0x0002, 0x0200);
	LCD_WriteReg(0x0003, 0x1030);
	LCD_WriteReg(0x0008, 0x0202);
    LCD_WriteReg(0x0009, 0x0000);
	LCD_WriteReg(0x000A, 0x0000);
	LCD_WriteReg(0x000C, 0x0000);
	LCD_WriteReg(0x000D, 0x0000);
	LCD_WriteReg(0x000F, 0x0000);
	LCD_WriteReg(0x0010, 0x0000);
	LCD_WriteReg(0x0011, 0x0007);
	LCD_WriteReg(0x0012, 0x0000);
	LCD_WriteReg(0x0013, 0x0000);
    LCD_Delay(20);
	LCD_WriteReg(0x0010, 0x1690);
	LCD_WriteReg(0x0011, 0x0227);
    LCD_Delay(5);
	LCD_WriteReg(0x0012, 0x000C);
    LCD_Delay(5);
	LCD_WriteReg(0x0013, 0x0800);
	LCD_WriteReg(0x0029, 0x0011);
	LCD_WriteReg(0x002B, 0x000B);
    LCD_Delay(5);
	LCD_WriteReg(0x0020, 0x0000);
	LCD_WriteReg(0x0021, 0x0000);
	LCD_WriteReg(0x0030, 0x0000);
	LCD_WriteReg(0x0031, 0x0106);
	LCD_WriteReg(0x0032, 0x0000);
	LCD_WriteReg(0x0035, 0x0204);
	LCD_WriteReg(0x0036, 0x160A);
	LCD_WriteReg(0x0037, 0x0707);
	LCD_WriteReg(0x0038, 0x0106);
	LCD_WriteReg(0x0039, 0x0707);
	LCD_WriteReg(0x003C, 0x0402);
	LCD_WriteReg(0x003D, 0x0C0F);
	LCD_WriteReg(0x0050, 0x0000);
	LCD_WriteReg(0x0051, 0x00EF);
	LCD_WriteReg(0x0052, 0x0000);
	LCD_WriteReg(0x0053, 0x013F);
	LCD_WriteReg(0x0060, 0x2700);
	LCD_WriteReg(0x0061, 0x0001);
	LCD_WriteReg(0x006A, 0x0000);
	LCD_WriteReg(0x0080, 0x0000);
	LCD_WriteReg(0x0081, 0x0000);
	LCD_WriteReg(0x0082, 0x0000);
	LCD_WriteReg(0x0083, 0x0000);
	LCD_WriteReg(0x0084, 0x0000);
	LCD_WriteReg(0x0085, 0x0000);
	LCD_WriteReg(0x0090, 0x0010);
	LCD_WriteReg(0x0092, 0x0600);
	LCD_WriteReg(0x0007,0x0021);		
    LCD_Delay(5);
	LCD_WriteReg(0x0007,0x0061);
    LCD_Delay(5);
	LCD_WriteReg(0x0007,0x0133);
    LCD_Delay(5);
  }
  else if(DeviceCode==0x9919)
  {
	LCD_WriteReg(0x28,0x0006);
	LCD_WriteReg(0x00,0x0001);		
	LCD_WriteReg(0x10,0x0000);		
	LCD_WriteReg(0x01,0x72ef);
	LCD_WriteReg(0x02,0x0600);
	LCD_WriteReg(0x03,0x6a38);	
	LCD_WriteReg(0x11,0x6874);
	LCD_WriteReg(0x0f,0x0000);
	LCD_WriteReg(0x0b,0x5308);
	LCD_WriteReg(0x0c,0x0003);
	LCD_WriteReg(0x0d,0x000a);
	LCD_WriteReg(0x0e,0x2e00);  
	LCD_WriteReg(0x1e,0x00be);
	LCD_WriteReg(0x25,0x8000);
	LCD_WriteReg(0x26,0x7800);
	LCD_WriteReg(0x27,0x0078);
	LCD_WriteReg(0x4e,0x0000);
	LCD_WriteReg(0x4f,0x0000);
	LCD_WriteReg(0x12,0x08d9);
	LCD_WriteReg(0x30,0x0000);
	LCD_WriteReg(0x31,0x0104);	 
	LCD_WriteReg(0x32,0x0100);	
    LCD_WriteReg(0x33,0x0305);	
    LCD_WriteReg(0x34,0x0505);	 
	LCD_WriteReg(0x35,0x0305);	
    LCD_WriteReg(0x36,0x0707);	
    LCD_WriteReg(0x37,0x0300);	
	LCD_WriteReg(0x3a,0x1200);	
	LCD_WriteReg(0x3b,0x0800);		 
    LCD_WriteReg(0x07,0x0033);
  }
  else if(DeviceCode==0x1505)
  {
    LCD_WriteReg(0x0007,0x0000);
    LCD_Delay(5);
    LCD_WriteReg(0x0012,0x011C);
    LCD_WriteReg(0x00A4,0x0001);
    LCD_WriteReg(0x0008,0x000F);
    LCD_WriteReg(0x000A,0x0008);
    LCD_WriteReg(0x000D,0x0008);    
    LCD_WriteReg(0x0030,0x0707);
    LCD_WriteReg(0x0031,0x0007); 
    LCD_WriteReg(0x0032,0x0603); 
    LCD_WriteReg(0x0033,0x0700); 
    LCD_WriteReg(0x0034,0x0202); 
    LCD_WriteReg(0x0035,0x0002); 
    LCD_WriteReg(0x0036,0x1F0F);
    LCD_WriteReg(0x0037,0x0707); 
    LCD_WriteReg(0x0038,0x0000); 
    LCD_WriteReg(0x0039,0x0000); 
    LCD_WriteReg(0x003A,0x0707); 
    LCD_WriteReg(0x003B,0x0000); 
    LCD_WriteReg(0x003C,0x0007); 
    LCD_WriteReg(0x003D,0x0000); 
    LCD_Delay(5);
    LCD_WriteReg(0x0007,0x0001);
    LCD_WriteReg(0x0017,0x0001);
    LCD_Delay(5);
    LCD_WriteReg(0x0010,0x17A0); 
    LCD_WriteReg(0x0011,0x0217);
    LCD_WriteReg(0x0012,0x011E);
    LCD_WriteReg(0x0013,0x0F00);
    LCD_WriteReg(0x002A,0x0000);  
    LCD_WriteReg(0x0029,0x000A);
    LCD_WriteReg(0x0012,0x013E);
    LCD_WriteReg(0x0050,0x0000);
    LCD_WriteReg(0x0051,0x00EF); 
    LCD_WriteReg(0x0052,0x0000); 
    LCD_WriteReg(0x0053,0x013F); 
    LCD_WriteReg(0x0060,0x2700); 
    LCD_WriteReg(0x0061,0x0001); 
    LCD_WriteReg(0x006A,0x0000); 
    LCD_WriteReg(0x0080,0x0000); 
    LCD_WriteReg(0x0081,0x0000); 
    LCD_WriteReg(0x0082,0x0000); 
    LCD_WriteReg(0x0083,0x0000); 
    LCD_WriteReg(0x0084,0x0000); 
    LCD_WriteReg(0x0085,0x0000); 
    LCD_WriteReg(0x0090,0x0013);
    LCD_WriteReg(0x0092,0x0300); 
    LCD_WriteReg(0x0093,0x0005); 
    LCD_WriteReg(0x0095,0x0000); 
    LCD_WriteReg(0x0097,0x0000); 
    LCD_WriteReg(0x0098,0x0000);
    LCD_WriteReg(0x0001,0x0100); 
    LCD_WriteReg(0x0002,0x0700); 
    LCD_WriteReg(0x0003,0x1018); //direction of drawing
    LCD_WriteReg(0x0004,0x0000); 
    LCD_WriteReg(0x000C,0x0000); 
    LCD_WriteReg(0x000F,0x0000); 
    LCD_WriteReg(0x0020,0x0000); 
    LCD_WriteReg(0x0021,0x0000); 
    LCD_WriteReg(0x0007,0x0021); 
    LCD_Delay(20);
    LCD_WriteReg(0x0007,0x0061); 
    LCD_Delay(20);
    LCD_WriteReg(0x0007,0x0173); 
    LCD_Delay(20);
  }							 
  else if(DeviceCode==0x8989)
  {
    LCD_WriteReg(0x0000,0x0001);    LCD_Delay(5);   
    LCD_WriteReg(0x0003,0xA8A4);    LCD_Delay(5);   
    LCD_WriteReg(0x000C,0x0000);    LCD_Delay(5);   
    LCD_WriteReg(0x000D,0x080C);    LCD_Delay(5);   
    LCD_WriteReg(0x000E,0x2B00);    LCD_Delay(5);   
    LCD_WriteReg(0x001E,0x00B0);    LCD_Delay(5);   
    LCD_WriteReg(0x0001,0x2B3F);    LCD_Delay(5);
    LCD_WriteReg(0x0002,0x0600);    LCD_Delay(5);
    LCD_WriteReg(0x0010,0x0000);    LCD_Delay(5);
	LCD_WriteReg(0x0011,0x6070);    LCD_Delay(5);
	LCD_WriteReg(0x0005,0x0000);    LCD_Delay(5);
    LCD_WriteReg(0x0006,0x0000);    LCD_Delay(5);
    LCD_WriteReg(0x0016,0xEF1C);    LCD_Delay(5);
    LCD_WriteReg(0x0017,0x0003);    LCD_Delay(5);
    LCD_WriteReg(0x0007,0x0133);    LCD_Delay(5);         
    LCD_WriteReg(0x000B,0x0000);    LCD_Delay(5);
    LCD_WriteReg(0x000F,0x0000);    LCD_Delay(5);   
    LCD_WriteReg(0x0041,0x0000);    LCD_Delay(5);
    LCD_WriteReg(0x0042,0x0000);    LCD_Delay(5);
    LCD_WriteReg(0x0048,0x0000);    LCD_Delay(5);
    LCD_WriteReg(0x0049,0x013F);    LCD_Delay(5);
    LCD_WriteReg(0x004A,0x0000);    LCD_Delay(5);
    LCD_WriteReg(0x004B,0x0000);    LCD_Delay(5);
    LCD_WriteReg(0x0044,0xEF00);    LCD_Delay(5);
    LCD_WriteReg(0x0045,0x0000);    LCD_Delay(5);
    LCD_WriteReg(0x0046,0x013F);    LCD_Delay(5);
    LCD_WriteReg(0x0030,0x0707);    LCD_Delay(5);
    LCD_WriteReg(0x0031,0x0204);    LCD_Delay(5);
    LCD_WriteReg(0x0032,0x0204);    LCD_Delay(5);
    LCD_WriteReg(0x0033,0x0502);    LCD_Delay(5);
    LCD_WriteReg(0x0034,0x0507);    LCD_Delay(5);
    LCD_WriteReg(0x0035,0x0204);    LCD_Delay(5);
    LCD_WriteReg(0x0036,0x0204);    LCD_Delay(5);
    LCD_WriteReg(0x0037,0x0502);    LCD_Delay(5);
    LCD_WriteReg(0x003A,0x0302);    LCD_Delay(5);
    LCD_WriteReg(0x003B,0x0302);    LCD_Delay(5);
    LCD_WriteReg(0x0023,0x0000);    LCD_Delay(5);
    LCD_WriteReg(0x0024,0x0000);    LCD_Delay(5);
    LCD_WriteReg(0x0025,0x8000);    LCD_Delay(5);
    LCD_WriteReg(0x004f,0);        
    LCD_WriteReg(0x004e,0);        
  }
  LCD_Delay(5);
}

/*******************************************************************************
* Function Name  : LCD_SetCursor
* Description    : Sets the cursor position.
*******************************************************************************/
void LCD_SetCursor(uint16_t Xpos,uint16_t Ypos)
{																												 
		if(DeviceCode==0x8989)
  		{
		LCD_WriteReg(0x004e,Xpos);
    	LCD_WriteReg(0x004f,Ypos);
  		}
		else if(DeviceCode==0x9919)
  		{
    	LCD_WriteReg(0x004e,Xpos);
    	LCD_WriteReg(0x004f,Ypos);
  		}
		else
  		{
    	LCD_WriteReg(0x0020,Xpos);
    	LCD_WriteReg(0x0021,Ypos);
  		}
}

/*****************************************************************************
* Function Name  : LCD_SetPoint
*******************************************************************************/
void LCD_SetPoint(uint16_t Xpos,uint16_t Ypos,uint16_t point)
{																		 
 	uint16_t Buff;
	int8_t f,g,s;
	if (PMode==0)
		{	
			Buff=Xpos;
			Xpos=Ypos;
			Ypos=0x013f-Buff;
		}
	if ((Xpos>239)||(Ypos>319)) return;

	if(PSize==1)
		{
			LCD_SetCursor(Xpos,Ypos);
			LCD_WriteRAM_Prepare();
			LCD_WriteRAM(point);
		}
	else
		{
		s=PSize/2;
		for(f=-s;f<(s+1);f++)
			{
			for(g=-s;g<(s+1);g++)
				{
					LCD_SetCursor(Xpos+f,Ypos+g);
					LCD_WriteRAM_Prepare();
					LCD_WriteRAM(point);
				}
			}
		}	
}

/*******************************************************************************
* Function Name  : LCD_GetPoint
*******************************************************************************/
uint16_t LCD_GetPoint(uint16_t Xpos,uint16_t Ypos)
{
  	uint16_t Buff;				
		if (PMode==0x00)
		{	
		Buff=Xpos;
		Xpos=Ypos;
		Ypos=0x013f-Buff;
		}
	LCD_SetCursor(Xpos,Ypos);
  if( DeviceCode==0x7783 || DeviceCode==0x4531 || DeviceCode==0x8989 )
    return ( LCD_ReadRAM() );
  else
    return ( LCD_BGR2RGB(LCD_ReadRAM()) );
}

/******************************************************************************
* Function Name  : LCD_DrawLine
*******************************************************************************/
void LCD_DrawLine(int x1, int y1, int x2, int y2,uint16_t bkColor)	
{ 																																		
  int x,y,dx,dy,Dx,Dy,e,i; 
	Dx=x2-x1; 
  Dy=y2-y1; 
  dx=fabs(x2-x1); 
  dy=fabs(y2-y1); 
  x=x1; 
  y=y1; 
  if(dy>dx) 
  { 
    e=-dy; 
    for(i=0;i<dy;i++) 
    { 
      LCD_SetPoint(x,y,bkColor); 
      if(Dy>=0) y++;   
      else y--;    
      e+=2*dx; 
      if(e>=0) 
      { 
        if(Dx>=0) x++; 
        else x--;  
        e-=2*dy; 
      } 
    } 
  } 
  else 
  { 
    e=-dx; 
    for(i=0;i<dx;i++) 
    { 
      LCD_SetPoint(x,y,bkColor); 
      if(Dx>=0) x++; 
      else x--; 
      e+=2*dy; 
      if(e>=0) 
      { 
        if(Dy>=0) y++; 
        else y--;
        e-=2*dx;
      } 
    } 
  } 
} 

#if ASCII_LIB > 0 

/******************************************************************************
* Function Name  : LCD_DrawPicture
*******************************************************************************/
void LCD_DrawPicture(uint16_t StartX,uint16_t StartY,uint16_t EndX,uint16_t EndY,uint16_t *pic)
{
  uint16_t i, Buff;

		if (PMode==0)
		{	
		 Buff=StartX;		 
		 StartX=0x013f-StartY;
		 StartY=Buff;
		 Buff=EndX;		 
		 EndX=0x013f-EndY;
		 EndY=Buff;
		 }
	LCD_SetCursor(StartX,StartY);  
  LCD_WriteRAM_Prepare();
  for (i=0;i<(EndX*EndY);i++)
  {
      LCD_WriteRAM(*pic++);
  }
}

/*******************************************************************************
* Function Name  : LCD_SetWindows
*******************************************************************************/
void LCD_SetWindows(uint16_t xStart,uint16_t yStart,uint16_t xLong,uint16_t yLong) 
{
  uint16_t Buff;
	
	if (PMode==0)
		{	
		 Buff=xStart;
		 xStart=yStart;
		 yStart=0x013f-Buff;
		 Buff=xLong;
		 xLong=yLong;
		 yLong=Buff;	
	  }
	LCD_SetCursor(xStart,yStart); 
  LCD_WriteReg(0x0050,xStart);
  LCD_WriteReg(0x0051,xStart+xLong-1);
  LCD_WriteReg(0x0052,yStart);
  LCD_WriteReg(0x0053,yStart+yLong-1);
}

/******************************************************************************
* Function Name  : LCD_Clear

*******************************************************************************/
void LCD_Clear(uint16_t Color)
{
  uint32_t index=0;
  LCD_SetCursor(0,0); 
  LCD_WriteRAM_Prepare();
  for(index=0;index<76800;index++)
   {
     LCD_RAM=Color;
   }
}
/*################################################################################
 * USER FUNCTIONS BY MILENA
 #################################################################################*/
//
//void LCD_Grad()
//{
//  uint16_t i,j;
//  uint16_t c=0;
//  LCD_SetCursor(0,0);
//  LCD_WriteRAM_Prepare();
//  for(i=0;i<320;i++)
//   {
//
//	  for(j=0;j<240;j++)
//	  {
//		  c=0x1F|((0x3f-(j>>2))<<5)|((0x1f-(j>>3))<<11);
//		  LCD_RAM=c;
//	  }
//   }
//}
//void LCD_DrawBird(uint16_t x, uint16_t y)
//{
//	if(x>320)
//		x=320;
//	if(y>240)
//		y=240;
//	uint16_t cnt=0,c,i,j;
//	LCD_SetCursor(x,y);
//	LCD_WriteRAM_Prepare();
//	for(j=y;j<y+20;j++)
//	{
//		for(i=x+25;i>x;i--)
//		{
//		  c=flappymimi[cnt];
//		  /*if(((c&0x1F)>0x0F) && ((c>>5)<0x0F))
//		  {
//			  LCD_SetCursor(i,j+1);
//			  LCD_WriteRAM_Prepare();
//		  }
//		  else*/
//		  LCD_SetCursor(j,i);
//		  LCD_WriteRAM_Prepare();
//		  if(!(((c&0x1F)>0x0F) && ((c>>5)<0x0F)))
//			  LCD_RAM=c;
//		  cnt++;
//		}
//	}
//}
//extern int32_t tx, pozgap,pozgap2;
//extern uint16_t score;
//void LCD_Draw(uint16_t x, uint16_t y)
//{
//	if(x>320)
//		x=320;
//	if(y>240)
//		y=240;
//	uint16_t cnt=0,cnt_br1=0,cnt_br2=0,c,i,j;
//	int16_t index1,index2;
//	LCD_SetCursor(0,0);
//	LCD_WriteRAM_Prepare();
//	for(i=0;i<320;i++)
//	{
//	  for(j=0;j<240;j++)
//	  {
//		  if(i>304 && j<20)
//		  {
//			  LCD_RAM=brojevi[score/10][cnt_br1++];
//		  }
//		  else if (i>288 && j<20)
//		  {
//			  LCD_RAM=brojevi[score%10][cnt_br2++];
//		  }
//		  else if(((j<=(pozgap-PREP_GAP/2)) || (j>=pozgap+PREP_GAP/2)) && (i>=(tx/10-PREP_WIDTH)) && (i<(tx/10)))
//		  {
//			  index1=i-tx/10+PREP_WIDTH;
//			  if((j==(pozgap-PREP_GAP/2))||(j==pozgap+PREP_GAP/2))
//				  LCD_RAM=0;
//			  else
//			  if(index1>=0)
//				  LCD_RAM=cev[index1];
//			  else
//				  LCD_RAM=0xFFF;
//		  }
//		  else if((pozgap2!=0) && ((j<=(pozgap2-PREP_GAP/2)) || (j>=pozgap2+PREP_GAP/2)) && (i>=(tx/10+KRUZENJE)) && (i<(tx/10+KRUZENJE+PREP_WIDTH)))
//		  {
//			  index2=i-tx/10-KRUZENJE;
//			  if((j==(pozgap2-PREP_GAP/2))||(j==pozgap2+PREP_GAP/2))
//				  LCD_RAM=0;
//			  else
//			  if(index2>=0)
//				  LCD_RAM=cev[index2];
//			  else
//				  LCD_RAM=0xFFF;
//
//		  }
//		  else if((i<=(x+25)) && i>x && j>=y && (j<(y+20)) )
//		  {
//			  c=flappymimi[cnt];
//			  if(!(((c&0x1F)>0x0F) && ((c>>5)<0x0F)))
//				  LCD_RAM=c;
//			  else
//			  {
//				  c=0x1F|((0x3f-(j>>2))<<5)|((0x1f-(j>>3))<<11);
//				  LCD_RAM=c;
//			  }
//			  cnt++;
//		  }
//		  else
//		  {
//			  c=0x1F|((0x3f-(j>>2))<<5)|((0x1f-(j>>3))<<11);
//			  LCD_RAM=c;
//		  }
//	  }
//	}
//}

/******************************************************************************
* Function Name  : PutChar1
*******************************************************************************/
void PutChar1(unsigned short Xpos,unsigned short Ypos,unsigned char c,unsigned short charColor,unsigned short bkColor)
{
  unsigned short i=0;
  unsigned short j=0;
  unsigned char buffer[16];
  unsigned char tmp_char=0;
 		
  GetASCIICode(buffer,c);
  for (i=0;i<16;i++)
  {
    tmp_char=buffer[i];
    for (j=0;j<8;j++)
    {
      if ( (tmp_char >> (7-j)) & (0x01 == 0x01))
        {
          LCD_SetPoint(Xpos+j,Ypos+i,charColor);  
        }
        else
        {
          LCD_SetPoint(Xpos+j,Ypos+i,bkColor);  
        }
    }
  }
}

/******************************************************************************
* Function Name  : PutCharRL
*******************************************************************************/
void PutCharRL(unsigned short Xpos,unsigned short Ypos,unsigned char c,unsigned short charColor,unsigned short bkColor)
{
	Xpos=Xpos * 8;
	Ypos=Ypos * 16;
	PutChar1(Xpos,Ypos,c,charColor,bkColor);
}

/******************************************************************************
* Function Name  : GUI_Text
*******************************************************************************/
void GUI_Text(uint16_t Xpos, uint16_t Ypos, uint8_t *str, uint16_t Color, uint16_t bkColor)
{
	uint8_t TempChar;
	
 do
  {
    TempChar=*str++;  
    PutChar1(Xpos,Ypos,TempChar,Color,bkColor);
		if(PMode==0x01)
		{
	  	if (Xpos<232)
    		{
      	Xpos=Xpos+8;
    		} 
    	else if (Ypos<287)
    		{	
      	Xpos=0;
      	Ypos=Ypos+16;
    		}   
    		else
    		{
      	Xpos=0;
      	Ypos=0;
    		}    
		}
		if(PMode==0)
		{
	  	if (Xpos<311)
				{
				Xpos=Xpos+8;
    		} 
    	else if	(Ypos<208)
				{
				Ypos=Ypos+16;
				Xpos=0;
				}
   		else
    		{
      	Xpos=0;
      	Ypos=0;
				}    			
		}	
	}
  while (*str!=0);
}

#endif
#if HZ_LIB > 0
#endif

/******************************************************************************
* Function Name  : GUI_TextRL
*******************************************************************************/
void GUI_TextRL(uint16_t Xpos, uint16_t Ypos, uint8_t *str, uint16_t Color, uint16_t bkColor)
{
	Xpos=Xpos * 8;
	Ypos=Ypos * 16;
	GUI_Text(Xpos, Ypos, str, Color, bkColor);
}

/******************************************************************************
* Function Name  : LCD_BGR2RGB
*******************************************************************************/
uint16_t LCD_BGR2RGB(uint16_t color)
{
  uint16_t  r, g, b, rgb;
  b = ( color>>0 )  & 0x1f;
  g = ( color>>5 )  & 0x3f;
  r = ( color>>11 ) & 0x1f;
  rgb =  (b<<11) + (g<<5) + (r<<0);
  return( rgb );
}

/******************************************************************************
* Function Name  : LCD_BackLight_Init
*******************************************************************************/
void LCD_BackLight_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure; 
  TIM_OCInitTypeDef TIM_OCInitStructure;
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO , ENABLE);
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_5 ;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_PinRemapConfig(GPIO_PartialRemap_TIM3, ENABLE);
  TimerPeriod = (uint16_t) (SystemCoreClock / 1000000) - 1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;  
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseStructure.TIM_Prescaler = TimerPeriod;  
  TIM_TimeBaseStructure.TIM_Period = 999;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = Channel2Pulse; 
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
  TIM_ARRPreloadConfig(TIM3, ENABLE);  
  TIM_Cmd(TIM3, ENABLE);
}
/******************************************************************************
* Function Name  : LCD_BackLight
*******************************************************************************/
FunctionalState LCD_BackLight( uint8_t percent)
{
  if( percent <= 100)
  {
    Channel2Pulse=percent*10;
	LCD_BackLight_Init(); 
	return ENABLE;
  } 
  else
    return DISABLE;
}

/*******************************************************************************
* Function Name  : LCD_Rectangle( )
*******************************************************************************/
void LCD_Rectangle(uint16_t x, uint16_t y, uint16_t longx, uint16_t longy, uint8_t grosor, uint16_t color)
{
  int f;
	for(f=0;f<grosor;f++)
		{
	  LCD_DrawLine(x,y+f, x+longx, y+f, color);
    LCD_DrawLine(x,y+longy-f, x+longx+1, y+longy-f, color);
    LCD_DrawLine(x+f,y, x+f, y+longy, color);
    LCD_DrawLine(x+longx-f,y, x+longx-f, y+longy, color);
  	}
}
/*******************************************************************************
* Function Name  : RectangleFill( )
*******************************************************************************/
void LCD_RectangleFill(uint16_t x, uint16_t y, uint16_t longx, uint16_t longy, uint16_t color)
{
  int f;
  for(f=0;f<longy+1;f++)
  	{
	  LCD_DrawLine(x, y+f, x+longx, y+f, color);
    }
}

/*******************************************************************************
* Function Name  : LCD_Button( )
*******************************************************************************/
void LCD_Button(uint16_t x, uint16_t y, uint16_t longx, uint16_t longy, uint8_t p, char* text, uint16_t ink, uint16_t bkcolor)
	{
	int f;
	LCD_DrawLine(x+1, y, x+longx-1, y, ink );
	LCD_DrawLine(x, y+1, x, y+longy, ink );
	LCD_DrawLine(x+1, y+longy, x+longx-1, y+longy, ink );
	LCD_DrawLine(x+longx-1, y+longy-1, x+longx-1, y, ink );

	for(f=1;f<longy;f++)
  	{
	  LCD_DrawLine(x+1, y+f, x+longx-1, y+f, bkcolor);
    }
  	  LCD_DrawLine(x+3,y+3, x+longx-3, y+3, ink);
  	  LCD_DrawLine(x+3,y+3, x+3, y+longy-2, ink);
  	  LCD_DrawLine(x+3,y+longy-3, x+longx-3, y+longy-3, ink);
  	  LCD_DrawLine(x+longx-4,y+3, x+longx-4, y+longy-3, ink);

	if(p==0)
		{
		LCD_DrawLine(x+3,y+longy-4, x+longx-3, y+longy-4, ink);
		LCD_DrawLine(x+longx-5,y+longy-3, x+longx-5, y+2, ink);
		LCD_DrawLine(x+3,y+longy-2, x+longx-2, y+longy-2, ink);
		LCD_DrawLine(x+longx-3,y+longy-2, x+longx-3, y+2, ink);
		GUI_Text(x+4,y+(longy/2)-8, text, ink, bkcolor);
		}
	if(p==1)
		{
		LCD_DrawLine(x+2,y+4, x+longx-3, y+4, ink);
		LCD_DrawLine(x+4,y+longy-3, x+4, y+2, ink);
		LCD_DrawLine(x+3,y+2, x+longx-3, y+2, ink);
		LCD_DrawLine(x+2,y+longy-3, x+2, y+1, ink);
		GUI_Text(x+6,y+(longy/2)-6, text, ink, bkcolor);
		}
	}

/*******************************************************************************
* Function Name  : LCD_Circle( )
*******************************************************************************/
void LCD_Circle(uint16_t Xpos, uint16_t Ypos, uint16_t radius, uint8_t grosor, uint16_t ink)
	{
	float f;
	int16_t x,y,g;	
	for(g=0;g<grosor;g++)
		{
		for(f=0;f<6.28;f=f+0.007)
			{
	  	x=(radius-g) * sin(f);
	  	y=(radius-g) * cos(f);
			LCD_SetPoint(Xpos+x, Ypos+y, ink);
			}
		}
	}

/*******************************************************************************
* Function Name  : LCD_CircleFill( )
*******************************************************************************/
void LCD_CircleFill(uint16_t Xpos, uint16_t Ypos, uint16_t radius, uint16_t ink)
	{
	float f;
	int16_t x, y;	
	for(f=0;f<3.14;f=f+0.007)
		{
	  x=radius * sin(f);
	  y=radius * cos(f);
		LCD_DrawLine(Xpos+x, Ypos+y, Xpos-x, Ypos+y, ink);
		}
	}

/*******************************************************************************
* Function Name  : LCD_Arc( )
*******************************************************************************/
void LCD_Arc(uint16_t Xpos, uint16_t Ypos, float ini, float fin, uint16_t radius, uint8_t grosor, uint16_t ink)
	{
	float f,s;
	int16_t x,y,g;
	
	ini=(ini)*(6.2831852/360);
	fin=(fin)*(6.2831852/360);
	s=0.4/radius;
	for(g=0;g<grosor;g++)
		{
		for(f=ini;f<fin;f=f+s)
			{
	  	x=(radius-g) * sin(f);
	  	y=(radius-g) * cos(f);
			LCD_SetPoint(Xpos+x, Ypos-y, ink);
			}
		}
	}

/*******************************************************************************
* Function Name  : LCD_CheckBox( )
*******************************************************************************/
void LCD_CheckBox(uint16_t x, uint16_t y, uint8_t p, uint16_t ink)
	{
	uint8_t mX[12]={4,5,5,6,7,7,8,8,9,9,10,11};
	uint8_t mY[12]={6,7,8,9,10,11,9,8,7,6,5,4};
    uint8_t f;
	LCD_RectangleFill(x,y,16,16,White);
	LCD_Rectangle(x,y,16,16,1,ink);
	LCD_Rectangle(x+2,y+2,12,12,1,ink);
	if(p==1)
		{
		for(f=0;f<12;f++)
			{
			LCD_SetPoint(x+mX[f],y+mY[f],ink);
			LCD_SetPoint(x+1+mX[f],y+mY[f],ink);
			}
		}
	}

/*******************************************************************************
* Function Name  : LCD_RadioButton( )
*******************************************************************************/
void LCD_RadioButton(uint16_t x, uint16_t y, uint8_t p, uint16_t ink)
	{
	LCD_RectangleFill(x,y,16,16,White);
	LCD_Rectangle(x,y,16,16,1,ink);
	LCD_DrawLine(x+5,y+2,x+12,y+2,ink);
	LCD_DrawLine(x+5,y+14,x+12,y+14,ink);
	LCD_DrawLine(x+2,y+5,x+2,y+12,ink);
	LCD_DrawLine(x+14,y+5,x+14,y+12,ink);
	LCD_SetPoint(x+3 ,y+4 ,ink);
	LCD_SetPoint(x+4 ,y+3 ,ink);
	LCD_SetPoint(x+12 ,y+3 ,ink);
	LCD_SetPoint(x+13 ,y+4 ,ink);
	LCD_SetPoint(x+3 ,y+12 ,ink);
	LCD_SetPoint(x+4 ,y+13 ,ink);
	LCD_SetPoint(x+12 ,y+13 ,ink);
	LCD_SetPoint(x+13 ,y+12 ,ink);
	if(p==1)
		{
		LCD_DrawLine(x+6,y+5,x+11,y+5,ink);	 
		LCD_DrawLine(x+5,y+6,x+12,y+6,ink);
		LCD_DrawLine(x+5,y+7,x+12,y+7,ink);
		LCD_DrawLine(x+5,y+8,x+12,y+8,ink);
		LCD_DrawLine(x+5,y+9,x+12,y+9,ink);
		LCD_DrawLine(x+5,y+10,x+12,y+10,ink);
		LCD_DrawLine(x+6,y+11,x+11,y+11,ink);
		}
	}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
