/**
  ******************************************************************************
  * @file    GW32L0xx_buzzer.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the BUZZER
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW32L0XX_BUZZER_H
#define __GW32L0XX_BUZZER_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

typedef enum
{
	BUZZER_ClkSel_HCLK = 0x0,
	BUZZER_ClkSel_1_2HCLK = 0x1,
	BUZZER_ClkSel_1_4HCLK = 0x2,
	BUZZER_ClkSel_1_8HCLK = 0x3

} BUZZER_ClkSel_TypeDef;

typedef struct
{
	BUZZER_ClkSel_TypeDef BUZZER_ClkSel;
	uint16_t BUZZER_FreqAdjustDivisor;

} BUZZER_InitTypeDef;

void BUZZER_DeInit(void);
void BUZZER_StructInit(BUZZER_InitTypeDef* BUZZER_InitStruct);
void BUZZER_Init(BUZZER_InitTypeDef* BUZZER_InitStruct);
void BUZZER_Cmd(FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_BUZZER_H */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
