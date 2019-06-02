/**
  ******************************************************************************
  * @file    GW32L0xx_lvd.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the LVD
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW32L0XX_LVD_H
#define __GW32L0XX_LVD_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

#define LVD_IntTrigSel_NO                   	(0x0)
#define LVD_IntTrigSel_Level_High             LVD_CTRL0_INTL
#define LVD_IntTrigSel_Edge_Rising            LVD_CTRL0_INTPOS
#define LVD_IntTrigSel_Edge_Falling  				  LVD_CTRL0_INTNEG	

typedef enum
{
	LVD_InputNegative_VCC = 0x0,
	LVD_InputNegative_PORT0_Pin_8 = 0x1,
	LVD_InputNegative_PORT0_Pin_9 = 0x2,
	LVD_InputNegative_PORT0_Pin_10 = 0x3

} LVD_InputNegative_TypeDef;

typedef enum
{
	LVD_OutputSignal_Interrupt = 0x0,
	LVD_OutputSignal_SystemReset = 0x1

} LVD_OutputSignal_TypeDef;

typedef enum
{
	LVD_BiasCurrent_80nA = 0x0,
	LVD_BiasCurrent_720nA = 0x1

} LVD_BiasCurrent_TypeDef;

typedef enum
{
	LVD_InputPositiveRefVolt_1P9V = 0x0,
	LVD_InputPositiveRefVolt_2P0V = 0x1,
	LVD_InputPositiveRefVolt_2P1V = 0x2,
	LVD_InputPositiveRefVolt_2P2V = 0x3,
	LVD_InputPositiveRefVolt_2P3V = 0x4,
	LVD_InputPositiveRefVolt_2P4V = 0x5,
	LVD_InputPositiveRefVolt_2P5V = 0x6,
	LVD_InputPositiveRefVolt_2P6V = 0x7,
	LVD_InputPositiveRefVolt_2P7V = 0x8,
	LVD_InputPositiveRefVolt_2P8V = 0x9,
	LVD_InputPositiveRefVolt_2P9V = 0xA,
	LVD_InputPositiveRefVolt_3P0V = 0xB,
	LVD_InputPositiveRefVolt_3P1V = 0xC,
	LVD_InputPositiveRefVolt_3P2V = 0xD,
	LVD_InputPositiveRefVolt_3P3V = 0xE,
	LVD_InputPositiveRefVolt_3P4V = 0xF

} LVD_InputPositiveRefVolt_TypeDef;

typedef enum
{
	LVD_FilterTime_25us = 0x0,
	LVD_FilterTime_50us = 0x1,
	LVD_FilterTime_100us = 0x2,
	LVD_FilterTime_400us = 0x3,
	LVD_FilterTime_1_6ms = 0x4,
	LVD_FilterTime_6ms = 0x5,
	LVD_FilterTime_25ms = 0x6,
	LVD_FilterTime_100ms = 0x7

} LVD_FilterTime_TypeDef;

typedef enum
{
	LVD_WarmUpResistance_High = 0x0,
	LVD_WarmUpResistance_Low = 0x1	

} LVD_WarmUpResistance_TypeDef;

typedef struct
{
	LVD_InputPositiveRefVolt_TypeDef LVD_InputPositiveRefVolt;
	LVD_InputNegative_TypeDef LVD_InputNegative;

	LVD_BiasCurrent_TypeDef LVD_BiasCurrent;
	LVD_WarmUpResistance_TypeDef LVD_WarmUpResistance;
	LVD_FilterTime_TypeDef LVD_FilterTime;

	LVD_OutputSignal_TypeDef LVD_OutputSignal;

} LVD_InitTypeDef;	

void LVD_StructInit(LVD_InitTypeDef* LVD_InitStruct);	 
void LVD_Init(LVD_InitTypeDef* LVD_InitStruct);

void LVD_Cmd(FunctionalState NewState);
void LVD_WarmUpCmd(FunctionalState NewState);
void LVD_HysteresisCmd(FunctionalState NewState);
void LVD_FilterCmd(FunctionalState NewState);

void LVD_ITConfig(uint16_t LVD_IntTrigSel, FunctionalState NewState);
ITStatus LVD_GetITStatus(void);	
void LVD_ClearITFlag(void);


#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_LVD_H */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
