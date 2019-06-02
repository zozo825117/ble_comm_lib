/**
  ******************************************************************************
  * @file    GW32L0xx_ram.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the RAM
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW32L0XX_RAM_H
#define __GW32L0XX_RAM_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

#define RAM_ITFlag_ODC_ERROR	          ((uint8_t)0x1)

typedef enum
{
	RAM_ERROR = 0x0,
	RAM_COMPLETE = 0x1 

} RAM_Status;

typedef enum
{
	RAM_BackUp_0 = 0x0,
	RAM_BackUp_1 = 0x1,
	RAM_BackUp_2 = 0x2,
	RAM_BackUp_3 = 0x3,
	RAM_BackUp_4 = 0x4,
	RAM_BackUp_5 = 0x5,
	RAM_BackUp_6 = 0x6,
	RAM_BackUp_7 = 0x7,
	RAM_BackUp_8 = 0x8,
	RAM_BackUp_9 = 0x9,
	RAM_BackUp_A = 0xA,
	RAM_BackUp_B = 0xB,
	RAM_BackUp_C = 0xC,
	RAM_BackUp_D = 0xD,
	RAM_BackUp_E = 0xE,
	RAM_BackUp_F = 0xF	

} RAM_BackUpSel_TypeDef;

typedef enum
{
	RAM_BackUpByteOffset_0 = 0x0,
	RAM_BackUpByteOffset_1 = 0x1,
	RAM_BackUpByteOffset_2 = 0x2,
	RAM_BackUpByteOffset_3 = 0x3

} RAM_BackUpByteOffset_TypeDef;

typedef enum
{
	RAM_BackUpHalfWordOffset_0 = 0x0,
	RAM_BackUpHalfWordOffset_1 = 0x2

} RAM_BackUpHalfWordOffset_TypeDef;

void RAM_BackUpRAM_DeInit(void);

RAM_Status RAM_WriteWord(uint32_t RAM_Address, uint32_t RAM_Data);
RAM_Status RAM_WriteHalfWord(uint32_t RAM_Address, uint16_t RAM_Data);
RAM_Status RAM_WriteByte(uint32_t RAM_Address, uint8_t RAM_Data);

RAM_Status RAM_ReadWord(uint32_t RAM_Address, uint32_t *pRAM_Data);
RAM_Status RAM_ReadHalfWord(uint32_t RAM_Address, uint16_t *pRAM_Data);
RAM_Status RAM_ReadByte(uint32_t RAM_Address, uint8_t *pRAM_Data);

uint16_t RAM_GetODCErrAddress(void);

ITStatus RAM_GetITStatus(void);
void RAM_ClearITFlag(void);

void RAM_BackUpRAMWriteWord(RAM_BackUpSel_TypeDef RAM_BackUpSel, uint32_t RAM_BackUpData);
void RAM_BackUpRAMWriteHalfWord(RAM_BackUpSel_TypeDef RAM_BackUpSel, RAM_BackUpHalfWordOffset_TypeDef RAM_BackUpHalfWordOffset, uint16_t RAM_BackUpData);
void RAM_BackUpRAMWriteByte(RAM_BackUpSel_TypeDef RAM_BackUpSel, RAM_BackUpByteOffset_TypeDef RAM_BackUpByteOffset, uint8_t RAM_BackUpData);
uint32_t RAM_BackUpRAMReadWord(RAM_BackUpSel_TypeDef RAM_BackUpSel);
uint16_t RAM_BackUpRAMReadHalfWord(RAM_BackUpSel_TypeDef RAM_BackUpSel, RAM_BackUpHalfWordOffset_TypeDef RAM_BackUpHalfWordOffset);
uint8_t RAM_BackUpRAMReadByte(RAM_BackUpSel_TypeDef RAM_BackUpSel, RAM_BackUpByteOffset_TypeDef RAM_BackUpByteOffset);



#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_RAM_H */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
