/**
  ******************************************************************************
  * @file    GW32L0xx_buzzer.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_buzzer.h"

/**
	* @brief  Deinitialize BUZZER register to the reset value.
	*/
void BUZZER_DeInit(void)
{
	do
	{
		/* Restore BUZZER peripheral register to the reset value */
		PERI_RST_CTRL0 |= RMU_PERI_RESET0_BUZZER;
		
	} while ( (PERI_RST_CTRL0 & RMU_PERI_RESET0_BUZZER) != RMU_PERI_RESET0_BUZZER );
	
	/* Switch to work in normal mode */
	PERI_RST_CTRL0 &= ~RMU_PERI_RESET0_BUZZER;
}

/**
	* @brief  Initialize structure with specified parameters.
	*/
void BUZZER_StructInit(BUZZER_InitTypeDef* BUZZER_InitStruct)
{
	BUZZER_InitStruct->BUZZER_ClkSel = BUZZER_ClkSel_HCLK;
	BUZZER_InitStruct->BUZZER_FreqAdjustDivisor = 0x0;
}

/**
	* @brief  Initialize BUZZER module with specified structure parameters.
	*/
void BUZZER_Init(BUZZER_InitTypeDef* BUZZER_InitStruct)
{
    volatile uint32_t tmpreg = 0;
	
	tmpreg = BUZZER;	
	BUZZER &= ~BUZZER_CTRL_BUZEN;
	
	tmpreg &= ~BUZZER_CTRL_BUZCLK;
	tmpreg |= (BUZZER_InitStruct->BUZZER_ClkSel << 1);
	tmpreg &= ~BUZZER_CTRL_N;
	tmpreg |= (BUZZER_InitStruct->BUZZER_FreqAdjustDivisor << 3);
	
	BUZZER = tmpreg;
}

/**
	* @brief  Enable or disable BUZZER module.
	*/
void BUZZER_Cmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		do
		{
			BUZZER |= BUZZER_CTRL_BUZEN;
			
		} while ( (BUZZER & BUZZER_CTRL_BUZEN) != BUZZER_CTRL_BUZEN );
	}
	else
	{
		BUZZER &= ~BUZZER_CTRL_BUZEN;
	}
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
