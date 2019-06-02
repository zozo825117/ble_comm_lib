/**
  ******************************************************************************
  * @file    GW32L0xx_rtc.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_rtc.h"

/**
	* @brief  Deinitialize RTC module to configurate RTC register reset value.
	*/
void RTC_DeInit(void)
{
	do
	{
		/* Restore RTC peripheral register to the reset value */
		PERI_RST_CTRL1 |= RMU_PERI_RESET1_RTC;
		
	} while ( (PERI_RST_CTRL1 & RMU_PERI_RESET1_RTC) != RMU_PERI_RESET1_RTC );
	
	/* Switch to work in normal mode */
	PERI_RST_CTRL1 &= ~RMU_PERI_RESET1_RTC;	
}

/**
	* @brief  Initialize RTC_InitStruct point to RTC_InitStruct 
  *         pointer type according to specified parameters.
	*/
void RTC_StructInit(RTC_InitTypeDef* RTC_InitStruct)
{
	RTC_InitStruct->RTC_SixteenOfSecond = 0x0;
	RTC_InitStruct->RTC_Second = 0x0;
	RTC_InitStruct->RTC_Minute = 0x0;
	RTC_InitStruct->RTC_Hour = 0x0;
	RTC_InitStruct->RTC_Day = 0x0;
	RTC_InitStruct->RTC_Month = 0x0;
	RTC_InitStruct->RTC_Year = 0x0;
	
	RTC_InitStruct->RTC_HourFormat = RTC_HourFormat_24H;
	
	RTC_InitStruct->RTC_Pulse0Freq = RTC_PulseFreq_0P5Sec;
	RTC_InitStruct->RTC_Pulse0DutyRatio = RTC_PulseDutyRatio_8Cycles;
	RTC_InitStruct->RTC_Pulse1Freq = RTC_PulseFreq_0P5Sec;
	RTC_InitStruct->RTC_Pulse1DutyRatio = RTC_PulseDutyRatio_8Cycles;
	RTC_InitStruct->RTC_Pulse0Pulse1PhaseDiff = 0x0;
}

/**
	* @brief  Initialize RTC module according to specified parameters as RTC_InitStruct.
	*/
void RTC_Init(RTC_InitTypeDef* RTC_InitStruct)
{
    volatile uint32_t tmpreg = 0;
	
	do 
	{
		volatile uint16_t num = 16 * 60;
		
		RTC->HOLD = 0x1;
		RTC->RTCRST = 0x0;
		RTC->RTCRST = 0x1;

		while (num--);
		
	} while (RTC->RTCRST != 0x1);
	
	RTC->SIXTEENOFS = (RTC_InitStruct->RTC_SixteenOfSecond & RTC_SIXTEENOFSECOND);
	RTC->SECOND = (RTC_InitStruct->RTC_Second & RTC_SECOND);
	RTC->MINUTE = (RTC_InitStruct->RTC_Minute & RTC_MINUTE);
	RTC->HOUR = (RTC_InitStruct->RTC_Hour & RTC_HOUR);
	RTC->DAY = (RTC_InitStruct->RTC_Day & RTC_DAY);
	RTC->MONTH = (RTC_InitStruct->RTC_Month & RTC_MONTH);
	RTC->YEARL = (uint8_t)(RTC_InitStruct->RTC_Year & RTC_YEAR_L);
	RTC->YEARH = (uint8_t)((RTC_InitStruct->RTC_Year >> 8) & RTC_YEAR_H);
	
	RTC->FORMAT = RTC_InitStruct->RTC_HourFormat;
	
	tmpreg = RTC->CONFIG0;
	tmpreg &= ~RTC_CONF0_P0F;
	tmpreg |= (RTC_InitStruct->RTC_Pulse0Freq << 2);
	tmpreg &= ~RTC_CONF0_P0D;
	tmpreg |= RTC_InitStruct->RTC_Pulse0DutyRatio;	
	RTC->CONFIG0 = tmpreg;
	
	tmpreg = RTC->CONFIG1;
	tmpreg &= ~RTC_CONF1_P1F;
	tmpreg |= (RTC_InitStruct->RTC_Pulse1Freq << 2);
	tmpreg &= ~RTC_CONF1_P1D;
	tmpreg |= RTC_InitStruct->RTC_Pulse1DutyRatio;	
	RTC->CONFIG1 = tmpreg;
	
	RTC->PHASE = (RTC_InitStruct->RTC_Pulse0Pulse1PhaseDiff & RTC_PHASE);
}

/**
	* @brief  Enable or disable RTC module.
	*/
void RTC_Cmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		RTC->HOLD &= ~RTC_HOLD;
	}
	else
	{
		RTC->HOLD |= RTC_HOLD;	
	}
}

/**
	* @brief  Reset RTC module.
	*/
void RTC_ResetCmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		RTC->RTCRST &= ~RTC_RESET;
	}
	else
	{
		RTC->RTCRST |= RTC_RESET;
	}	
}

/**
	* @brief  Configurate interrupt flag to be enabled or disabled status.
	*/
void RTC_ITConfig(RTC_ITFlag_TypeDef RTC_ITFlag, uint8_t ITInterval)
{
	switch (RTC_ITFlag)
	{
		case RTC_ITFlag_MilliSecond:			
			RTC->INTERVAL = (uint8_t)((RTC_ITFlag_MilliSecond - 1) | ITInterval);	
			break;
		case RTC_ITFlag_SixteenOfOneSec:
			RTC->INTERVAL = (uint8_t)((RTC_ITFlag_SixteenOfOneSec - 1) | ITInterval);			
			break;
		case RTC_ITFlag_Second:
			RTC->INTERVAL = (uint8_t)((RTC_ITFlag_Second - 1) | ITInterval);
			break;
		case RTC_ITFlag_Minute:
			RTC->INTERVAL = (uint8_t)((RTC_ITFlag_Minute - 1) | ITInterval);
			break;
		case RTC_ITFlag_Hour:
			RTC->INTERVAL = (uint8_t)((RTC_ITFlag_Hour - 1) | ITInterval);
			break;
		case RTC_ITFlag_Day:
			RTC->INTERVAL = (uint8_t)(RTC_ITFlag_Day | ITInterval);
			break;
		case RTC_ITFlag_Month:
			RTC->INTERVAL = (uint8_t)(RTC_ITFlag_Month | ITInterval);
			break;
		case RTC_ITFlag_Year:
			RTC->INTERVAL = (uint8_t)(RTC_ITFlag_Year | ITInterval);
			break;		
		default:
			RTC->INTERVAL = RTC_ITFlag_NO;			
			break;
	}
}

/**
	* @brief  Get status of RTC relevant interrupt flag.
	*/
ITStatus RTC_GetITStatus(void)
{
	return (RTC->RTCINT & RTC_INT) == RTC_INT ? SET : RESET;
}

/**
	* @brief  Clear RTC relevant interrupt flag.
	*/
void RTC_ClearITFlag(void)
{
	RTC->RTCINT |= RTC_INT;
}

/**
	* @brief  Adajust value of RTC relevant setting.
	*
	* @param  RTC_TimeItemSel:
	*		@arg  RTC_TimeItemSel_Minute
	*		@arg  RTC_TimeItemSel_Hour
	*		@arg  RTC_TimeItemSel_Day
	*		@arg  RTC_TimeItemSel_Month
	*		@arg  RTC_TimeItemSel_Year
	*		@arg  RTC_TimeItemSel_Second
	*		@arg  RTC_TimeItemSel_SixteenOfSec
	*
	* @param  RTC_TimeDir:
	*		@arg  RTC_TimeDir_Inc
	*		@arg  RTC_TimeDir_Dec
	*/
void RTC_AdjustConfig(RTC_TimeItemSel_TypeDef RTC_TimeItemSel, RTC_TimeDir_TypeDef RTC_TimeDir)
{
	if (RTC_TimeDir != RTC_TimeDir_Dec)
	{
		RTC->ADJUST_INC = (0x1 << RTC_TimeItemSel);
	}
	else
	{
		RTC->ADJUST_DEC = (0x1 << RTC_TimeItemSel);
	}
}

/**
	* @brief  Get current value of sixteenofSecond.
	*/
uint8_t RTC_GetSixteenOfSecond(void)
{
	return RTC->SIXTEENOFS_DIS & RTC_SIXTEENOFSEC_DIS;
}

/**
	* @brief  Get current value of Second.
	*/
uint8_t RTC_GetSecond(void)
{
	return RTC->SECOND_DIS & RTC_SECOND_DIS;
}

/**
	* @brief  Get current value of Minute.
	*/
uint8_t RTC_GetMinute(void)
{
	return RTC->MINUTE_DIS & RTC_MINUTE_DIS;
}

/**
	* @brief  Get current value of Hour.
	*/
uint8_t RTC_GetHour(void)
{
	return RTC->HOUR_DIS & RTC_HOUR_DIS;
}

/**
	* @brief  Get current value of Day.
	*/
uint8_t RTC_GetDay(void)
{
	return RTC->DAY_DIS & RTC_DAY_DIS;
}

/**
	* @brief  Get current value of Month.
	*/
uint8_t RTC_GetMonth(void)
{
	return RTC->MONTH_DIS & RTC_MONTH_DIS;
}

/**
	* @brief  Get current LSB value of Year.
	*/
uint8_t RTC_GetYearLSB(void)
{
	return RTC->YEARL_DIS & RTC_YEAR_L_DIS;
}

/**
	* @brief  Get current HSB value of Year.
	*/
uint8_t RTC_GetYearHSB(void)
{
	return RTC->YEARH_DIS & RTC_YEAR_H_DIS;
}

/**
	* @brief  Get current value of Year.
	*/
uint16_t RTC_GetYear(void)
{
	uint32_t vBuff = RTC->YEARH_DIS;
	
	return (vBuff << 8 | RTC->YEARL_DIS) & 0xFFFF ;
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
