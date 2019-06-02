/**
  ******************************************************************************
  * @file    GW32L0xx_misc.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_misc.h"

/**
	* @brief  Deinitialize NVIC register to the reset value.
	*/
void NVIC_DeInit(void)
{
	/* Reset interrupt set enable register */
	NVIC->ISER[0] = 0x00000000;
	
	/* Reset interrupt clear enable register */	
	NVIC->ICER[0] = 0x00000000;

	/* Reset interrupt set pending register */	
	NVIC->ISPR[0] = 0x00000000;
	
	/* Reset interrupt clear pending register */		
	NVIC->ICPR[0] = 0x00000000;
	
	/* Reset interrupt priority register */		
	NVIC->IP[0] = 0x00000000;
	NVIC->IP[1] = 0x00000000;
	NVIC->IP[2] = 0x00000000;
	NVIC->IP[3] = 0x00000000;
	NVIC->IP[4] = 0x00000000;
	NVIC->IP[5] = 0x00000000;
	NVIC->IP[6] = 0x00000000;
	NVIC->IP[7] = 0x00000000;
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
