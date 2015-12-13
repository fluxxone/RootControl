#ifndef __I2C__
#define __I2C__

#ifdef __cplusplus
 extern "C" {
#endif

#include "stm32f10x.h"

#define ErrTemperature (-100)

#ifndef false
#define false FALSE
#endif

#ifndef true
#define true TRUE
#endif

typedef enum {
FALSE = 0, TRUE = !FALSE
} boole;

//---------------------------
void I2C_init(void);
void SoftDelay_us(vu32 count);
void AM2321_Start(unsigned int am2321_addr);//AM2321 启动
void I2C_start(void);// I2C启动
void I2C_stop(void);// I2C停止
void I2C_Rec_Ack(void);// I2C 主接受，继续操作，确认应答
void I2C_End_Ack(void);// I2C 主接受，结束操作，确认应答
boole I2C_Test_Ack(void);// I2C 从接受确认应答
unsigned char I2C_receive(void); //I2C接受 数据从高位到低位
void I2C_send(unsigned char I2C_data);  // I2C发送
boole I2C_Read(unsigned char I2C_Addr,  unsigned char *pData, unsigned char Len); // I2C 连续读Len字节
boole I2C_Write(unsigned char I2C_Addr, unsigned char Fun_Data, unsigned char *pData, unsigned char Len);
/**************************************************/
/**************************************************/
#ifdef __cplusplus
 }
#endif
#endif// __I2C__
