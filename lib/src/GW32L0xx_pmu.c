/**
  ******************************************************************************
  * @file    GW32L0xx_pmu.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_pmu.h"

/**
	* @brief  Core enter into idle mode. 
	*/
void PMU_EnterSleepMode(PMU_EnterMode_TypeDef PMU_EnterSleep)
{
  /* Enter Cortex sleep mode */
  SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;

	if (PMU_EnterSleep != PMU_EnterMode_Now)
	{
		SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
	}
	else
	{
		SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
		__WFI();		
	}	
}

/**
	* @brief  Core enter into deepsleep mode, and close high speed clock. 
	*/
void PMU_EnterDeepSleep3Mode(PMU_EnterMode_TypeDef PMU_EnterDeepSleep3)
{
  /* Enter Cortex deep sleep mode */
	/* After entering deep sleep, HSF clock will automatically close */	
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

	if (PMU_EnterDeepSleep3 != PMU_EnterMode_Now)
	{
		SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
	}
	else
	{
		SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
		__WFI();		
	}	
}

/**
	* @brief  Core enter into deepsleep mode, and close all clock. 
	*/
void PMU_EnterDeepSleep4Mode(PMU_EnterMode_TypeDef PMU_EnterDeepSleep4)
{
  /* Enter Cortex deep sleep mode */
	/* After entering deep sleep, all HSF clock will automatically close */	
  SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
	
	/* Close all LSF clock */
	SYSCLK0 &= ~(CMU_SYSCLK0_XLF_EN | CMU_SYSCLK0_IRC38K_EN);

	if (PMU_EnterDeepSleep4 != PMU_EnterMode_Now)
	{
		SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
	}
	else
	{
		SCB->SCR &= ~SCB_SCR_SLEEPONEXIT_Msk;
		__WFI();		
	}	
}

/**
	* @brief  Core enter into powerdown mode, and close high speed clock. 
	*/
void PMU_EnterPowerDown3Mode(void)
{
    volatile uint32_t tmp = 0;
	
	do
	{
		tmp = 0x5AA5C33C;
		
		/* Enter power down mode */
		PMU_CTRL = 0x9876;
		PMU_CTRL = 0xCDEF;
	
	} while (tmp != 0x5AA5C33C);
}

/**
	* @brief  Core enter into powerdown mode, and close all clock. 
	*/
void PMU_EnterPowerDown4Mode(void)
{
    volatile uint32_t tmp = 0;
	
	/* Close all LSF clock */
	SYSCLK0 &= ~(CMU_SYSCLK0_XLF_EN | CMU_SYSCLK0_IRC38K_EN);
	
	do
	{
		tmp = 0x5AA5C33C;

		/* Enter power down mode */		
		PMU_CTRL = 0x9876;
		PMU_CTRL = 0xCDEF;
	
	} while (tmp != 0x5AA5C33C);
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
