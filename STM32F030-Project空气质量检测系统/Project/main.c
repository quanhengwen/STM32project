/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：main.c
 * 描述    ：主要是完成对eeprom的写操作和读操作
 * 库版本  ：V1.3.0
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2015-10-20
 * 调试方式：J-Link-OB
**********************************************************************************/

//头文件
#include <string.h>
#include "stm32f0xx.h"
#include "led.h"
#include "SYSTICK.h"
#include "usart.h"
#include "i2c.h"
#include <stdio.h>
#include "MyLCD.h"
#include "ADC.h"
#include "Alarm.h"
#include "DHT12.h"

const unsigned char  *point;//定义不可改变的指针
unsigned char ACK=0;
extern unsigned char  picture_tab[];//字模信息
extern unsigned char F16x16[];
extern unsigned char BMP1[];
unsigned char temp_string[]="Hello everyone!"; 
unsigned char air_string[]="AQI"; 
unsigned char maohao_string[]=":"; 

int main(void)
{
	uint16_t Temp_Value;
	float ADC_Value=0.00;
	char strTemp[20];
	unsigned int i=0;
    SYSTICK_Init();			//系统初始化
    USART1_Config();//PA9  TX     PA10     RX		波特率9600
    //LED_GPIO_Config();	
    I2C_Configuration();	//IIC初始化配置   SCL——PB7    SDA——PB8
	ADC_Configuration();	//ADC配置   PA0
	Alarm_Configuration();		//嗡鸣器配置
	//IIC_Init();
	sensor_iic_init();//DHT12_IIC初始化
	
	//OLED配置显示
	point= &picture_tab[0];
	OLED_init();
    OLED_full();
	delay_ms(1000);
	OLED_clear();//清屏
	
    while (1)
    {	
		Temp_Value = ADC_GetConversionValue(ADC1);		//可燃气体监测
		ADC_Value = (3.3/4096)*Temp_Value;			 /*将AD值转换为电压值*/
		printf("\r\n 这是一个空气质量检测系统 \r\n");
		sprintf(strTemp, "%.1f", 100*ADC_Value);     //输出3.30V，意思是转化为字符串
		if(Temp_Value>3000)
			{
				Alarm_H;			//当监测到的电压值大于3/4最大值就立即嗡鸣器发声
			}
			
		//Picture_display(point);//	其本质是一个图片
		
		OLED_ShowStr(0,0,temp_string,2);
		OLED_ShowStr(0,2,air_string,2);
		OLED_ShowStr(56,2,maohao_string,2);
		OLED_ShowStr(64,2,strTemp,2);
		for(i=0;i<2;i++)
		{
			OLED_ShowCN(24+i*16,2,i); //点阵显示 
		}
		
		sensor_read();//读取温湿度数据		
		printf("The Temp_Value is %d \r\n",Temp_Value);
        printf("The AQI_ Value is %f \r\n",100*ADC_Value);
		
		//OLED_DrawBMP(0,0,127,7,BMP1);
		delay_ms(1000);	
		//Alarm_L;
		//OLED_clear();//清屏
		//Picture_ReverseDisplay(point);//图片反色显示
		//delay_ms(1000);
		//OLED_OFF(); 
		//if(i%5==0)
		{
		//	OLED_ON();
		}
    }
}


/*********************************************************************************************************
      END FILE
*********************************************************************************************************/





