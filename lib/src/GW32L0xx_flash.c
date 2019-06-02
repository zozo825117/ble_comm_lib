/**
  ******************************************************************************
  * @file    GW32L0xx_flash.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_flash.h"

/**
	* @brief  Set value of TNVS.
	*/
void FLASH_SetTNVS(uint16_t Flash_TNVS)
{
	FLASH->TNVS = (Flash_TNVS & FLASH_TNVS);
}

/**
	* @brief  Set value of TPGS.
	*/
void FLASH_SetTPGS(uint16_t Flash_TPGS)
{
	FLASH->TPGS = (Flash_TPGS & FLASH_TPGS);
}

/**
	* @brief  Set value of TPROG.
	*/
void FLASH_SetTPROG(uint16_t Flash_TPROG)
{
	FLASH->TPROG = (Flash_TPROG & FLASH_TPROG);
}

/**
	* @brief  Set value of TNVH.
	*/
void FLASH_SetTNVH(uint16_t Flash_TNVH)
{
	FLASH->TNVH = (Flash_TNVH & FLASH_TNVH);
}

/**
	* @brief  Set value of TRCV.
	*/
void FLASH_SetTRCV(uint8_t Flash_TRCV)
{
	FLASH->TRCV = (Flash_TRCV & FLASH_TRCV);
}

/**
	* @brief  Set value of TERASE.
	*/
void FLASH_SetTERASE(uint32_t Flash_TERASE)
{
	FLASH->TERASE = (Flash_TERASE & FLASH_TERASE);
}

/**
	* @brief  Set value of TME.
	*/
void FLASH_SetTME(uint32_t Flash_TME)
{
	FLASH->TME = (Flash_TME & FLASH_TME);
}

/**
	* @brief  Set value of TNVH1.
	*/
void FLASH_SetTNVH1(uint16_t Flash_TNVH1)
{
	FLASH->TNVH1 = (Flash_TNVH1 & FLASH_TNVH1);
}

/**
	* @brief  Unlock page of FLASH with specified parameters.
	* @param  FLASH_PAGEx as follow
  * 	@arg    0: FLASH_PAGE0
  * 	@arg    1: FLASH_PAGE1
  *         ...
  *   @arg  255: FLASH_PAGE255
	*/
void FLASH_UnLockPage(uint8_t FLASH_PAGEx)
{
	FLASH->PL_SEQ = 0x5A5A5A5A;
	FLASH->PL_SEQ = 0xA5A5A5A5;
	
	*(volatile uint32_t *)( (EFLASH_CTRL_BASEADDR + 0x38) + (FLASH_PAGEx / 32) * 4 ) |= (0x1 << FLASH_PAGEx % 32);
}

/**
	* @brief  Lock page of FLASH with specified parameters.
	* @param  FLASH_PAGEx as follow
  * 	@arg    0: FLASH_PAGE0
  * 	@arg    1: FLASH_PAGE1
  *         ...
  *   @arg  255: FLASH_PAGE255
	*/
void FLASH_LockPage(uint8_t FLASH_PAGEx)
{	
	FLASH->PL_SEQ = 0x5A5A5A5A;
	FLASH->PL_SEQ = 0xA5A5A5A5;
		
	*(volatile uint32_t *)( (EFLASH_CTRL_BASEADDR + 0x38) + (FLASH_PAGEx / 32) * 4 ) &= ~(0x1 << FLASH_PAGEx % 32);
}

/**
	* @brief  SysCoreClk > 16MHz and read flash, must insert flash read wait cycle.
	*/
void FLASH_ReadWaitCycleCmd(FunctionalState NewState)
{
	volatile uint32_t tmp = 0x5AA5C33C;
	
	if (NewState != DISABLE)
	{
		FLASH->FLASH_CTRL |= FLASH_CTRL_READ_WAIT_CYCLE;
	}
	else
	{
		FLASH->FLASH_CTRL &= ~FLASH_CTRL_READ_WAIT_CYCLE;	
	}
	
	if (tmp != 0x5AA5C33C)
	{
		FLASH->FLASH_CTRL &= ~FLASH_CTRL_READ_WAIT_CYCLE;		
	}
}

/**
	* @brief  Enable flash read operation.
	*/
void FLASH_ReadCmd(FunctionalState NewState)
{
	volatile uint32_t tmp = 0x5AA5C33C;
	
	FLASH->FLASH_CTRL &= ~FLASH_CTRL_MODE;
	
	if (NewState != DISABLE)
	{
		FLASH->FLASH_CTRL |= FLASH_CTRL_MODE_Read;	
	}
	
	if (tmp != 0x5AA5C33C)
	{
		FLASH->FLASH_CTRL &= ~FLASH_CTRL_MODE;	
	}		
}

/**
	* @brief  Enable flash write operation.
	*/
void FLASH_WriteCmd(FunctionalState NewState)
{
	volatile uint32_t tmp = 0x5AA5C33C;
	
	FLASH->FLASH_CTRL &= ~FLASH_CTRL_MODE;
	
	if (NewState != DISABLE)
	{
		FLASH->FLASH_CTRL |= FLASH_CTRL_MODE_Write;	
	}
	
	if (tmp != 0x5AA5C33C)
	{
		FLASH->FLASH_CTRL &= ~FLASH_CTRL_MODE;	
	}	
}

/**
	* @brief  Flash erase page with specified parameters.
	* @param  FLASH_PAGEx as follow
  * 	@arg    0: FLASH_PAGE0
  * 	@arg    1: FLASH_PAGE1
  *         ...
  *   @arg  255: FLASH_PAGE255
	* @retval FLASH_COMPLETE or FLASH_ERROR
	*/
FLASH_Status FLASH_ErasePage(uint8_t FLASH_PAGEx)
{
	volatile uint32_t tmp = 0x5AA5C33C;
		
	FLASH->FLASH_CTRL &= ~FLASH_CTRL_MODE;
		
	if (tmp == 0x5AA5C33C)
	{
		FLASH->FLASH_CTRL |= FLASH_CTRL_MODE_ErasePage;
			
		if (tmp == 0x5AA5C33C)
		{
			*(volatile uint32_t *)(FLASH_PAGEx << 10) = 0x5A0F3CE1;
				
			return FLASH_COMPLETE;
		}
	}
	
	return FLASH_ERROR;
}

/**
	* @brief  Flash erase chip.
	* @retval FLASH_COMPLETE or FLASH_ERROR
	*/
FLASH_Status FLASH_EraseMass(void)
{
	volatile uint32_t tmp = 0x5AA5C33C;
		
	FLASH->FLASH_CTRL &= ~FLASH_CTRL_MODE;
		
	if (tmp == 0x5AA5C33C)
	{
		FLASH->FLASH_CTRL |= FLASH_CTRL_MODE_EraseMass;
			
		if (tmp == 0x5AA5C33C)
		{
			*(volatile uint32_t *)(FLASH_SIZE - 4) = 0x5A0F3CE1;
			
			return FLASH_COMPLETE;
		}
	}
		
	return FLASH_ERROR;
}

/**
	* @brief  Flash write word with the specified flash addres.
	* @retval FLASH_COMPLETE or FLASH_ERROR
	*/
FLASH_Status FLASH_WriteWord(uint32_t FLASH_Address, uint32_t FLASH_Data)
{
	volatile uint32_t tmp = 0x5AA5C33C;
		
	FLASH->FLASH_CTRL &= ~FLASH_CTRL_MODE;
		
	if (tmp == 0x5AA5C33C)
	{
		FLASH->FLASH_CTRL |= FLASH_CTRL_MODE_Write;
			
		if (tmp == 0x5AA5C33C)
		{
			*(volatile uint32_t *)FLASH_Address = FLASH_Data;
			
			return FLASH_COMPLETE;
		}
	}
		
	return FLASH_ERROR;
}

/**
	* @brief  Flash write halfword with the specified flash addres.
	* @retval FLASH_COMPLETE or FLASH_ERROR
	*/
FLASH_Status FLASH_WriteHalfWord(uint32_t FLASH_Address, uint16_t FLASH_Data)
{
	volatile uint32_t tmp = 0x5AA5C33C;
		
	FLASH->FLASH_CTRL &= ~FLASH_CTRL_MODE;
		
	if (tmp == 0x5AA5C33C)
	{
		FLASH->FLASH_CTRL |= FLASH_CTRL_MODE_Write;
			
		if (tmp == 0x5AA5C33C)
		{
			*(volatile uint16_t *)FLASH_Address = FLASH_Data;
			
			return FLASH_COMPLETE;
		}
	}
		
	return FLASH_ERROR;
}

/**
	* @brief  Flash write byte with the specified flash addres.
	* @retval FLASH_COMPLETE or FLASH_ERROR
	*/
FLASH_Status FLASH_WriteByte(uint32_t FLASH_Address, uint8_t FLASH_Data)
{
	volatile uint32_t tmp = 0x5AA5C33C;
		
	FLASH->FLASH_CTRL &= ~FLASH_CTRL_MODE;
		
	if (tmp == 0x5AA5C33C)
	{
		FLASH->FLASH_CTRL |= FLASH_CTRL_MODE_Write;
			
		if (tmp == 0x5AA5C33C)
		{
			*(volatile uint8_t *)FLASH_Address = FLASH_Data;
			
			return FLASH_COMPLETE;
		}
	}
		
	return FLASH_ERROR;
}

/**
	* @brief  Flash read word with the specified flash addres.
	* @retval FLASH_COMPLETE or FLASH_ERROR
	*/
FLASH_Status FLASH_ReadWord(uint32_t FLASH_Address, uint32_t *pFLASH_Data)
{
	volatile uint32_t tmp = 0x5AA5C33C;
		
	FLASH->FLASH_CTRL &= ~FLASH_CTRL_MODE;
		
	if (tmp == 0x5AA5C33C)
	{
		FLASH->FLASH_CTRL |= FLASH_CTRL_MODE_Read;
			
		if (tmp == 0x5AA5C33C)
		{
			*pFLASH_Data = *(volatile uint32_t *)FLASH_Address;		
			
			return FLASH_COMPLETE;
		}
	}
		
	return FLASH_ERROR;
}

/**
	* @brief  Flash read halfword with the specified flash addres.
	* @retval FLASH_COMPLETE or FLASH_ERROR
	*/
FLASH_Status FLASH_ReadHalfWord(uint32_t FLASH_Address, uint16_t *pFLASH_Data)
{
	volatile uint32_t tmp = 0x5AA5C33C;
		
	FLASH->FLASH_CTRL &= ~FLASH_CTRL_MODE;
		
	if (tmp == 0x5AA5C33C)
	{
		FLASH->FLASH_CTRL |= FLASH_CTRL_MODE_Read;
			
		if (tmp == 0x5AA5C33C)
		{
			*pFLASH_Data = *(volatile uint16_t *)FLASH_Address;		
			
			return FLASH_COMPLETE;
		}
	}
		
	return FLASH_ERROR;
}

/**
	* @brief  Flash read byte with the specified flash addres.
	* @retval FLASH_COMPLETE or FLASH_ERROR
	*/
FLASH_Status FLASH_ReadByte(uint32_t FLASH_Address, uint8_t *pFLASH_Data)
{
	volatile uint32_t tmp = 0x5AA5C33C;
		
	FLASH->FLASH_CTRL &= ~FLASH_CTRL_MODE;
		
	if (tmp == 0x5AA5C33C)
	{
		FLASH->FLASH_CTRL |= FLASH_CTRL_MODE_Read;
			
		if (tmp == 0x5AA5C33C)
		{
			*pFLASH_Data = *(volatile uint8_t *)FLASH_Address;		
			
			return FLASH_COMPLETE;
		}
	}
		
	return FLASH_ERROR;
}

/**
	* @brief  Get status of FLASH interrupt flag.
	*/
ITStatus FLASH_GetITStatus(FLASH_ITFlag_TypeDef FLASH_ITFlag)
{
	return (FLASH->FLASH_FLAG & FLASH_ITFlag) == FLASH_ITFlag ? SET : RESET;
}

/**
	* @brief  Clear interrupt flag of FLASH.
	*/
void FLASH_ClearITFlag(FLASH_ITFlag_TypeDef FLASH_ITFlag)
{
	FLASH->FLASH_FLAG |= FLASH_ITFlag;
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
