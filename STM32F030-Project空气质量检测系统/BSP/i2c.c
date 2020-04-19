/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：i2c.c
 * 描述    ：初始化IIC及一些基本的操作
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2015-12-20
 * 硬件连接: SCL--PF6,SDA--PF7 
 * 调试方式：J-Link-OB
******************************************************************************/	

//头文件
#include "SYSTICK.h"
#include "i2c.h"
#include "usart.h"
#include "string.h"



 /**
  * @file   I2C_Configuration
  * @brief  EEPROM管脚配置
  * @param  无
  * @retval 无
  */
void I2C_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 
	/* Configure I2C2 pins: PB6->SCL and PB7->SDA */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);//开启GPIOB时钟
	
	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SCL_PIN;//PB7   SCL
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//频率选择
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;  
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = EEPROM_I2C_SDA_PIN;//PB8  SDA
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;  
	GPIO_Init(EEPROM_I2C_SDA_GPIO_PORT, &GPIO_InitStructure);
	//SDA_H;//PB8拉高
	//SCL_H;//PB9拉高
}


/**************************IIC模块发送函数************************************************

 *************************************************************************/
//写入  最后将SDA拉高，以等待从设备产生应答
void IIC_write(unsigned char date)
{
	unsigned char i, temp;
	temp = date;
			
	for(i=0; i<8; i++)
	{	IIC_SCK_0;
		
        if ((temp&0x80)==0)
            IIC_SDA_0;
        else IIC_SDA_1;
		temp = temp << 1;
		delay_us(1);			  
		IIC_SCK_1;
		delay_us(1);
		
	}
	IIC_SCK_0;
	delay_us(1);
	IIC_SDA_1;
	delay_us(1);
	IIC_SCK_1;
//								不需要应答
//	if (READ_SDA==0)
//		ACK = 1;
//	else ACK =0;
	delay_us(1);
	IIC_SCK_0;
	delay_us(1);
	

}

//启动信号
//SCL在高电平期间，SDA由高电平向低电平的变化定义为启动信号
void IIC_start()
{
	IIC_SDA_1;
	delay_us(1);
	IIC_SCK_1;
	delay_us(1);				   //所有操作结束释放SCL	
	IIC_SDA_0;
	delay_us(3);
	IIC_SCK_0;
	
    IIC_write(0x78);
        
}

//停止信号
//SCL在高电平期间，SDA由低电平向高电平的变化定义为停止信号
void IIC_stop()
{
	IIC_SDA_0;
	delay_us(1);
	IIC_SCK_1;
	delay_us(3);
	IIC_SDA_1;
}

