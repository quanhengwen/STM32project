#ifndef _DHT12_H_
#define _DHT12_H_
#include "stm32f0xx.h"
#include "myiic.h"
#include "stdio.h"
#include "usart.h"
#include "MyLCD.h"


void sensor_iic_init(void);//初始化DHT12_IIC
void sensor_read(void);//读取数据

extern unsigned char maohao_string[]; 



#endif	//_DHT12_H_
