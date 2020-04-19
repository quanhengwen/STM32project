#include "stm32f10x.h"
#include "delay.h"
#include "usart.h"
#include "string.h"
#include "LED.h"
#include "stdio.h"
#include "OLED_IIC.h"
 
 /*
 Keil: MDK5.10.0.2
MCU:stm32f103c8
硬件接法：
GY-39---STM32
1、GY-39_RX---STM32_TX,STM32复位将发送A5 82 27 给模块
2、STM32_TX---FT232,STM32将数据上传给上位机
3、GY-39_TX---STM32_RX，接收模块数据
软件说明:
该程序采用串口方式获取模块数据，波特率9600

注：模块波特率需和该程序波特率一样为9600，中断函数位于stm32f10x_it.c
联系方式：
http://shop62474960.taobao.com/?spm=a230r.7195193.1997079397.2.9qa3Ky&v=1
*/
static void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_X;
  
  /* 4个抢占优先级，4个响应优先级 */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  /*抢占优先级可打断中断级别低的中断*/
	/*响应优先级按等级执行*/
	NVIC_X.NVIC_IRQChannel = USART1_IRQn;//中断向量
  NVIC_X.NVIC_IRQChannelPreemptionPriority = 0;//抢占优先级
  NVIC_X.NVIC_IRQChannelSubPriority = 0;//响应优先级
  NVIC_X.NVIC_IRQChannelCmd = ENABLE;//使能中断响应
  NVIC_Init(&NVIC_X);
}
void send_com(u8 data)
{
	u8 bytes[3]={0};
	bytes[0]=0xa5;
	bytes[1]=data;//功能字节
	//bytes[2]=0x28;
	USART_Send(bytes,3);//发送帧头、功能字节、校验和
}
//typedef struct
//{
//    uint32_t P;
//    uint16_t Temp;
//    uint16_t Hum;
//    uint16_t Alt;
//} bme;

int fputc(int ch, FILE *f)
{
 while (!(USART1->SR & USART_FLAG_TXE));
 USART_SendData(USART1, (unsigned char) ch);// USART1 可以换成 USART2 等
 return (ch);
}

char strTemp[20];//OLED显示临时变量

int main(void)
{
  u8 sum=0,i=0, j=0;
	float  Temp_gaungzhaodu=0;
//	int16_t data=0;
//	uint16_t data_16[2]={0};
	unsigned char maohao_string[]=":"; 
	unsigned char temp_string[]="Lux"; 
	//unsigned char zhixian_string[]="---"; 
	delay_init(72);
	NVIC_Configuration();
	Usart_Int(9600);
	
	point= &picture_tab[0];
	IO_init();	//OLED端口初始化
	OLED_init();
	OLED_full();
	delay_ms(1000);
	OLED_clear();
	
	delay_ms(100);//等待模块初始化完成
	//send_com(0x82);//发送读气压温湿度指令
	//send_com(0x81);//连续输出光照度
	while(1)
	{
		
		send_com(0x51);//连续输出光照度
		delay_ms(100);
		if(Receive_ok)//串口接收完毕，在串口中断1处理函数中设置的
		{
			for(sum=0,i=0;i<(raw_data[3]+4);i++)//rgb_data[3]=3
			sum+=raw_data[i];
			if(sum==raw_data[i])//校验和判断
			{
				Temp_gaungzhaodu=(raw_data[4]<<24)|(raw_data[5]<<16)|(raw_data[6]<<8)|(raw_data[7]);//获取的是温度的值
				Temp_gaungzhaodu=Temp_gaungzhaodu/100;//光照度运算结果
				sprintf(strTemp, "%.2f", Temp_gaungzhaodu);     //输出3.30V，意思是转化为字符串
				
				for(j=0;j<6;j++)
				{
					OLED_ShowCN(16+j*16,0,j); //点阵显示 
				}
				for(j=6;j<12;j++)
				{
					OLED_ShowCN((j-6)*16,2,j);
				}
				OLED_ShowStr(96,2,maohao_string,2);
				OLED_ShowStr(80,4,temp_string,2);
				OLED_ShowStr(24,4,strTemp,2);
				for(j=12;j<15;j++)
				{
					OLED_ShowCN(24+(j-12)*16,6,j);
				}
				OLED_ShowStr(72,6,maohao_string,2);
				for(j=15;j<18;j++)
				{
					OLED_ShowCN(80+(j-15)*16,6,j);
				}

			}
			Receive_ok=0;//处理数据完毕标志
			delay_ms(1000);
		}
	}
}
