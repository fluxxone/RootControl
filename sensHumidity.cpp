#include "sensHumidity.h"
#include "stm32f10x_i2c.h"
#include "stm32f10x_rcc.h"
void initI2C2()
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);



	I2C_InitTypeDef i2c2def;
	I2C_StructInit(&i2c2def);
	I2C_Init(I2C2, &i2c2def);
	I2C_Cmd(I2C2,ENABLE);


}
sensHumidity::sensHumidity()
{
	initI2C2();
}

void sensHumidity::run()
{

}
