/**
  ******************************************************************************
  * @file    GW32L0xx_systick.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the SysTick
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW32L0XX_SYSTICK_H
#define __GW32L0XX_SYSTICK_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

typedef enum
{
	SysTick_ClkSource_ExtRefClk_LSE = 0x0,
	SysTick_ClkSource_ExtRefClk_LSI = 0x1,
	SysTick_ClkSource_ExtRefClk_HSI = 0x2,
	SysTick_ClkSource_ExtRefClk_HSE = 0x3,
	SysTick_CLKSource_SystemCoreClock = 0x4

} SysTick_ClkSource_TypeDef;

void SysTick_CLKSourceConfig(SysTick_ClkSource_TypeDef SysTick_ClkSource);
void SysTick_ITConfig(FunctionalState NewState);
void SysTick_Cmd(FunctionalState NewState);

ITStatus SysTick_GetITStatus(void);
void SysTick_ClearITFlag(void);

void SysTick_SetReloadValue(uint32_t SysTick_ReloadValue);
uint32_t SysTick_GetReloadValue(void);

void SysTick_SetCurrentValue(uint32_t SysTick_ReloadValue);
uint32_t SysTick_GetCurrentValue(void);

#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_SYSTICK_H*/

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
