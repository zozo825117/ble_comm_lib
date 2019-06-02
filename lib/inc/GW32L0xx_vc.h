/**
  ******************************************************************************
  * @file    GW32L0xx_vc.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the VC
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW32L0XX_VC_H
#define __GW32L0XX_VC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

#define VC_IntTrigSel_NO                   	(0x0)
#define VC_IntTrigSel_Level_High            VC_CTRL1_INTL
#define VC_IntTrigSel_Edge_Rising          	VC_CTRL1_INTPOS
#define VC_IntTrigSel_Edge_Falling          VC_CTRL1_INTNEG	

typedef enum
{
	VC_InputPositiveSel_PORT0_Pin_0 = 0x0,
	VC_InputPositiveSel_PORT0_Pin_1 = 0x1,
	VC_InputPositiveSel_PORT0_Pin_2 = 0x2,
	VC_InputPositiveSel_PORT0_Pin_3 = 0x3,
	VC_InputPositiveSel_PORT0_Pin_4 = 0x4,
	VC_InputPositiveSel_PORT0_Pin_5 = 0x5,
	VC_InputPositiveSel_PORT0_Pin_6 = 0x6,
	VC_InputPositiveSel_PORT0_Pin_7 = 0x7

} VC_InputPositiveSel_TypeDef;

typedef enum
{
	VC_InputNegativeSel_PORT0_Pin_0 = 0x0,
	VC_InputNegativeSel_PORT0_Pin_1 = 0x1,
	VC_InputNegativeSel_PORT0_Pin_2 = 0x2,
	VC_InputNegativeSel_PORT0_Pin_3 = 0x3,
	VC_InputNegativeSel_PORT0_Pin_4 = 0x4,
	VC_InputNegativeSel_PORT0_Pin_5 = 0x5,
	VC_InputNegativeSel_PORT0_Pin_6 = 0x6,
	VC_InputNegativeSel_PORT0_Pin_7 = 0x7,
	VC_InputNegativeSel_Scaler = 0x8,
	VC_InputNegativeSel_TS = 0x9,
	VC_InputNegativeSel_BGR1P2V = 0xB,
	VC_InputNegativeSel_BGR2P5V = 0xC

} VC_InputNegativeSel_TypeDef;

typedef enum
{
	VC_BiasCurrentSel_160nA = 0x0,
	VC_BiasCurrentSel_1P28uA = 0x1,
	VC_BiasCurrentSel_10uA = 0x2,
	VC_BiasCurrentSel_80uA = 0x3

} VC_BiasCurrentSel_TypeDef;

typedef enum
{
	VC_FilterTime_25us = 0x0,
	VC_FilterTime_50us = 0x1,
	VC_FilterTime_100us = 0x2,
	VC_FilterTime_400us = 0x3,
	VC_FilterTime_1P6ms = 0x4,
	VC_FilterTime_6ms = 0x5,
	VC_FilterTime_25ms = 0x6,
	VC_FilterTime_100ms = 0x7

} VC_FilterTime_TypeDef;

typedef struct
{
	VC_InputPositiveSel_TypeDef VC_InputPositiveSel;
	VC_InputNegativeSel_TypeDef VC_InputNegativeSel;
	VC_BiasCurrentSel_TypeDef	VC_BiasCurrentSel;
	uint16_t VC_VCCScalerLevel;
	VC_FilterTime_TypeDef VC_FilterTime;

} VC_InitTypeDef;	

void VC_StructInit(VC_InitTypeDef* VC_InitStruct);	 
void VC_Init(VC_InitTypeDef* VC_InitStruct);

void VC_Cmd(FunctionalState NewState);
void VC_VCCScalerCmd(FunctionalState NewState);
void VC_BGRCmd(FunctionalState NewState);
void VC_FilterCmd(FunctionalState NewState);

void VC_ITConfig(uint16_t VC_IntTrigSel, FunctionalState NewState);
ITStatus VC_GetITStatus(void);	
void VC_ClearITFlag(void);


#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_VC_H */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
