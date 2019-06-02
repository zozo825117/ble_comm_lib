/**
  ******************************************************************************
  * @file    GW32L0xx_crc.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_crc.h"

/**
	* @brief  Deinitialize CRC register to the reset value.
	*/
void CRC_DeInit(void)
{
	do
	{
		/* Restore CRC peripheral register to the reset value */
		PERI_RST_CTRL0 |= RMU_PERI_RESET0_CRC;
		
	} while ( (PERI_RST_CTRL0 & RMU_PERI_RESET0_CRC) != RMU_PERI_RESET0_CRC );
	
	/* Switch to work in normal mode */
	PERI_RST_CTRL0 &= ~RMU_PERI_RESET0_CRC;
}

/**
	* @brief  Initialize structure with the default value.
	*/
void CRC_StructInit(CRC_InitTypeDef* CRC_InitStruct)
{
	CRC_InitStruct->CRC_Mode = CRC_Mode_16Bits;
	
	CRC_InitStruct->CRC_OutputAllReverse = CRC_OutputAllReverse_Disable;
	CRC_InitStruct->CRC_OutputAllXOR = CRC_OutputAllXOR_Disable;
	CRC_InitStruct->CRC_InputByteReverse = CRC_InputByteReverse_Disable;
}

/**
	* @brief  Initialize CRC module with the specified structure parameters.
	*/
void CRC_Init(CRC_InitTypeDef* CRC_InitStruct)
{
    volatile uint32_t tmpreg = 0;
	
	tmpreg = CRC->CTRL;
	
	tmpreg &= ~CRC_CTRL_CRC_SEL;
	tmpreg |= (CRC_InitStruct->CRC_Mode << 1);
	tmpreg &= ~CRC_CTRL_REFOUT;
	tmpreg |= (CRC_InitStruct->CRC_OutputAllReverse << 3);
	tmpreg &= ~CRC_CTRL_XOROUT;
	tmpreg |= (CRC_InitStruct->CRC_OutputAllXOR << 4);
	tmpreg &= ~CRC_CTRL_REFIN;
	tmpreg |= (CRC_InitStruct->CRC_InputByteReverse << 2);
	
	CRC->CTRL = tmpreg;
}

/**
	* @brief  Get result of CRC according to the CRC run mode.
	* @param  CRC_Mode, as follow
	* 	@arg  CRC_Mode_16Bits
	*   @arg  CRC_Mode_32Bits
	*/
uint32_t CRC_GetCRCResult(CRC_Mode_TypeDef CRC_Mode)
{
	return CRC->RESULT & ( (CRC_Mode == CRC_Mode_16Bits) ? CRC_RESULT_CRC16 : CRC_RESULT_CRC32 );
}

/**
	* @brief  Get status of CRC check out flag.
	*/
ErrorStatus CRC_GetCRCFlagStatus(void)
{
	return (CRC->FLAG & CRC_FLAG_CRCFLAG) == CRC_FLAG_CRCFLAG ? SUCCESS : ERROR;
}

/**
	* @brief  Initialize result of CRC according to the CRC run mode.
	* @param  CRC_Mode, as follow
	* 	@arg  CRC_Mode_16Bits
	*   @arg  CRC_Mode_32Bits
	*/
void CRC_InitResult(CRC_Mode_TypeDef CRC_Mode)
{
	CRC->RESULT = ( (CRC_Mode == CRC_Mode_16Bits) ? CRC_RESULT_CRC16 : CRC_RESULT_CRC32 );
}

/**
	* @brief  Send data as CRC input according to the CRC run mode.
	* @param  CRC_Mode, as follow
	* 	@arg  CRC_Mode_16Bits
	*   @arg  CRC_Mode_32Bits
	*/
void CRC_SendCRCData(CRC_Mode_TypeDef CRC_Mode, uint32_t CRC_Data)
{
	if ((CRC_Mode != CRC_Mode_16Bits))
	{
		*( (volatile uint32_t *)(CRC_BASEADDR + 0x80) ) = CRC_Data & CRC_RESULT_CRC32;
	}
	else
	{
		*( (volatile uint16_t *)(CRC_BASEADDR + 0x80) ) = CRC_Data & CRC_RESULT_CRC16;
	}
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
