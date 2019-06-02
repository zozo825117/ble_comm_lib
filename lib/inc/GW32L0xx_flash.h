/**
  ******************************************************************************
  * @file    GW32L0xx_flash.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the FLASH
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW32L0XX_FLASH_H
#define __GW32L0XX_FLASH_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

#define FLASH_CTRL_MODE_Read              ((uint8_t)0x00)
#define FLASH_CTRL_MODE_Write             ((uint8_t)0x01)
#define FLASH_CTRL_MODE_ErasePage         ((uint8_t)0x02)	 
#define FLASH_CTRL_MODE_EraseMass         ((uint8_t)0x03)


typedef enum
{
	FLASH_ERROR = 0x0,
	FLASH_COMPLETE = 0x1 

} FLASH_Status;

typedef enum
{
	FLASH_ITFlag_0 = 0x1,
	FLASH_ITFlag_1 = 0x2

} FLASH_ITFlag_TypeDef;

void FLASH_SetTNVS(uint16_t Flash_TNVS);
void FLASH_SetTPGS(uint16_t Flash_TPGS);
void FLASH_SetTPROG(uint16_t Flash_TPROG);
void FLASH_SetTNVH(uint16_t Flash_TNVH);
void FLASH_SetTRCV(uint8_t Flash_TRCV);
void FLASH_SetTERASE(uint32_t Flash_TERASE);
void FLASH_SetTME(uint32_t Flash_TME);
void FLASH_SetTNVH1(uint16_t Flash_TNVH1);

void FLASH_UnLockPage(uint8_t FLASH_PAGEx);
void FLASH_LockPage(uint8_t FLASH_PAGEx);

void FLASH_ReadWaitCycleCmd(FunctionalState NewState);
void FLASH_ReadCmd(FunctionalState NewState);
void FLASH_WriteCmd(FunctionalState NewState);
FLASH_Status FLASH_ErasePage(uint8_t FLASH_PAGEx);
FLASH_Status FLASH_EraseMass(void);

FLASH_Status FLASH_WriteWord(uint32_t FLASH_Address, uint32_t FLASH_Data);
FLASH_Status FLASH_WriteHalfWord(uint32_t FLASH_Address, uint16_t FLASH_Data);
FLASH_Status FLASH_WriteByte(uint32_t FLASH_Address, uint8_t FLASH_Data);

FLASH_Status FLASH_ReadWord(uint32_t FLASH_Address, uint32_t *pFLASH_Data);
FLASH_Status FLASH_ReadHalfWord(uint32_t FLASH_Address, uint16_t *pFLASH_Data);
FLASH_Status FLASH_ReadByte(uint32_t FLASH_Address, uint8_t *pFLASH_Data);

ITStatus FLASH_GetITStatus(FLASH_ITFlag_TypeDef FLASH_ITFlag);
void FLASH_ClearITFlag(FLASH_ITFlag_TypeDef FLASH_ITFlag);

#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_FLASH_H */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
