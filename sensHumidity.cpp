#include "sensHumidity.h"
#include "listener.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_gpio.h"
#include "debug.h"
#include "inttypes.h"
#include "i2c.h"
#define i2c2_FLAG_TIMEOUT	((uint32_t)0x1000)
#define i2c2_LONG_TIMEOUT	((uint32_t)(500 *i2c2_FLAG_TIMEOUT))
#define AM2321_ADDRESS		(0xB8)
uint32_t Timeout;
uint16_t err;
const char* errmsg = 0;
#define Timed(x) Timeout = 0xFFFFF; while (x) { if (Timeout-- == 0) {errmsg = #x;goto errReturn;}} err++;
void initI2C2()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);

//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_1);
//	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_1);

	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
//	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
//	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	I2C_InitTypeDef I2C_InitStructure;
//	I2C_InitStructure.I2C_AnalogFilter = I2C_AnalogFilter_Enable;
//	I2C_InitStructure.I2C_DigitalFilter = 0x00;
	I2C_InitStructure.I2C_OwnAddress1 = 0x00;
	I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
	I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
	I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
	I2C_InitStructure.I2C_ClockSpeed = 50000;
	//I2C_InitStructure.I2C_Timing = 0xA0120227;
	//I2C_InitStructure.I2C_Timing = 0x20310A0D;
	I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
	I2C_Init(I2C2, &I2C_InitStructure);
	I2C_Cmd(I2C2,ENABLE);
}
void AM2321_wakeup()
{
	uint8_t tmp=0;
	err = 0;
	Timed(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C2, ENABLE);
	Timed(!I2C_GetFlagStatus(I2C2,I2C_FLAG_SB));

	I2C_Send7bitAddress(I2C2, AM2321_ADDRESS, I2C_Direction_Transmitter);

	Timed(I2C_GetFlagStatus(I2C2,I2C_FLAG_ADDR));
	tmp = I2C2->SR1;
	tmp += I2C2->SR2;
	SoftDelay_us(2000);

	I2C_Cmd(I2C2,DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, DISABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
	/* Release I2C2 from reset state */
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);
	I2C_ClearFlag(I2C2,I2C_FLAG_BUSY);
	GPIO_SetBits(GPIOB,10);
	initI2C2();

	return;

	errReturn:

	DEBUG.print("Error during wakeup, err=%"PRIu16"!\r\n",err);
	DEBUG.print(errmsg);
	DEBUG.print("\r\n");
	I2C_Cmd(I2C2,DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, DISABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
	/* Release I2C2 from reset state */
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);
	I2C_ClearFlag(I2C2,I2C_FLAG_BUSY);
	GPIO_SetBits(GPIOB,10);
	initI2C2();

	return;
}

void I2C2Write(const uint8_t* ptr,uint8_t num)
{
	uint8_t tmp=0;
	err = 0;
	Timed(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C2, ENABLE);
	Timed(!I2C_GetFlagStatus(I2C2,I2C_FLAG_SB));

	I2C_Send7bitAddress(I2C2, AM2321_ADDRESS, I2C_Direction_Transmitter);

	Timed(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));
//	Timed(I2C_GetFlagStatus(I2C2,I2C_FLAG_ADDR));
//	tmp = I2C2->SR1;
//	tmp += I2C2->SR2;
//	Timed(!I2C_GetFlagStatus(I2C2,I2C_FLAG_ADDR));

	for(uint8_t i = 0; i < num; i++)
	{
		I2C_SendData(I2C2, ptr[i]);
		Timed(!I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
		//Timed(!I2C_GetFlagStatus(I2C2,I2C_FLAG_TXE));

	}
	Timed(!I2C_GetFlagStatus(I2C2,I2C_FLAG_BTF));
	I2C_GenerateSTOP(I2C2,ENABLE);

	Timed(I2C_GetFlagStatus(I2C2, I2C_FLAG_STOPF));
	return;

	errReturn:

	DEBUG.print("Error during write, err=%"PRIu16"!\r\n",err);
	DEBUG.print(errmsg);
	DEBUG.print("\r\n");
	I2C_Cmd(I2C2,DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, DISABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
	/* Release I2C2 from reset state */
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);
	I2C_ClearFlag(I2C2,I2C_FLAG_BUSY);
	GPIO_SetBits(GPIOB,10);
	initI2C2();
	return;
}


bool I2C2ReadReg(uint8_t* ptr,uint8_t num)
{
	uint8_t tmp=0;
	err = 0;
	Timed(I2C_GetFlagStatus(I2C2, I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C2, ENABLE);
	Timed(!I2C_GetFlagStatus(I2C2,I2C_FLAG_SB));

	I2C_Send7bitAddress(I2C2, AM2321_ADDRESS, I2C_Direction_Receiver);

	Timed(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));

	for(uint8_t i = 0; i < num; i++)
	{
		Timed(!I2C_CheckEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED));
		ptr[i]=I2C_ReceiveData(I2C2);


	}
	I2C_NACKPositionConfig(I2C2, I2C_NACKPosition_Current);
	I2C_AcknowledgeConfig(I2C2,DISABLE);

	I2C_GenerateSTOP(I2C2,ENABLE);
	Timed(I2C_GetFlagStatus(I2C2, I2C_FLAG_STOPF));
	I2C_AcknowledgeConfig(I2C2,ENABLE);
	return true;

	errReturn:

	DEBUG.print("Error during read, err=%"PRIu16"!\r\n",err);
	DEBUG.print(errmsg);
	DEBUG.print("\r\n");
	I2C_Cmd(I2C2,DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2, DISABLE);
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, ENABLE);
	/* Release I2C2 from reset state */
	RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2, DISABLE);
	I2C_ClearFlag(I2C2,I2C_FLAG_BUSY);
	GPIO_SetBits(GPIOB,10);
	initI2C2();
	return false;
}

sensHumidityTemperature::sensHumidityTemperature()
{
	initI2C2();
	currentHumidity = 0;
	currentTemperature = 0;
}
const static uint8_t READ_REGISTER_CMD[] =
{
0x03,     // Read register command
0x00,     // start addrress
0x04     // read length
};

float getLogicalValue(uint16_t regVal)
{
    if(regVal & 0x8000)
    {
	regVal &= ~0x8000;
	return (float)regVal / -10.0;
    }
    else
    {
	return (float)regVal / 10.0;
    }
}
uint16_t calcCRC16(const uint8_t* src, int len)
{
    uint16_t crc = 0xFFFF;

	while(len--)
	{
		crc ^= *(src++);

		for(uint8_t i = 0; i < 8; i++)
		{
			if(crc & 0x01)
			{
				crc >>= 1;
				crc ^= 0xA001;
			}
			else
			{
				crc >>= 1;
			}
		}
	}

	return crc;
}
void sensHumidityTemperature::run()
{
	DEBUG.print("sensHumidity thread started!\r\n");
	float temperature;
	float humidity;
	while(1)
	{
		CoSchedLock();
		AM2321_wakeup();
		I2C2Write(READ_REGISTER_CMD,3);
		I2C2ReadReg(buffer,8);
		CoSchedUnlock();
		uint8_t  cmd     = buffer[0];
		uint8_t  dataLen = buffer[1];
		uint16_t Humidity = (buffer[2] << 8) + buffer[3];
		uint16_t Temperature = (buffer[4] << 8) + buffer[5];
		uint16_t recvCRC = buffer[6] + (buffer[7] * 256);
		uint16_t chkCRC  = calcCRC16(&buffer[0], 6);

		if(dataLen == 4)
		{
			if(recvCRC == chkCRC)
			{
				if(cmd == 0x03)
				{
					currentHumidity = Humidity;
					currentTemperature = Temperature;
					sensHumi.setVal(Humidity);
					sensTemp.setVal(Temperature);
					sensHumi.updateListeners();
					sensTemp.updateListeners();
				}
			}
		}
		CoTimeDelay(0, 0, 5, 0);
	}
}
