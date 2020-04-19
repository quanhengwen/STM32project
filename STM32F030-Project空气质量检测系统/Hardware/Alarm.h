#include "stm32f0xx.h"

#define Alarm_H         GPIOB->BSRR = GPIO_Pin_7	 /* GPIO_SetBits(GPIOB , GPIO_Pin_6)   */
#define Alarm_L        GPIOB->BRR  = GPIO_Pin_7   /* GPIO_ResetBits(GPIOB , GPIO_Pin_6) */

void Alarm_Configuration(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure; 
	/* Configure I2C2 pins: PB6->SCL and PB7->SDA */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);//开启GPIOB时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;//PA1 接嗡鸣器
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//频率选择
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//输出模式
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;  //开路输出，外接电阻GPIO_OType_PP
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//配置上拉
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	//SDA_H;//PB8拉高
	//SCL_H;//PB9拉高
	Alarm_L;
}



