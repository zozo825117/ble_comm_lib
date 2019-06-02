/**
  ******************************************************************************
  * @file    GW32L0xx_rtc.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the RTC
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW32L0XX_RTC_H
#define __GW32L0XX_RTC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

typedef enum
{
	RTC_HourFormat_12H = 0x0,
	RTC_HourFormat_24H = 0x1

} RTC_HourFormat_TypeDef;

typedef enum
{
	RTC_PulseFreq_0P5Sec = 0x0,
	RTC_PulseFreq_1Sec = 0x1,
	RTC_PulseFreq_2Sec = 0x2,
	RTC_PulseFreq_4Sec = 0x3,

} RTC_PulseFreq_TypeDef;

typedef enum
{
	RTC_PulseDutyRatio_8Cycles = 0x0,
	RTC_PulseDutyRatio_16Cycles = 0x1,
	RTC_PulseDutyRatio_32Cycles = 0x2,
	RTC_PulseDutyRatio_64Cycles = 0x3

} RTC_PulseDutyRatio_TypeDef;

typedef enum
{
	RTC_ITFlag_NO = 0x00,	
	RTC_ITFlag_MilliSecond = 0xE1,	
	RTC_ITFlag_SixteenOfOneSec = 0x01,
	RTC_ITFlag_Second	= 0x41,
	RTC_ITFlag_Minute = 0x81,
	RTC_ITFlag_Hour = 0xC1,	
	RTC_ITFlag_Day = 0x10,
	RTC_ITFlag_Month = 0x20,
	RTC_ITFlag_Year = 0x30

} RTC_ITFlag_TypeDef;

typedef enum
{
	RTC_TimeItemSel_Minute = 0x0,
	RTC_TimeItemSel_Hour = 0x1,
	RTC_TimeItemSel_Day = 0x2,
	RTC_TimeItemSel_Month = 0x3,
	RTC_TimeItemSel_Year = 0x4,
	RTC_TimeItemSel_Second = 0x5,
	RTC_TimeItemSel_SixteenOfSec = 0x6

} RTC_TimeItemSel_TypeDef;

typedef enum
{
	RTC_TimeDir_Inc = 0x0,
	RTC_TimeDir_Dec	= 0x1

} RTC_TimeDir_TypeDef;

typedef struct
{
	uint8_t RTC_SixteenOfSecond;
	uint8_t RTC_Second;
	uint8_t RTC_Minute;
	uint8_t RTC_Hour;
	uint8_t RTC_Day;
	uint8_t RTC_Month;
	uint8_t RTC_Six;
	uint16_t RTC_Year;	
	RTC_HourFormat_TypeDef RTC_HourFormat;

	RTC_PulseFreq_TypeDef RTC_Pulse0Freq;
	RTC_PulseDutyRatio_TypeDef RTC_Pulse0DutyRatio;
	RTC_PulseFreq_TypeDef RTC_Pulse1Freq;
	RTC_PulseDutyRatio_TypeDef RTC_Pulse1DutyRatio;
	uint8_t RTC_Pulse0Pulse1PhaseDiff;

} RTC_InitTypeDef;

void RTC_DeInit(void);
void RTC_StructInit(RTC_InitTypeDef* RTC_InitStruct);
void RTC_Init(RTC_InitTypeDef* RTC_InitStruct);
void RTC_Cmd(FunctionalState NewState);
void RTC_ResetCmd(FunctionalState NewState);

void RTC_ITConfig(RTC_ITFlag_TypeDef RTC_ITFlag, uint8_t ITInterval);
ITStatus RTC_GetITStatus(void);
void RTC_ClearITFlag(void);

void RTC_AdjustConfig(RTC_TimeItemSel_TypeDef RTC_TimeItemSel, RTC_TimeDir_TypeDef RTC_TimeDir);

uint8_t RTC_GetSixteenOfSecond(void);
uint8_t RTC_GetSecond(void);
uint8_t RTC_GetMinute(void);
uint8_t RTC_GetHour(void);
uint8_t RTC_GetDay(void);
uint8_t RTC_GetMonth(void);
uint8_t RTC_GetYearLSB(void);
uint8_t RTC_GetYearHSB(void);
uint16_t RTC_GetYear(void);	

#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_RTC_H */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
