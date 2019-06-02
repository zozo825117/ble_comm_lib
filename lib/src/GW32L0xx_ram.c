/**
  ******************************************************************************
  * @file    GW32L0xx_ram.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_ram.h"

/**
	* @brief  Deinitialize backupram module to set relevant register to the reset value.
	*/
void RAM_BackUpRAM_DeInit(void)
{
	do
	{
		/* Restore BKRAM peripheral register to the reset value */
		PERI_RST_CTRL1 |= RMU_PERI_RESET1_BKRAM;
		
	} while ( (PERI_RST_CTRL1 & RMU_PERI_RESET1_BKRAM) != RMU_PERI_RESET1_BKRAM );
	
	/* Switch to work in normal mode */
	PERI_RST_CTRL1 &= ~RMU_PERI_RESET1_BKRAM;
}

/**
	* @brief  RAM controller write word to specified address.
	* @retval RAM_COMPLETE or RAM_ERROR.
	*/
RAM_Status RAM_WriteWord(uint32_t RAM_Address, uint32_t RAM_Data)
{
	if (RAM_Address < SRAM_BASE + RAM_SIZE)
	{
		*(volatile uint32_t *)RAM_Address = RAM_Data;
		
		return RAM_COMPLETE;
	}
	else
	{
		return RAM_ERROR;	
	}
}

/**
	* @brief  RAM controller write halfword to specified address.
	* @retval RAM_COMPLETE or RAM_ERROR.
	*/
RAM_Status RAM_WriteHalfWord(uint32_t RAM_Address, uint16_t RAM_Data)
{
	if (RAM_Address < SRAM_BASE + RAM_SIZE)
	{
		*(volatile uint16_t *)RAM_Address = RAM_Data;
		
		return RAM_COMPLETE;
	}
	else
	{
		return RAM_ERROR;	
	}
}

/**
	* @brief  RAM controller write byte to specified address.
	* @retval RAM_COMPLETE or RAM_ERROR.
	*/
RAM_Status RAM_WriteByte(uint32_t RAM_Address, uint8_t RAM_Data)
{
	if (RAM_Address < SRAM_BASE + RAM_SIZE)
	{
		*(volatile uint8_t *)RAM_Address = RAM_Data;
		
		return RAM_COMPLETE;
	}
	else
	{
		return RAM_ERROR;	
	}
}

/**
	* @brief  RAM controller read word from specified address.
	* @retval RAM_COMPLETE or RAM_ERROR.
	*/
RAM_Status RAM_ReadWord(uint32_t RAM_Address, uint32_t *pRAM_Data)
{
	if (RAM_Address < SRAM_BASE + RAM_SIZE)
	{
		*pRAM_Data = *(volatile uint32_t *)RAM_Address;
		
		return RAM_COMPLETE;
	}
	else
	{
		return RAM_ERROR;	
	}
}

/**
	* @brief  RAM controller read halfword from specified address.
	* @retval RAM_COMPLETE or RAM_ERROR.
	*/
RAM_Status RAM_ReadHalfWord(uint32_t RAM_Address, uint16_t *pRAM_Data)
{
	if (RAM_Address < SRAM_BASE + RAM_SIZE)
	{
		*pRAM_Data = *(volatile uint16_t *)RAM_Address;
		
		return RAM_COMPLETE;
	}
	else
	{
		return RAM_ERROR;	
	}
}

/**
	* @brief  RAM controller read byte from specified address.
	* @retval RAM_COMPLETE or RAM_ERROR.
	*/
RAM_Status RAM_ReadByte(uint32_t RAM_Address, uint8_t *pRAM_Data)
{
	if (RAM_Address < SRAM_BASE + RAM_SIZE)
	{
		*pRAM_Data = *(volatile uint8_t *)RAM_Address;
		
		return RAM_COMPLETE;
	}
	else
	{
		return RAM_ERROR;	
	}
}

/**
	* @brief  RAM controller get address of error ODC.
	* @retval Error address, range(0 ~ 32 * 1024 - 1).
	*/
uint16_t RAM_GetODCErrAddress(void)
{
	return (RAM_FAULT_ADDR & RAM_FAULT_ADDR_VALUE);
}

/**
	* @brief  Get status of RAM interrupt.
	*/
ITStatus RAM_GetITStatus(void)
{
	return (RAM_FAULT_INTR & RAM_FAULT_INTR_FLAG) == RAM_ITFlag_ODC_ERROR ? SET : RESET;
}

/**
	* @brief  Clear RAM interrupt flag.
	*/
void RAM_ClearITFlag(void)
{
	RAM_FAULT_INTR |= RAM_FAULT_INTR_FLAG;
}

/**
	* @brief  BKRAM controller write word to specified backupram.
	* @param  RAM_BackUpSel, as follow
	* 	@arg	RAM_BackUp_0
	* 	@arg	RAM_BackUp_1
	* 	@arg	RAM_BackUp_2
	* 	@arg	RAM_BackUp_3
	* 	@arg	RAM_BackUp_4
	* 	@arg	RAM_BackUp_5
	* 	@arg	RAM_BackUp_6
	* 	@arg	RAM_BackUp_7
	* 	@arg	RAM_BackUp_8
	* 	@arg	RAM_BackUp_9
	* 	@arg	RAM_BackUp_A
	* 	@arg	RAM_BackUp_B
	* 	@arg	RAM_BackUp_C
	* 	@arg	RAM_BackUp_D
	* 	@arg	RAM_BackUp_E
	* 	@arg	RAM_BackUp_F
	*/
void RAM_BackUpRAMWriteWord(RAM_BackUpSel_TypeDef RAM_BackUpSel, uint32_t RAM_BackUpData)
{
	*(volatile uint32_t *)(ANALOG_CTRL_BASEADDR + 0xC0 + 4 * RAM_BackUpSel) = RAM_BackUpData;
}

/**
	* @brief  BKRAM controller write halfword to specified backupram.
	* @param  RAM_BackUpSel, as follow
	* 	@arg	RAM_BackUp_0
	* 	@arg	RAM_BackUp_1
	* 	@arg	RAM_BackUp_2
	* 	@arg	RAM_BackUp_3
	* 	@arg	RAM_BackUp_4
	* 	@arg	RAM_BackUp_5
	* 	@arg	RAM_BackUp_6
	* 	@arg	RAM_BackUp_7
	* 	@arg	RAM_BackUp_8
	* 	@arg	RAM_BackUp_9
	* 	@arg	RAM_BackUp_A
	* 	@arg	RAM_BackUp_B
	* 	@arg	RAM_BackUp_C
	* 	@arg	RAM_BackUp_D
	* 	@arg	RAM_BackUp_E
	* 	@arg	RAM_BackUp_F
	* @param  RAM_BackUpHalfWordOffset, as follow
	* 	@arg 	RAM_BackUpHalfWordOffset_0
	* 	@arg 	RAM_BackUpHalfWordOffset_1
	*/
void RAM_BackUpRAMWriteHalfWord(RAM_BackUpSel_TypeDef RAM_BackUpSel, RAM_BackUpHalfWordOffset_TypeDef RAM_BackUpHalfWordOffset, uint16_t RAM_BackUpData)
{
	*(volatile uint32_t *)(ANALOG_CTRL_BASEADDR + 0xC0 + 4 * RAM_BackUpSel) &= ~(0xFFFFUL << RAM_BackUpHalfWordOffset * 8);
	*(volatile uint32_t *)(ANALOG_CTRL_BASEADDR + 0xC0 + 4 * RAM_BackUpSel) |= (RAM_BackUpData << RAM_BackUpHalfWordOffset * 8);
}

/**
	* @brief  BKRAM controller write byte to specified backupram.
	* @param  RAM_BackUpSel, as follow
	* 	@arg	RAM_BackUp_0
	* 	@arg	RAM_BackUp_1
	* 	@arg	RAM_BackUp_2
	* 	@arg	RAM_BackUp_3
	* 	@arg	RAM_BackUp_4
	* 	@arg	RAM_BackUp_5
	* 	@arg	RAM_BackUp_6
	* 	@arg	RAM_BackUp_7
	* 	@arg	RAM_BackUp_8
	* 	@arg	RAM_BackUp_9
	* 	@arg	RAM_BackUp_A
	* 	@arg	RAM_BackUp_B
	* 	@arg	RAM_BackUp_C
	* 	@arg	RAM_BackUp_D
	* 	@arg	RAM_BackUp_E
	* 	@arg	RAM_BackUp_F
	* @param  RAM_BackUpByteOffset, as follow
	* 	@arg 	RAM_BackUpByteOffset_0
	* 	@arg 	RAM_BackUpByteOffset_1
	* 	@arg 	RAM_BackUpByteOffset_2
	* 	@arg 	RAM_BackUpByteOffset_3	
	*/
void RAM_BackUpRAMWriteByte(RAM_BackUpSel_TypeDef RAM_BackUpSel, RAM_BackUpByteOffset_TypeDef RAM_BackUpByteOffset, uint8_t RAM_BackUpData)
{
	*(volatile uint32_t *)(ANALOG_CTRL_BASEADDR + 0xC0 + 4 * RAM_BackUpSel) &= ~(0xFFUL << RAM_BackUpByteOffset * 8);
	*(volatile uint32_t *)(ANALOG_CTRL_BASEADDR + 0xC0 + 4 * RAM_BackUpSel) |= (RAM_BackUpData << RAM_BackUpByteOffset * 8);
}

/**
	* @brief  BKRAM controller read word form specified backupram.
	* @param  RAM_BackUpSel, as follow
	* 	@arg	RAM_BackUp_0
	* 	@arg	RAM_BackUp_1
	* 	@arg	RAM_BackUp_2
	* 	@arg	RAM_BackUp_3
	* 	@arg	RAM_BackUp_4
	* 	@arg	RAM_BackUp_5
	* 	@arg	RAM_BackUp_6
	* 	@arg	RAM_BackUp_7
	* 	@arg	RAM_BackUp_8
	* 	@arg	RAM_BackUp_9
	* 	@arg	RAM_BackUp_A
	* 	@arg	RAM_BackUp_B
	* 	@arg	RAM_BackUp_C
	* 	@arg	RAM_BackUp_D
	* 	@arg	RAM_BackUp_E
	* 	@arg	RAM_BackUp_F
	*/
uint32_t RAM_BackUpRAMReadWord(RAM_BackUpSel_TypeDef RAM_BackUpSel)
{
	return *(volatile uint32_t *)(ANALOG_CTRL_BASEADDR + 0xC0 + 4 * RAM_BackUpSel);
}

/**
	* @brief  BKRAM controller read halfword form specified backupram.
	* @param  RAM_BackUpSel, as follow
	* 	@arg	RAM_BackUp_0
	* 	@arg	RAM_BackUp_1
	* 	@arg	RAM_BackUp_2
	* 	@arg	RAM_BackUp_3
	* 	@arg	RAM_BackUp_4
	* 	@arg	RAM_BackUp_5
	* 	@arg	RAM_BackUp_6
	* 	@arg	RAM_BackUp_7
	* 	@arg	RAM_BackUp_8
	* 	@arg	RAM_BackUp_9
	* 	@arg	RAM_BackUp_A
	* 	@arg	RAM_BackUp_B
	* 	@arg	RAM_BackUp_C
	* 	@arg	RAM_BackUp_D
	* 	@arg	RAM_BackUp_E
	* 	@arg	RAM_BackUp_F
	* @param  RAM_BackUpHalfWordOffset, as follow
	* 	@arg 	RAM_BackUpHalfWordOffset_0
	* 	@arg 	RAM_BackUpHalfWordOffset_1
	*/
uint16_t RAM_BackUpRAMReadHalfWord(RAM_BackUpSel_TypeDef RAM_BackUpSel, RAM_BackUpHalfWordOffset_TypeDef RAM_BackUpHalfWordOffset)
{
	return *(volatile uint16_t *)(ANALOG_CTRL_BASEADDR + 0xC0 + 4 * RAM_BackUpSel + RAM_BackUpHalfWordOffset);
}

/**
	* @brief  BKRAM controller read byte form specified backupram.
	* @param  RAM_BackUpSel, as follow
	* 	@arg	RAM_BackUp_0
	* 	@arg	RAM_BackUp_1
	* 	@arg	RAM_BackUp_2
	* 	@arg	RAM_BackUp_3
	* 	@arg	RAM_BackUp_4
	* 	@arg	RAM_BackUp_5
	* 	@arg	RAM_BackUp_6
	* 	@arg	RAM_BackUp_7
	* 	@arg	RAM_BackUp_8
	* 	@arg	RAM_BackUp_9
	* 	@arg	RAM_BackUp_A
	* 	@arg	RAM_BackUp_B
	* 	@arg	RAM_BackUp_C
	* 	@arg	RAM_BackUp_D
	* 	@arg	RAM_BackUp_E
	* 	@arg	RAM_BackUp_F
	* @param  RAM_BackUpByteOffset, as follow
	* 	@arg 	RAM_BackUpByteOffset_0
	* 	@arg 	RAM_BackUpByteOffset_1
	* 	@arg 	RAM_BackUpByteOffset_2
	* 	@arg 	RAM_BackUpByteOffset_3	
	*/
uint8_t RAM_BackUpRAMReadByte(RAM_BackUpSel_TypeDef RAM_BackUpSel, RAM_BackUpByteOffset_TypeDef RAM_BackUpByteOffset)
{
	return *(volatile uint8_t *)(ANALOG_CTRL_BASEADDR + 0xC0 + 4 * RAM_BackUpSel + RAM_BackUpByteOffset);
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
