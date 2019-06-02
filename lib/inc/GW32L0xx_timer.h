/**
  ******************************************************************************
  * @file    GW32L0xx_timer.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the Timer 
  *          firmware library. 
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

#ifndef __GW32L0XX_TIMER_H
#define __GW32L0XX_TIMER_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

typedef enum 
{
	BTIMER_Mode_FreeCounter = 0x0,
	BTIMER_Mode_CustomizeCounter = 0x1,	
	TIMER_Mode_FreeCounter = 0x0,
	TIMER_Mode_CustomizeCounter = 0x1

} TIMER_Mode_TypeDef;

typedef enum
{
	BTIMER_PWMOutput_Disable = 0x0,
	BTIMER_PWMOutput_Enable = 0x1,
	TIMER_PWMOutput_Disable = 0x0,
	TIMER_PWMOutput_Enable = 0x1

} TIMER_PWMOutput_Typedef;


typedef enum
{
	BTIMER_CntClkSel_LF32K_38K = 0x0,
	BTIMER_CntClkSel_ExClk = 0x1,
	TIMER_CntClkSel_APBusClk = 0x0,
	TIMER_CntClkSel_ExClk = 0x1

} TIMER_CntClkSel_TypeDef;

typedef enum
{
	BTIMER_GateCtrl_Disable = 0x0,
	BTIMER_GateCtrl_Enable = 0x1,	
	TIMER_GateCtrl_Disable = 0x0,
	TIMER_GateCtrl_Enable = 0x1

} TIMER_GateCtrl_TypeDef;

typedef struct
{
	TIMER_Mode_TypeDef TIMER_Mode;

	TIMER_CntClkSel_TypeDef	TIMER_CntClkSel;

	TIMER_PWMOutput_Typedef TIMER_PWMOutput;

	TIMER_GateCtrl_TypeDef TIMER_GateCtrl;

} TIMER_InitTypeDef;


void TIMER_DeInit(TIMER_TypeDef *TIMERx);
void TIMER_StructInit(TIMER_InitTypeDef* TIMER_InitStruct);
void TIMER_Init(TIMER_TypeDef *TIMERx, TIMER_InitTypeDef* TIMER_InitStruct);
void TIMER_Cmd(TIMER_TypeDef *TIMERx, FunctionalState NewState);
void TIMER_ITConfig(TIMER_TypeDef* TIMERx, FunctionalState NewState);

uint8_t TIMER_GetAllRawITStatus(void);
ITStatus TIMER_GetITStatus(TIMER_TypeDef* TIMERx);
uint8_t TIMER_GetAllITStatus(void);
void TIMER_ClearITFlag(TIMER_TypeDef* TIMERx);
void TIMER_ClearAllITFlag(void);

void TIMER_SetLoadCounter0(TIMER_TypeDef* TIMERx, uint32_t Counter);
void TIMER_SetLoadCounter1(TIMER_TypeDef* TIMERx, uint32_t Counter);
uint32_t TIMER_GetCurrentCounter(TIMER_TypeDef* TIMERx);

#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_TIMER_H */


/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
