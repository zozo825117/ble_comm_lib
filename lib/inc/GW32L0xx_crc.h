/**
  ******************************************************************************
  * @file    GW32L0xx_crc.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the CRC
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW32L0XX_CRC_H
#define __GW32L0XX_CRC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

typedef enum
{
	CRC_Mode_16Bits = 0x0,
	CRC_Mode_32Bits = 0x1

} CRC_Mode_TypeDef;

typedef enum
{
	CRC_InputByteReverse_Disable = 0x1,	
	CRC_InputByteReverse_Enable = 0x0

} CRC_InputByteReverse_TypeDef;

typedef enum
{
	CRC_OutputAllReverse_Disable = 0x1,	
	CRC_OutputAllReverse_Enable = 0x0

} CRC_OutputAllReverse_TypeDef;

typedef enum
{
	CRC_OutputAllXOR_Disable = 0x1,	
	CRC_OutputAllXOR_Enable = 0x0

} CRC_OutputAllXOR_TypeDef;

typedef struct
{
	CRC_Mode_TypeDef CRC_Mode;

	CRC_OutputAllReverse_TypeDef CRC_OutputAllReverse;
	CRC_OutputAllXOR_TypeDef CRC_OutputAllXOR;
	CRC_InputByteReverse_TypeDef CRC_InputByteReverse;

} CRC_InitTypeDef;

void CRC_DeInit(void);
void CRC_StructInit(CRC_InitTypeDef* CRC_InitStruct);
void CRC_Init(CRC_InitTypeDef* CRC_InitStruct);

uint32_t CRC_GetCRCResult(CRC_Mode_TypeDef CRC_Mode);
ErrorStatus CRC_GetCRCFlagStatus(void);

void CRC_InitResult(CRC_Mode_TypeDef CRC_Mode);
void CRC_SendCRCData(CRC_Mode_TypeDef CRC_Mode, uint32_t CRC_Data);

#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_CRC_H */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
