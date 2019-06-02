/**
  ******************************************************************************
  * @file    GW32L0xx_wdt.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the WDT
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW32L0XX_WDT_H
#define __GW32L0XX_WDT_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

typedef enum
{
	WDT_RstPulseLen_2PClkCycles = 0x0,
	WDT_RstPulseLen_4PClkCycles = 0x1,
	WDT_RstPulseLen_8PClkCycles = 0x2,
	WDT_RstPulseLen_16PClkCycles = 0x3,
	WDT_RstPulseLen_32PClkCycles = 0x4,
	WDT_RstPulseLen_64PClkCycles = 0x5,
	WDT_RstPulseLen_128PClkCycles = 0x6,
	WDT_RstPulseLen_256PClkCycles = 0x7

} WDT_RstPulseLen_TypeDef;

typedef enum
{
	WDT_RespMode_SysReset = 0x0,
	WDT_RespMode_Interrupt = 0x1

} WDT_RespMode_TypeDef;	

typedef struct
{
	uint8_t WDT_TimeOverCycle;

	WDT_RespMode_TypeDef WDT_RespMode;

	WDT_RstPulseLen_TypeDef WDT_RstPulseLen;

} WDT_InitTypeDef;

void WDT_DeInit(void);
void WDT_Init(WDT_InitTypeDef* WDT_InitStruct);
void WDT_StructInit(WDT_InitTypeDef* WDT_InitStruct);

void WDT_Cmd(FunctionalState NewState);
void WDT_RestartCmd(FunctionalState NewState);

ITStatus WDT_GetITStatus(void);
void WDT_ClearITFlag(void);

uint32_t WDT_GetCurrentWDTimer(void);	 

#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_WDT_H */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
