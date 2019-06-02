/**
  ******************************************************************************
  * @file    GW32L0xx_rmu.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_rmu.h"

/**
	* @brief  Get flag of system reset source.
	*/
FlagStatus RMU_GetResetFlag(RMU_ResetSource_TypeDef RMU_ResetSource)
{
	return (RESETFLAG & RMU_ResetSource) != RMU_ResetSource ? RESET : SET;
}

/**
	* @brief  Clear flag of system reset source.
	*/
void RMU_ClearResetFlag(RMU_ResetSource_TypeDef RMU_ResetSource)
{
	RESETFLAG &= ~RMU_ResetSource;
}

/**
  * @param   RMU_Periph0: specifies the peripheral.
  *          This parameter can be any combination of the following values:
  *           @arg RMU_APBPeriph0_RNG
  *           @arg RMU_APBPeriph0_DES
  *           @arg RMU_APBPeriph0_ADC
  *           @arg RMU_APBPeriph0_BUZZER  
  *           @arg RMU_APBPeriph0_CRC
  *           @arg RMU_APBPeriph0_DMA
  *           @arg RMU_APBPeriph0_FLASH
  *           @arg RMU_APBPeriph0_PCA4
  *           @arg RMU_APBPeriph0_PCA3 
  *           @arg RMU_APBPeriph0_PCA2
  *           @arg RMU_APBPeriph0_PCA1         
  *           @arg RMU_APBPeriph0_TIMER4
  *           @arg RMU_APBPeriph0_TIMER3
  *           @arg RMU_APBPeriph0_TIMER2 
  *           @arg RMU_APBPeriph0_TIMER1
  *           @arg RMU_APBPeriph0_SCI7816      
  *           @arg RMU_APBPeriph0_I2C2
  *           @arg RMU_APBPeriph0_I2C1 
  *           @arg RMU_APBPeriph0_SPI4
  *           @arg RMU_APBPeriph0_SPI3
  *           @arg RMU_APBPeriph0_SPI2
  *           @arg RMU_APBPeriph0_SPI1
  *           @arg RMU_APBPeriph0_UART6
  *           @arg RMU_APBPeriph0_UART5
  *           @arg RMU_APBPeriph0_UART4
  *           @arg RMU_APBPeriph0_UART3
  *           @arg RMU_APBPeriph0_UART2
  *           @arg RMU_APBPeriph0_UART1	
  * @param  NewState: new state of the specified peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RMU_Periph0ResetCmd(uint32_t RMU_Periph0, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		PERI_RST_CTRL0 |= RMU_Periph0;
	}
	else
	{
		PERI_RST_CTRL0 &= ~RMU_Periph0;
	}
}

/**   
  * @param  RMU_Periph1: specifies the peripheral.
  *         This parameter can be any combination of the following values:
  *             @arg RMU_APBPeriph1_LCD
  *             @arg RMU_APBPeriph1_WDT
  *             @arg RMU_APBPeriph1_BASETIMER
  *             @arg RMU_APBPeriph1_RTC
  *             @arg RMU_APBPeriph1_PORT  
  *             @arg RMU_APBPeriph1_BKRAM 
  * @param  NewState: new state of the specified peripheral.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void RMU_Periph1ResetCmd(uint8_t RMU_Periph1, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		PERI_RST_CTRL1 |= RMU_Periph1;
	}
	else
	{
		PERI_RST_CTRL1 &= ~RMU_Periph1;
	}
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
