#ifndef __I2C_H
#define __I2C_H			 
#include "stm32f0xx.h"

/* Includes ------------------------------------------------------------------*/
#define IIC_SCK_PIN 7
#define IIC_SDA_PIN 8

#define EEPROM_I2C_SCL_PIN      					 	GPIO_Pin_7   //SCL  PB7
#define EEPROM_I2C_SCL_GPIO_PORT   	       	GPIOB  
#define EEPROM_I2C_SCL_GPIO_RCC      			  RCC_AHBPeriph_GPIOB  
 
#define EEPROM_I2C_SDA_PIN      					 	GPIO_Pin_8  //SDA  PB8 
#define EEPROM_I2C_SDA_GPIO_PORT   	       	GPIOB  
#define EEPROM_I2C_SDA_GPIO_RCC      			  RCC_AHBPeriph_GPIOB  

/* Private define ------------------------------------------------------------*/
#define IIC_SCK_1         GPIOB->BSRR = GPIO_Pin_7	 /* GPIO_SetBits(GPIOB , GPIO_Pin_6)   */
#define IIC_SCK_0         GPIOB->BRR  = GPIO_Pin_7   /* GPIO_ResetBits(GPIOB , GPIO_Pin_6) */
   
#define IIC_SDA_1         GPIOB->BSRR = GPIO_Pin_8	 /* GPIO_SetBits(GPIOB , GPIO_Pin_7)   */
#define IIC_SDA_0         GPIOB->BRR  = GPIO_Pin_8	 /* GPIO_ResetBits(GPIOB , GPIO_Pin_7) */

#define SCL_read      GPIOB->IDR  & GPIO_Pin_7   /* GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_6) */
#define SDA_read      GPIOB->IDR  & GPIO_Pin_8	 /* GPIO_ReadInputDataBit(GPIOB , GPIO_Pin_7) */

#define I2C_PageSize  8  /* 24C02Ã¿Ò³8×Ö½Ú */

#define ADDR_24C08		0xA0



void I2C_Configuration(void);
void IIC_write(unsigned char date);
void IIC_start(void);
void IIC_stop(void);


/* Private function prototypes -----------------------------------------------*/
//void I2C_Configuration(void);
//FunctionalState I2C_WriteByte(uint8_t SendByte, uint16_t WriteAddress, uint8_t DeviceAddress);
//FunctionalState I2C_ReadByte(uint8_t* pBuffer,   uint16_t length,   uint16_t ReadAddress,  uint8_t DeviceAddress);
//void I2C_Test(void);
// FunctionalState I2C_Start(void);
//  void I2C_Stop(void);
//   void I2C_Ack(void);
//    void I2C_NoAck(void);
//	 FunctionalState I2C_WaitAck(void) 	;
//	  void I2C_SendByte(uint8_t SendByte) ;
//	   uint8_t I2C_ReceiveByte(void) ;
//	   FunctionalState I2C_WriteByte(uint8_t SendByte, uint16_t WriteAddress, uint8_t DeviceAddress);
//	   FunctionalState I2C_ReadByte(uint8_t* pBuffer,   uint16_t length,   uint16_t ReadAddress,  uint8_t DeviceAddress);
	   
#endif 
/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
