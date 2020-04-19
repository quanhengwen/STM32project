/******************** (C) COPYRIGHT  源地工作室 ********************************
 * 文件名  ：led.c
 * 描述    ：LED灯引脚配置     
 * 作者    ：zhuoyingxingyu
 * 淘宝    ：源地工作室http://vcc-gnd.taobao.com/
 * 论坛地址：极客园地-嵌入式开发论坛http://vcc-gnd.com/
 * 版本更新: 2017-05-12
 * 硬件连接: D1->PC13;D2->PB0;D4->PB1
 * 调试方式：J-Link-OB
**********************************************************************************/	


//头文件
#include "led.h"

 /**
  * @file   LED_GPIO_Config
  * @brief  LED灯引脚配置
  * @param  无
  * @retval 无
  */
void LED_GPIO_Config(void)
{	
	//定义一个GPIO_InitTypeDef 类型的结构体
	GPIO_InitTypeDef  GPIO_InitStructure;
	//使能GPIOC的外设时钟
	RCC_AHBPeriphClockCmd(LED1_GPIO_RCC|LED2_GPIO_RCC|LED3_GPIO_RCC,ENABLE);//使能GPIO的外设时钟
	
	GPIO_InitStructure.GPIO_Pin =LED1_GPIO_PIN;	//选择要用的GPIO引脚
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	//设置引脚为普通输出模式				
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	//设置引脚为推挽输出
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; //设置引脚为上拉		
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//设置引脚速度为50MHZ
	GPIO_Init(LED1_GPIO_PORT, &GPIO_InitStructure);//调用库函数，初始化GPIO
	
	GPIO_InitStructure.GPIO_Pin =LED2_GPIO_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;				
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED2_GPIO_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin =LED3_GPIO_PIN;	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(LED3_GPIO_PORT, &GPIO_InitStructure);
	
}

 /**
  * @file   LEDXToggle
  * @brief  LED亮灭翻转
  * @param  ledx:1--PC13;2--PB0;3--PB1
  * @retval 无
  */
void LEDXToggle(uint8_t ledx)
{
  if(ledx==1)
  {
    LED1_GPIO_PORT->ODR^=LED1_GPIO_PIN;
  }
  else if(ledx==2)
  {
    LED2_GPIO_PORT->ODR^=LED2_GPIO_PIN;
  }
  else if(ledx==3)
  {
    LED3_GPIO_PORT->ODR^=LED3_GPIO_PIN;
  }

}
