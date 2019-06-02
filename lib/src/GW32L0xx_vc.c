/**
  ******************************************************************************
  * @file    GW32L0xx_vc.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_vc.h"

/**
	* @brief  Initialize VC structure according to specified parameters.
	*/
void VC_StructInit(VC_InitTypeDef* VC_InitStruct)
{
	VC_InitStruct->VC_InputPositiveSel = VC_InputPositiveSel_PORT0_Pin_0;
	VC_InitStruct->VC_InputNegativeSel = VC_InputNegativeSel_PORT0_Pin_0;
	VC_InitStruct->VC_VCCScalerLevel = 0x00;
	
	VC_InitStruct->VC_BiasCurrentSel = VC_BiasCurrentSel_160nA;
	
	VC_InitStruct->VC_FilterTime = VC_FilterTime_25us;	
}

/**
	* @brief  Initialize VC module according to specified structure parameters.
	*/
void VC_Init(VC_InitTypeDef* VC_InitStruct)
{
    volatile uint32_t tmpreg = 0, tmpreg0 = 0;
	
	tmpreg0 = VC_CTRL0;
	VC_CTRL0 &= ~VC_CTRL0_VCEN;

	tmpreg = VC_CTRL1;
	tmpreg &= ~VC_CTRL1_VCCLEVEL;
	tmpreg |= (VC_InitStruct->VC_VCCScalerLevel << 6);
	tmpreg &= ~VC_CTRL1_FLT;
	tmpreg |= (VC_InitStruct->VC_FilterTime << 1);
	VC_CTRL1 = tmpreg;
	
	tmpreg0 &= ~(VC_CTRL0_TM1GE | VC_CTRL0_TM1G | VC_CTRL0_TM0GE | VC_CTRL0_TM0G);
	tmpreg0 &= ~VC_CTRL0_INPSEL;
	tmpreg0 |= (VC_InitStruct->VC_InputPositiveSel << 8);
	tmpreg0 &= ~VC_CTRL0_INNSEL;
	tmpreg0 |= (VC_InitStruct->VC_InputNegativeSel << 4);
	VC_CTRL0 = tmpreg0;
	
	do
	{
		volatile uint16_t num = 16 * 30;
		
		VC_CTRL0 &= ~VC_CTRL0_BIASCTRL;
		VC_CTRL0 |= (VC_InitStruct->VC_BiasCurrentSel << 2);
		while (num--);
		
	} while ((VC_CTRL0 & VC_CTRL0_BIASCTRL) != (VC_InitStruct->VC_BiasCurrentSel << 2));
}

/**
	* @brief  Enable or disable VC module.
	*/
void VC_Cmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		do 
		{		
			volatile uint16_t num = 16 * 30;
				
			VC_CTRL0 |= VC_CTRL0_VCEN;
			while (num--);
			
		} while ((VC_CTRL0 & VC_CTRL0_VCEN) != VC_CTRL0_VCEN);			
	}
	else
	{
		VC_CTRL0 &= ~VC_CTRL0_VCEN;	
	}
}

/**
	* @brief  Enable VCC scaler module, or make DAC for VC as negative referring voltage.
	*/
void VC_VCCScalerCmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		do
		{
			volatile uint16_t num = 16 * 30;
			
			VC_CTRL1 |= VC_CTRL1_SCALEREN;
			while (num--);
			
		} while ((VC_CTRL1 & VC_CTRL1_SCALEREN) != VC_CTRL1_SCALEREN);
		
	}
	else
	{
		VC_CTRL1 &= ~VC_CTRL1_SCALEREN;
	}
}

/**
	* @brief  Support internal BGR(1.2V or 2.5V) for VC as negative referring voltage.
	*/
void VC_BGRCmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		do 
		{
			volatile uint16_t num = 16 * 30;
			
			VC_CTRL1 |= VC_CTRL1_V2P5EN;
			while (num--);
			
		} while ((VC_CTRL1 & VC_CTRL1_V2P5EN) != VC_CTRL1_V2P5EN);
	}
	else
	{
		VC_CTRL1 &= ~VC_CTRL1_V2P5EN;
	}
}

/**
	* @brief  Enable or disable filter module for VC output.
	*/
void VC_FilterCmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		VC_CTRL1 |= VC_CTRL1_FLTEN;
	}
	else
	{
		VC_CTRL1 &= ~VC_CTRL1_FLTEN;
	}
}

/**
	* @brief  Configurate to select which to trigge interrupt for VC.
	* @param  VC_IntTrigSel, as follow:
	* 	@arg  VC_IntTrigSel_NO
	*	  @arg  VC_IntTrigSel_Level_High               
	*   @arg  VC_IntTrigSel_Edge_Rising          	
	*   @arg  VC_IntTrigSel_Edge_Falling					
	*/
void VC_ITConfig(uint16_t VC_IntTrigSel, FunctionalState NewState)
{	
	volatile uint32_t tmpreg = VC_CTRL1;
		
	tmpreg &= ~(VC_CTRL1_INTL | VC_CTRL1_INTPOS | VC_CTRL1_INTNEG);
	
	if (NewState != DISABLE)
	{
		tmpreg |= VC_IntTrigSel;
	}
	
	VC_CTRL1 = tmpreg;
}

/**
	* @brief  Get interrupt flag of VC.
	*/
ITStatus VC_GetITStatus(void)
{
	return (VC_CTRL1 & VC_CTRL1_VCINT) != VC_CTRL1_VCINT ? SET : RESET;
}

/**
	* @brief  Clear interrupt flag of VC.
	*/
void VC_ClearITFlag(void)
{
	VC_CTRL1 &= ~VC_CTRL1_VCINT;
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
