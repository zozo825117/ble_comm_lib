/**
  ******************************************************************************
  * @file    GW32L0xx_des.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_des.h"

/**
	* @brief  Deinitialize DES register to the reset value.
	*/
void DES_DeInit(void)
{
	do
	{
		/* Restore DES peripheral register to the reset value */
		PERI_RST_CTRL0 |= RMU_PERI_RESET0_DES;
		
	} while ( (PERI_RST_CTRL0 & RMU_PERI_RESET0_DES) != RMU_PERI_RESET0_DES );
	
	/* Switch to work in normal mode */
	PERI_RST_CTRL0 &= ~RMU_PERI_RESET0_DES;
}

/**
	* @brief  Initialize structure with the specified parameters.
	*/
void DES_StructInit(DES_InitTypeDef* DES_InitStruct)
{
	DES_InitStruct->DES_Mode = DES_Mode_DES;
	DES_InitStruct->DES_EncryptDecrypt = DES_EncryptDecrypt_Encrypt;
	DES_InitStruct->DES_OPMode = DES_OPMode_ECB;
	DES_InitStruct->DES_KeySel = DES_KeySel_DES_KEY1;
	DES_InitStruct->DES_RandomFunction = DES_RandomFunction_Disable;
}

/**
	* @brief  Initialize DES module with the specified structure parameters.
	*/
void DES_Init(DES_InitTypeDef* DES_InitStruct)
{
    volatile uint32_t tmpreg = 0;
	
	tmpreg = DES->CTRL;	
	DES->CTRL &= ~DES_CTRL_START;
	
	tmpreg &= ~DES_CTRL_DES_MODE;
	tmpreg |= (DES_InitStruct->DES_Mode << 4);
	tmpreg &= ~DES_CTRL_ENCRYPT;
	tmpreg |= (DES_InitStruct->DES_EncryptDecrypt << 1);
	tmpreg &= ~DES_CTRL_OP_MODE;
	tmpreg |= (DES_InitStruct->DES_OPMode << 5);
	tmpreg &= ~DES_CTRL_KEY_SEL;
	tmpreg |= (DES_InitStruct->DES_KeySel << 2);
	tmpreg &= ~DES_CTRL_RAND_EN;
	tmpreg |= (DES_InitStruct->DES_RandomFunction << 8);
	
	DES->CTRL = tmpreg;
}

/**
	* @brief  Enable or disable DES module.
	*/
void DES_Cmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		do
		{
			DES->CTRL |= DES_CTRL_START;
			
		} while ((DES->CTRL & DES_CTRL_START) != DES_CTRL_START);
	}
	else
	{
		DES->CTRL &= ~DES_CTRL_START;	
	}
}

/**
	* @brief  Get completed flag of DES.
	*/
FlagStatus DES_GetCompletedFlagStatus(void)
{
	return (DES->CTRL & DES_CTRL_START) == DES_CTRL_START ? RESET : SET;
}

/**
	* @brief  Set random number for DES.
	*/
void DES_SetRandomNumber(uint32_t DES_RandomNumber)
{
	DES->RAND = (DES_RandomNumber & DES_RAND);
}

/**
	* @brief  Set key for DES.
	* @param  DES_KeySel, as follow
	* 	@arg	DES_KeySel_DES_KEY1
	* 	@arg	DES_KeySel_DES_KEY2
	* 	@arg	DES_KeySel_DES_KEY3
	*/
void DES_SetKey(DES_KeySel_TypyDef DES_KeySel, uint64_t DES_KEY)
{
	*(volatile uint32_t *)( (DES_BASEADDR + 0x28) + 8 * DES_KeySel ) = (DES_KEY & DES_KEY_LOW);
	*(volatile uint32_t *)( (DES_BASEADDR + 0x28) + 0x4 + 8 * DES_KeySel ) = ((DES_KEY >> 32) & DES_KEY_HIGH);
}

/**
	* @brief  Set initialization vector for DES.
	*/
void DES_SetIV(uint64_t DES_IV)
{
	DES->IV_L = (DES_IV & DES_IV_LOW);
	DES->IV_H = ( (DES_IV >> 32) & DES_IV_HIGH );
}

/**
	* @brief  Set data for DES as input.
	*/
void DES_SetData(uint64_t DES_DATA)
{
	DES->DATA_L = (DES_DATA & DES_DATA_LOW);
	DES->DATA_H = ( (DES_DATA >> 32) & DES_DATA_HIGH );
}

/**
	* @brief  Get encrypted data for DES as output.
	*/
uint64_t DES_GetData(void)
{
	uint64_t vBuff = DES->DATA_H;
	return ( vBuff << 32 ) | DES->DATA_L;
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
