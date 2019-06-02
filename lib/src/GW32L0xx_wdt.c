/**
  ******************************************************************************
  * @file    GW32L0xx_wdt.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_wdt.h"

/**
	* @brief  Deinitialize WDT register to the reset value.
	*/
void WDT_DeInit(void)
{
	do
	{
		/* Restore WDT peripheral register to the reset value */
		PERI_RST_CTRL1 |= RMU_PERI_RESET1_WDT;
		
	} while ( (PERI_RST_CTRL1 & RMU_PERI_RESET1_WDT) != RMU_PERI_RESET1_WDT );
	
	/* Switch to work in normal mode */
	PERI_RST_CTRL1 &= ~RMU_PERI_RESET1_WDT;	
}

/**
	* @brief  Initialize structure with specified parameters.
	*/
void WDT_StructInit(WDT_InitTypeDef* WDT_InitStruct)
{
	WDT_InitStruct->WDT_TimeOverCycle = 0x0;
	WDT_InitStruct->WDT_RespMode = 	WDT_RespMode_Interrupt;
	WDT_InitStruct->WDT_RstPulseLen = WDT_RstPulseLen_2PClkCycles;	
}

/**
	* @brief  Initialize WDT module with specified structure parameters.
	*/
void WDT_Init(WDT_InitTypeDef* WDT_InitStruct)
{
    volatile uint32_t tmpreg = 0;
	
	tmpreg = WDT->CTRL;	
	WDT->CTRL &= ~WDT_CTRL_WDT_EN;
	
	WDT->TIMEOV = (WDT_InitStruct->WDT_TimeOverCycle & WDT_TIMEOV);
	
	tmpreg &= ~WDT_CTRL_RST_LEN;
	tmpreg |= (WDT_InitStruct->WDT_RstPulseLen << 2);
	tmpreg &= ~WDT_CTRL_RESP_MODE;
	tmpreg |= (WDT_InitStruct->WDT_RespMode << 1);
	
	WDT->CTRL = tmpreg;
}

/**
	* @brief  Enable or disable WDT module.
	*/
void WDT_Cmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		do
		{
			WDT->CTRL |= WDT_CTRL_WDT_EN;
			
		} while ( (WDT->CTRL & WDT_CTRL_WDT_EN) != WDT_CTRL_WDT_EN );
	}
	else
	{
		WDT->CTRL &= ~WDT_CTRL_WDT_EN;	
	}
}

/**
	* @brief  Restart WDT module.
	*/
void WDT_RestartCmd(FunctionalState NewState)
{
	volatile uint32_t tmp = 0x5AA53C3C;
	
	if (NewState != DISABLE)
	{
		if (tmp == 0x5AA53C3C)
		{
			WDT->RESTART = 0x76;
		}
	}
}

/**
	* @brief  Get status of WDT interrupt flag.
	*/
ITStatus WDT_GetITStatus(void)
{
	return (WDT->INTSTAT & WDT_INTSTAT) == WDT_INTSTAT ? SET : RESET;
}

/**
	* @brief  Clear WDT interrupt flag.
	*/
void WDT_ClearITFlag(void)
{	
	WDT->INTCLR = WDT->INTCLR;
}

/**
	* @brief  Get current value of WDT timer.
	*/
uint32_t WDT_GetCurrentWDTimer(void)
{
	return (WDT->CV & WDT_CV);
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
