#ifndef __SYSTICK_H
#define __SYSTICK_H
#include "stm32f0xx.h"


void SYSTICK_Init(void);
void delay_us(uint16_t nus);
void delay_ms(uint16_t nms);
#endif
