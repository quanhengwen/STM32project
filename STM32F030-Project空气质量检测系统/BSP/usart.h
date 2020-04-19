#ifndef __USART_H
#define __USART_H

#include "stm32f0xx.h"
#include <stdio.h>

#define BaudRate	 9600

#define USART              	 		USART1
#define USART_RCC         	 		RCC_APB2Periph_USART1

#define USART_GPIO_RCC    			RCC_AHBPeriph_GPIOA
#define USART_TX_GPIO_PinSource		        	GPIO_PinSource9
#define USART_RX_GPIO_PinSource		        	GPIO_PinSource10	
#define USART_TX		       		 	GPIO_Pin_9	// out
#define USART_RX		       		 	GPIO_Pin_10	// in 
#define USART_GPIO_PORT    			GPIOA   


void USART1_Config(void);
#endif
