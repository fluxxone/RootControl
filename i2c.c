#include "i2c.h"
//=========================================================

#include <math.h>    //Keil library
#include <stdio.h>   //Keil library
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"

#define noACK 0
#define ACK   1


#define ERROR ((char)(0))
#define OK ((char)(1))
#define NOP() SoftDelay_us(30);//

/*************引脚定义*********************************/
#define I2C_SDA GPIO_Pin_11
#define I2C_SCL GPIO_Pin_10
#define I2C_GPIO GPIOB
/***************数据输出***************************/
#define I2C_SDA_LOW() GPIO_ResetBits(I2C_GPIO, I2C_SDA)
#define I2C_SDA_HIGH() GPIO_SetBits(I2C_GPIO, I2C_SDA)
/****************数据输入********************************/
#define I2C_SDA_READ() GPIO_ReadInputDataBit(I2C_GPIO, I2C_SDA)  //读之前必须置高 释放数据总线
/***************时钟选择***************************/
#define I2C_SCL_LOW() GPIO_ResetBits(I2C_GPIO, I2C_SCL)
#define I2C_SCL_HIGH() GPIO_SetBits(I2C_GPIO, I2C_SCL)
/****************时钟判断*******************************/
#define I2C_SCL_READ() GPIO_ReadInputDataBit(I2C_GPIO, I2C_SCL)//读之前必须置高
/************************************************/
#define I2C_RAddr (0x01) //
#define I2C_WAddr (0x00)       //I2C中，7位地址后紧跟的一位为读写判断位




/************************************************************/


void SoftDelay_us(vu32 count)
{
// for 72Mhz
count *= 6;
while(count--)
{

__NOP();

}

}


void I2C_init(void)    //初始化I2C的引脚
{

unsigned charsht_temp;
GPIO_InitTypeDef GPIO_InitStructure;


//------- 防I2C设备 锁死 SDA 线
RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
GPIO_InitStructure.GPIO_Pin = I2C_SDA | I2C_SCL;   //输入模式  判断总线状态
GPIO_Init(I2C_GPIO, &GPIO_InitStructure);

if(!I2C_SDA_READ() || I2C_SCL_READ())
{
// 如果 SDA 线被锁低 或 SCL拉低    若SCL线拉低
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_OD;
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
GPIO_InitStructure.GPIO_Pin = I2C_SCL;
GPIO_Init(I2C_GPIO, &GPIO_InitStructure);

int sht_temp;
for(sht_temp=0; sht_temp<8; sht_temp++)
{

    I2C_SCL_LOW();
    NOP();
NOP();
    I2C_SCL_HIGH();
    NOP();
NOP();

}

}

    GPIO_InitStructure.GPIO_Pin   = (I2C_SCL | I2C_SDA);
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;  //开漏输出

    GPIO_Init(I2C_GPIO, &GPIO_InitStructure);

//GPIO_PinLockConfig(I2C_GPIO, I2C_SCL | I2C_SDA);  //锁定时钟输出的属性


}


/*
* name:AM2321_Start
* function: 启动温湿度传感器 AM2321
* 参数：无
* 返回值：无
*/
void AM2321_Start(unsigned int am2321_addr)
{

I2C_start();
I2C_send(am2321_addr+I2C_WAddr);
I2C_Test_Ack();
SoftDelay_us(3500);
I2C_stop();

}



/*
*function:set SDA to GPIO_Mode_IN
*/
void I2C_SDA_SetIN(void)
{

GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Pin   =  I2C_SDA;
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
GPIO_Init(I2C_GPIO, &GPIO_InitStructure);

}
/*
*function:set SDA to GPIO_Mode_OUT
*/
void I2C_SDA_SetOUT(void)
{

GPIO_InitTypeDef GPIO_InitStructure;
GPIO_InitStructure.GPIO_Pin   =  I2C_SDA;
GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_OD;
GPIO_Init(I2C_GPIO, &GPIO_InitStructure);

}

/**************I2C启动*******************************/
void I2C_start(void)// I2C启动 Start
{

I2C_SDA_HIGH();
NOP();
I2C_SCL_HIGH();
NOP();
NOP();
I2C_SDA_LOW();
NOP();
NOP();
    I2C_SCL_LOW();
NOP();
NOP();

}
/**************I2C停止************************/
void I2C_stop(void)// I2C停止  Stop
{

I2C_SDA_LOW();
NOP();
I2C_SCL_HIGH();
NOP();
NOP();
I2C_SDA_HIGH();
NOP();
NOP();

}
/************I2C 主接受 继续操作*****************************/
void I2C_Rec_Ack(void)// I2C 主接受，继续操作，确认应答
{

I2C_SDA_LOW();
NOP();
NOP();
I2C_SCL_HIGH();
NOP();
NOP();
I2C_SCL_LOW();
NOP();
NOP();

}
/***********I2C 主接受 结束操作******************************/
void I2C_End_Ack(void)// I2C 主接受，结束操作，确认应答
{

I2C_SDA_HIGH();
NOP();
NOP();
I2C_SCL_HIGH();
NOP();
NOP();
I2C_SCL_LOW();
NOP();
NOP();

}
/***************Ack 判断确认**************************************/
//return value: true: have ACK
//false:no ACK
boole I2C_Test_Ack(void)// I2C 从接受确认应答
{

unsigned char I2Ctest_time;
boole  Ack_SDA;

    NOP();
    I2C_SDA_HIGH();
I2C_SDA_SetIN(); //设置为输入
NOP();
NOP();
I2C_SCL_HIGH();
NOP();// wait ACKSDA=0
I2Ctest_time = 0;

while (1)
{

	NOP();
if(I2C_SDA_READ()==0)
{

Ack_SDA = true;
break;

}
I2Ctest_time++;
if(I2Ctest_time>40)
{

Ack_SDA = false;
break;// 必须调整为合适的时间间隔，避免浪费主程序的等待时间

}

}
I2C_SCL_LOW();
I2C_SDA_SetOUT();//设置为输出
    NOP();
return(Ack_SDA);

}
/*
*
*description: I2C判断从器件是否忙
*parameter: I2C_Addr
*return value： 0：not busy
1: busy
*/
boole I2C_CheckBusy(unsigned char I2C_Addr)
{

I2C_stop();
I2C_start();
I2C_send( I2C_Addr + I2C_WAddr );
if(!I2C_Test_Ack())
{

return true;  //busy

}
else
{

return false; //not busy

}

}

/*************I2C接收数据**************************************/
unsigned char I2C_receive(void)   ////I2C接受 数据从高位到低位
{

unsigned char I2C_data;
unsigned char re_i;

I2C_SDA_HIGH();
I2C_SDA_SetIN(); //设置为输入
I2C_data = 0;
for(re_i=0; re_i<8; re_i++)
{

I2C_SCL_HIGH();
NOP();
I2C_data<<=1;
if(I2C_SDA_READ()==1)
I2C_data += 1;
I2C_SCL_LOW();
NOP();

}
I2C_SDA_SetOUT();//设置为输出
return(I2C_data);

}
/**************I2C发送字节数据********************************/
void I2C_send(unsigned char I2C_data)  // I2C发送
{

unsigned char sendi;

for(sendi=0; sendi<8; sendi++)
{

if(I2C_data&0x80)
{

I2C_SDA_HIGH();

}
else
{

I2C_SDA_LOW();

}
//NOP();
NOP();
	I2C_SCL_HIGH();
NOP();
//NOP();//
I2C_data<<=1;
	I2C_SCL_LOW();
NOP();

}

}


/*****************I2C读器件整体数据*********************************************/
/*
*函数名：I2C_Read
*功能  ：从24c02随机地址中读入数据  实现页读功能  当Len大于8时，会从该页头开始重复读
*传入参数：I2C_Addr : I2C 器件地址
   Data_Addr: 字地址
   Len    ：写入字节的长度
*传出参数：pData：指向传入参数的指针
*返回值：成功返回TURE  失败返回FALSE
*/
boole I2C_Read(unsigned char I2C_Addr,unsigned char *pData, unsigned char Len)   // I2C 连续读Len字节
{

unsigned char readi2c;

I2C_start();
I2C_send(I2C_Addr + I2C_RAddr);
if(I2C_Test_Ack())
{

SoftDelay_us(50);

if(Len>1)
{

for(readi2c=0;readi2c<(Len-1);readi2c++)
{

*pData = ( I2C_receive() ); pData++;
I2C_Rec_Ack();

}
*pData = I2C_receive();

I2C_End_Ack();
I2C_stop();
return(TRUE);

}

}

I2C_stop();
return(FALSE);

}



/********************I2C写器件整体数据*****************************************/
/*
*函数名：I2C_Write
*功能  ：指定地址中写入数据
*传入参数：I2C_Addr : I2C 器件地址
   Fun_Data: 功能码
   pData：指向传入参数的指针
   Len    ：写入字节的长度
*传出参数：无
*返回值：成功返回TURE  失败返回FALSE
*/
boole I2C_Write(unsigned char I2C_Addr, unsigned char Fun_Data, unsigned char *pData, unsigned char Len)
{
// I2C 连续写Len字节
unsigned char writei;
//while(I2C_CheckBusy(I2C_Addr)) //判断从器件是否忙
//{

//NOP();
//
//}
I2C_start();
I2C_send(I2C_Addr + I2C_WAddr);
if(I2C_Test_Ack())
{

I2C_send(Fun_Data);
if(I2C_Test_Ack())
{

for(writei=0; writei<Len; writei++)
{

I2C_send( *pData );
pData++;
if(!I2C_Test_Ack())//如果没有应答信号 停止写入
{

I2C_stop();
return(FALSE);

}

}
I2C_stop();
return(TRUE);

}

}
I2C_stop();
return(FALSE);

}


/****************************************************/
/************************************************************************/
