#ifndef __DELAY_H__
#define __DELAY_H__

#include "GW32L.h"

void delay_us(uint32_t u32Cnt);
void delay_ms(uint32_t u32Cnt);
void delay_0_5_ms(uint32_t u32Cnt);
void SysTick_Configuration(void);
void CMU_Configuration(void);
void delay_1_us(uint32_t u32Cnt);
#endif



