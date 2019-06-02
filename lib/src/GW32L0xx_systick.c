/**
  ******************************************************************************
  * @file    GW32L0xx_systick.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_systick.h"

/**
  * @brief  Configures the SysTick clock source.
  * @param  SysTick_ClkSource: specifies the SysTick clock source.
  *   			This parameter can be one of the following values:
	*		@arg	SysTick_ClkSource_ExtRefClk_LSE: external reference clock LSE(32.768KHz) selected as SysTick clock source.
	*		@arg	SysTick_ClkSource_ExtRefClk_LSI: external reference clock LSI(38.5KHz) selected as SysTick clock source.
	*		@arg	SysTick_ClkSource_ExtRefClk_HSI: external reference clock HSI(2,4,8,16MHz) selected as SysTick clock source.
	*         if selected HSI as source, mustn't divisive all frequency, and HSI as system clock source.
	*		@arg	SysTick_ClkSource_ExtRefClk_HSE: external reference clock HSE(4...32MHz) selected as SysTick clock source.
  *         if selected HSE as source, may divisive frequency, and HSE as system clock source.	
  *   @arg  SysTick_CLKSource_SystemCoreClock: AHB clock(core clock or HCLK) selected as SysTick clock source.
  * @retval None
	*/
void SysTick_CLKSourceConfig(SysTick_ClkSource_TypeDef SysTick_ClkSource)
{
	if (SysTick_ClkSource != SysTick_CLKSource_SystemCoreClock)
	{
		SYSTICK_TIMER &= ~SYSTICK_TIMER_NOREF;
		
		SYSTICK_TIMER &= ~SYSTICK_TIMER_CLK_SEL;
		SYSTICK_TIMER |= SysTick_ClkSource << 26;
	}
	else
	{
		SYSTICK_TIMER |= SYSTICK_TIMER_NOREF;
	}
}

/**
	* @brief  Enable systick timer interrupt request.
	*/
void SysTick_ITConfig(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		SysTick->CTRL |=  SysTick_CTRL_TICKINT_Msk;
	}
	else
	{
		SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;	
	}
}

/**
	* @brief  Enable or disable systemtick timer.
	*/
void SysTick_Cmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	}
	else
	{
		SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;	
	}
}

/**
	* @brief  Get systick timer interrupt flag.
	*/
ITStatus SysTick_GetITStatus(void)
{
	return (SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == SysTick_CTRL_COUNTFLAG_Msk ? SET : RESET;
}

/**
	* @brief  Clear systick timer interrupt flag.
	*/
void SysTick_ClearITFlag(void)
{
	SysTick->CTRL = SysTick->CTRL;
}

/**
	* @brief  Set reload value of systemtick timer.
	*/
void SysTick_SetReloadValue(uint32_t SysTick_ReloadValue)
{
	SysTick->LOAD = (SysTick_ReloadValue & SysTick_LOAD_RELOAD_Msk);
}

/**
	* @brief  Get reload value of systemtick timer.
	*/
uint32_t SysTick_GetReloadValue(void)
{
	return SysTick->LOAD & SysTick_LOAD_RELOAD_Msk;
}

/**
	* @brief  Set current value of systemtick timer.
	*/
void SysTick_SetCurrentValue(uint32_t SysTick_ReloadValue)
{
	SysTick->VAL = (SysTick_ReloadValue & SysTick_VAL_CURRENT_Msk);
}

/**
	* @brief  Get current value of systemtick timer.
	*/
uint32_t SysTick_GetCurrentValue(void)
{
	return SysTick->VAL & SysTick_VAL_CURRENT_Msk;
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
