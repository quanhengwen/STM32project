//****************************************************************//
//模拟IIC配置程序
//注意：DHT12的IIC的通讯频率不得超过50KHZ
// 公司：    奥松电子
//****************************************************************//

#include "myiic.h"

//初始化IIC
void IIC_Init(void)
{					     
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB2PeriphClockCmd(	RCC_AHBPeriph_GPIOB, ENABLE );//使能GPIOB	
	   
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;//PB13,PB14
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT ;   //输出
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//开漏
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//配置上下拉，空
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_SetBits(GPIOB,GPIO_Pin_13|GPIO_Pin_14); 	//PB13,PB14 输出高
}

void SDA_MODE_IN(void)
{
GPIO_InitTypeDef GPIO_InitStructure;

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;//òy??????
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;//ê?è??￡ê?
GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
GPIO_Init(GPIOB, &GPIO_InitStructure);//3?ê??ˉ????
}

void SDA_MODE_OUT(void)
{
GPIO_InitTypeDef GPIO_InitStructure;

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;//òy??????
GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//ê?3??￡ê?
GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;//
GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;//2?′?é?à-μ?×è
GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;//ê?3??ù?è
GPIO_Init(GPIOB, &GPIO_InitStructure);//3?ê??ˉ????
}

//产生IIC起始信号
void IIC_Start(void)
{
	SDA_MODE_OUT();     //sda线输出
	set_SDA;	  	  
	set_SCL;
	delay_us(14);
 	clr_SDA;//开始：当SCL为高时，数据从高到低变化
	delay_us(14);
	clr_SCL;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_MODE_OUT();//sda线输出
	clr_SCL;
	clr_SDA;//停止:当SCL为高时，数据从低到高变化
 	delay_us(14);
	set_SCL;
	delay_us(14);	 
	set_SDA;//发送I2C总线结束信号
							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	clr_SCL;
	set_SDA;
	SDA_MODE_IN();      //SDA设置为输入  
	delay_us(14);	   
	set_SCL;
	delay_us(14);	 
	while(read_SDA)//等到SDA变低
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
		delay_us(1);
	}
	clr_SCL;//时钟输出0
	delay_us(10); 
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
	clr_SCL;
	SDA_MODE_OUT();
	clr_SDA;
	delay_us(15);
	set_SCL;
	delay_us(15);
	clr_SCL;
}
//产生非ACK应答		    
void IIC_NAck(void)
{
	clr_SCL;
	SDA_MODE_OUT();
	set_SDA;
	delay_us(15);
	set_SCL;
	delay_us(15);
	clr_SCL;
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
	SDA_MODE_OUT(); 	    
    clr_SCL;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
		clr_SCL;
		if((txd&0x80)>>7)
			set_SDA;
		else
			clr_SDA;
		txd<<=1; 	  
		delay_us(15);   //延时
		set_SCL;
		delay_us(15); 	
    }
	clr_SCL;	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_MODE_IN();//SDA设置为输入
    for(i=0;i<8;i++ )
	{
        clr_SCL; 
        delay_us(50);
		set_SCL;
		delay_us(50);
        receive<<=1;
        if(read_SDA)receive++;   
    }
        clr_SCL;						 
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK   
    return receive;
}



























