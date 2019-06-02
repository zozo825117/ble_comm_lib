/**
  ******************************************************************************
  * @file    GW32L0xx_rng.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the RNG
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW32L0XX_RNG_H
#define __GW32L0XX_RNG_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

typedef enum
{
	RNG_FeedBackShiftCnt_0 = 0x0,
	RNG_FeedBackShiftCnt_8 = 0x1,
	RNG_FeedBackShiftCnt_16 = 0x2,
	RNG_FeedBackShiftCnt_32 = 0x3,
	RNG_FeedBackShiftCnt_64 = 0x4,
	RNG_FeedBackShiftCnt_128 = 0x5,
	RNG_FeedBackShiftCnt_256 = 0x6

} RNG_FeedBackShiftCnt_TypeDef;

typedef enum
{
	RNG_FeedBack_Disable = 0x0,
	RNG_FeedBack_Enable = 0x1

} RNG_FeedBack_TypeDef;

typedef enum
{
	RNG_LoadInitialValue_Disable = 0x0,
	RNG_LoadInitialValue_Enable = 0x1

} RNG_LoadInitialValue_TypeDef;

typedef struct
{
	RNG_LoadInitialValue_TypeDef RNG_LoadInitialValue;	
	RNG_FeedBack_TypeDef RNG_FeedBack;
	RNG_FeedBackShiftCnt_TypeDef RNG_FeedBackShiftCnt;

} RNG_InitTypeDef;

void RNG_DeInit(void);
void RNG_StructInit(RNG_InitTypeDef* RNG_InitStruct);
void RNG_Init(RNG_InitTypeDef* RNG_InitStruct);

void RNG_Cmd(FunctionalState NewState);
void RNG_CircuitCmd(FunctionalState NewState);

FlagStatus RNG_GetCompletedFlagStatus(void);

uint64_t RNG_GetRandomNumber(void);

#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_RNG_H */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
