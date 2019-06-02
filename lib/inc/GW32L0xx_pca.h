/**
  ******************************************************************************
  * @file    GW32L0xx_pca.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the PCA
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW32L0XX_PCA_H
#define __GW32L0XX_PCA_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

typedef enum
{
	PCA_Mode_NO = 0x0,
	PCA_Mode_CT = 0x1,
	PCA_Mode_CMP = 0x2,
	PCA_Mode_CAP = 0x3

} PCA_Mode_TypeDef;

typedef enum
{
PCA_WdTimer_Disable = 0x0,
PCA_WdTimer_Enable = 0x1

} PCA_WdTimer_TypeDef;

typedef enum
{
	PCA_Comparer_Disable = 0x0,
	PCA_Comparer_Enable = 0x1

}	PCA_Comparer_TypeDef;

typedef enum
{
	PCA_Matcher_Disable = 0x0,
	PCA_Matcher_Enable = 0x1

} PCA_Matcher_TypeDef;

typedef enum
{
	PCA_CaptToggle_Disable = 0x0,
	PCA_CaptToggle_Enable = 0x1

} PCA_CaptToggle_TypeDef;

typedef enum
{
	PCA_CaptToggleEdge_NO = 0x0,
	PCA_CaptToggleEdge_Falling = 0x1,	
	PCA_CaptToggleEdge_Rising = 0x2,
	PCA_CaptToggleEdge_Falling_Rising = 0x3

} PCA_CaptToggleEdge_TypeDef;

typedef enum
{
	PCA_PWM_Disable = 0x0,
	PCA_PWM_Enable = 0x1

} PCA_PWM_TypeDef;

typedef enum
{
	PCA_CntClkSel_1_64PCLK = 0x0,
	PCA_CntClkSel_1_32PCLK = 0x1,
	PCA_CntClkSel_1_16PCLK = 0x2,
	PCA_CntClkSel_1_8PCLK = 0x3,
	PCA_CntClkSel_1_4PCLK = 0x4,
	PCA_CntClkSel_1_2PCLK = 0x5,
	PCA_CntClkSel_TIMERxOV = 0x6,
	PCA_CntClkSel_ExtClk = 0x7

} PCA_CntClkSel_TypeDef;

typedef enum
{
	PCA_ITFlag_CCF0 = 0x1,
	PCA_ITFlag_CCF1 = 0x2,
	PCA_ITFlag_CCF2 = 0x4,
	PCA_ITFlag_CCF3 = 0x8,
	PCA_ITFlag_CCF4 = 0x10,
	PCA_ITFlag_CF = 0x80,
	PCA_ITFlag_ALL = 0x9F	

} PCA_ITFlag_TypeDef;

typedef enum
{
	PCA_CCAPMSel_CCAP0 = 0x0,
	PCA_CCAPMSel_CCAP1 = 0x1,
	PCA_CCAPMSel_CCAP2 = 0x2,
	PCA_CCAPMSel_CCAP3 = 0x3,
	PCA_CCAPMSel_CCAP4 = 0x4,
	PCA_CCAPMSel_NO = 0x5

} PCA_CCAPMSel_TypeDef;

typedef enum
{
	PCA_CmpMode_NO = 0x0,
	PCA_CmpMode_SWCounter = 0x1,
	PCA_CmpMode_HSOutput = 0x2,
	PCA_CmpMode_WDT = 0x3,
	PCA_CmpMode_PWM	= 0x4

} PCA_CmpMode_TypeDef;

typedef enum
{
	PCA_CCAPOPolarity_Low = 0x0,
	PCA_CCAPOPolarity_High = 0x1

} PCA_CCAPOPolarity_TypeDef;

typedef struct
{
	PCA_Mode_TypeDef PCA_Mode;

	PCA_CntClkSel_TypeDef PCA_CntClkSel;

	PCA_CCAPMSel_TypeDef PCA_CCAPMSel;

	PCA_CaptToggleEdge_TypeDef PCA_CaptToggleEdge;

	PCA_CmpMode_TypeDef PCA_CmpMode;

} PCA_InitTypeDef;


void PCA_DeInit(PCA_TypeDef* PCAx);
void PCA_StructInit(PCA_InitTypeDef* PCA_InitStruct);
void PCA_Init(PCA_TypeDef* PCAx, PCA_InitTypeDef* PCA_InitStruct);
void PCA_Cmd(PCA_TypeDef* PCAx, FunctionalState NewState);
void PCA_ITConfig(PCA_TypeDef* PCAx, PCA_ITFlag_TypeDef PCA_ITFlag, FunctionalState NewState);

ITStatus PCA_GetITStatus(PCA_TypeDef* PCAx, PCA_ITFlag_TypeDef PCA_ITFlag);
void PCA_ClearITFlag(PCA_TypeDef* PCAx, PCA_ITFlag_TypeDef PCA_ITFlag);

void PCA_SetCounterHSB(PCA_TypeDef* PCAx, uint8_t CounterHSB);
void PCA_SetCounterLSB(PCA_TypeDef* PCAx, uint8_t CounterLSB);

uint8_t PCA_GetCounterHSB(PCA_TypeDef* PCAx);
uint8_t PCA_GetCounterLSB(PCA_TypeDef* PCAx);
uint16_t PCA_GetCounter(PCA_TypeDef* PCAx);

void PCA_SetCapturerLSB(PCA_TypeDef* PCAx, PCA_CCAPMSel_TypeDef PCA_CCAPMSel, uint8_t CapturerLSB);
void PCA_SetCapturerHSB(PCA_TypeDef* PCAx, PCA_CCAPMSel_TypeDef PCA_CCAPMSel, uint8_t CapturerHSB);

uint8_t PCA_GetCapturerLSB(PCA_TypeDef* PCAx, PCA_CCAPMSel_TypeDef PCA_CCAPMSel);
uint8_t PCA_GetCapturerHSB(PCA_TypeDef* PCAx, PCA_CCAPMSel_TypeDef PCA_CCAPMSel);
uint16_t PCA_GetCapturer(PCA_TypeDef* PCAx, PCA_CCAPMSel_TypeDef PCA_CCAPMSel);

void PCA_CCAPOPolarityConfig(PCA_TypeDef* PCAx, PCA_CCAPMSel_TypeDef PCA_CCAPMSel, PCA_CCAPOPolarity_TypeDef PCA_CCAPOPolarity);


#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_PCA_H */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
