/**
  ******************************************************************************
  * @file    GW32L0xx_rng.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_rng.h"

/**
	* @brief  Deinitialize RNG register to the reset value.
	*/
void RNG_DeInit(void)
{
	do
	{
		/* Restore RNG peripheral register to the reset value */
		PERI_RST_CTRL0 |= RMU_PERI_RESET0_RNG;
		
	} while ( (PERI_RST_CTRL0 & RMU_PERI_RESET0_RNG) != RMU_PERI_RESET0_RNG );
	
	/* Switch to work in normal mode */
	PERI_RST_CTRL0 &= ~RMU_PERI_RESET0_RNG;
}

/**
	* @brief  Initialize structure with the specified parameters.
	*/
void RNG_StructInit(RNG_InitTypeDef* RNG_InitStruct)
{
	RNG_InitStruct->RNG_LoadInitialValue = RNG_LoadInitialValue_Disable;
	RNG_InitStruct->RNG_FeedBack = RNG_FeedBack_Disable;
	RNG_InitStruct->RNG_FeedBackShiftCnt = RNG_FeedBackShiftCnt_64;
}

/**
	* @brief  Initialize RNG module according to the specified structure parameters.
	*/
void RNG_Init(RNG_InitTypeDef* RNG_InitStruct)
{
    volatile uint32_t tmpreg = 0, tmpreg0 = 0;
	
	tmpreg = RNG->CTRL;
	RNG->CTRL &= ~RNG_CTRL_RUN;

	tmpreg0 = RNG->MODE;
	tmpreg0 &= ~RNG_MODE_TRNG_LOAD;
	tmpreg0 |= RNG_InitStruct->RNG_LoadInitialValue;
	tmpreg0 &= ~RNG_MODE_TRNG_FDBK;
	tmpreg0 |= (RNG_InitStruct->RNG_FeedBack << 1);
	tmpreg0 &= ~RNG_MODE_TRNG_CNT;
	tmpreg0 |= (RNG_InitStruct->RNG_FeedBackShiftCnt << 2);	
	RNG->MODE = tmpreg0;

	RNG->CTRL = tmpreg;
}

/**
	* @brief  Enable or disbale RNG module.
	*/
void RNG_Cmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		do 
		{
			RNG->CTRL |= RNG_CTRL_RUN;
			
		} while ((RNG->CTRL & RNG_CTRL_RUN) != RNG_CTRL_RUN);
	}
	else
	{
		RNG->CTRL &= ~RNG_CTRL_RUN;		
	}
}

/**
	* @brief  Power on or power off the circuit of RNG.
	*/
void RNG_CircuitCmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		do 
		{
			RNG->CTRL |= RNG_CTRL_RNGCIR_EN;
			
		} while ((RNG->CTRL & RNG_CTRL_RNGCIR_EN) != RNG_CTRL_RNGCIR_EN);
	}
	else
	{
		RNG->CTRL &= ~RNG_CTRL_RNGCIR_EN;		
	}
}

/**
	* @brief  Get status of RNG completed flag.
	*/
FlagStatus RNG_GetCompletedFlagStatus(void)
{
	return (RNG->CTRL & RNG_CTRL_RUN) == RNG_CTRL_RUN ? RESET : SET;
}

/**
	* @brief  Get the random number of RNG.
	*/
uint64_t RNG_GetRandomNumber(void)
{
	uint64_t vBuff = RNG->DATA1;
	
	return ((uint64_t)vBuff << 32 | RNG->DATA0);
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
