/**
  ******************************************************************************
  * @file    GW32L0xx_lvd.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_lvd.h"

/**
	* @brief  Initialize structure with default value.
	*/
void LVD_StructInit(LVD_InitTypeDef* LVD_InitStruct)
{
	LVD_InitStruct->LVD_InputNegative = LVD_InputNegative_VCC;
	LVD_InitStruct->LVD_InputPositiveRefVolt = LVD_InputPositiveRefVolt_1P9V;
	
	LVD_InitStruct->LVD_BiasCurrent = LVD_BiasCurrent_80nA;
	LVD_InitStruct->LVD_WarmUpResistance = LVD_WarmUpResistance_High;	
	LVD_InitStruct->LVD_FilterTime = LVD_FilterTime_25us;
	
	LVD_InitStruct->LVD_OutputSignal = LVD_OutputSignal_Interrupt;
}

/**
	* @brief  Initialize LVD module with specified structure parameters.
	*/
void LVD_Init(LVD_InitTypeDef* LVD_InitStruct)
{
    volatile uint32_t tmpreg = 0, tmpreg0 = 0;
	
	tmpreg0 = LVD_CTRL0;
	LVD_CTRL0 &= ~LVD_CTRL0_LVDEN;

	tmpreg = LVD_CTRL1;
	tmpreg &= ~LVD_CTRL1_LEVEL;
	tmpreg |= (LVD_InitStruct->LVD_InputPositiveRefVolt << 4);
	tmpreg &= ~LVD_CTRL1_FLT;
	tmpreg |= (LVD_InitStruct->LVD_FilterTime << 1);
	LVD_CTRL1 = tmpreg;

	tmpreg0 &= ~LVD_CTRL0_WARMUPFAST;
	tmpreg0 |= (LVD_InitStruct->LVD_WarmUpResistance << 6);
	tmpreg0 &= ~LVD_CTRL0_VSEL;
	tmpreg0 |= (LVD_InitStruct->LVD_InputNegative << 3);
	tmpreg0 &= ~LVD_CTRL0_RST;
	tmpreg0 |= (LVD_InitStruct->LVD_OutputSignal << 2);
	LVD_CTRL0 = tmpreg0;
	
	do
	{
		volatile uint16_t num = 16 * 30;
		
		LVD_CTRL1 &= ~LVD_CTRL1_BIASCTRL;
		LVD_CTRL1 |= (LVD_InitStruct->LVD_BiasCurrent << 8);
		while (num--);
		
	} while ((LVD_CTRL1 & LVD_CTRL1_BIASCTRL) != (LVD_InitStruct->LVD_BiasCurrent << 8));
}

/**
	* @brief  Enable or disable LVD module.
	*/
void LVD_Cmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		do 
		{		
			volatile uint16_t num = 16 * 30;
				
			LVD_CTRL0 |= LVD_CTRL0_LVDEN;
			while (num--);
			
		} while ((LVD_CTRL0 & LVD_CTRL0_LVDEN) != LVD_CTRL0_LVDEN);			
	}
	else
	{
		LVD_CTRL0 &= ~LVD_CTRL0_LVDEN;	
	}
}

/**
	* @brief  Enable or disable divider resistance.
	*/
void LVD_WarmUpCmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		do
		{
			volatile uint16_t num = 16 * 1000;
			
			LVD_CTRL0 |= LVD_CTRL0_WARMUPEN;
			while (num--);
			
		} while ((LVD_CTRL0 & LVD_CTRL0_WARMUPEN) != LVD_CTRL0_WARMUPEN);
		
	}
	else
	{
		LVD_CTRL0 &= ~LVD_CTRL0_WARMUPEN;
	}
}

/**
	* @brief  Enable or disable Hysteresis function.
	*/
void LVD_HysteresisCmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		do 
		{
			volatile uint16_t num = 16 * 30;
			
			LVD_CTRL0 |= LVD_CTRL0_HYST;
			while (num--);
			
		} while ((LVD_CTRL0 & LVD_CTRL0_HYST) != LVD_CTRL0_HYST);
	}
	else
	{
		LVD_CTRL0 &= ~LVD_CTRL0_HYST;
	}
}

/**
	* @brief  Enable or filter resistance
	*/
void LVD_FilterCmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		LVD_CTRL1 |= LVD_CTRL1_FLTEN;
	}
	else
	{
		LVD_CTRL1 &= ~LVD_CTRL1_FLTEN;
	}
}

/**
	* @brief  Configurate to select which to trigge interrupt.
	* @param  LVD_IntTrigSel, as follow:
	*		@arg  LVD_IntTrigSel_NO
	*		@arg  LVD_IntTrigSel_Level                
	*		@arg  LVD_IntTrigSel_Edge_Rising          	
	*		@arg  LVD_IntTrigSel_Edge_Falling					
	*/
void LVD_ITConfig(uint16_t LVD_IntTrigSel, FunctionalState NewState)
{	
	volatile uint32_t tmpreg = LVD_CTRL0;
		
	tmpreg &= ~(LVD_CTRL0_INTL | LVD_CTRL0_INTPOS | LVD_CTRL0_INTNEG);
	
	if (NewState != DISABLE)
	{
		tmpreg |= LVD_IntTrigSel;
	}
	
	LVD_CTRL0 = tmpreg;
}

/**
	* @brief  Get status of LVD interrupt flag.
	*/
ITStatus LVD_GetITStatus(void)
{
	return ( (LVD_CTRL0 & LVD_CTRL0_LVDINT) != LVD_CTRL0_LVDINT ) ? SET : RESET;
}

/**
	* @brief  Clear interrupt flag of LVD.
	*/
void LVD_ClearITFlag(void)
{
	LVD_CTRL0 &= ~LVD_CTRL0_LVDINT;
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
