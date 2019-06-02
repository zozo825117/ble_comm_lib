/**
  ******************************************************************************
  * @file    GW32L0xx_spi.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the SPI 
  *          firmware library. 
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *

  ******************************************************************************
  */

#ifndef __GW32L0XX_SPI_H
#define __GW32L0XX_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

typedef enum
{
	SPI_Mode_TxRx = 0x0,
	SPI_Mode_Tx = 0x1,
	SPI_Mode_Rx = 0x2,     
	SPI_Mode_EEPROMRead = 0x3

} SPI_Mode_TypeDef;

typedef enum
{
	SPI_ClkPol_Low = 0x0,
	SPI_ClkPol_High = 0x1

} SPI_CLKPOL_TypeDef;

typedef enum
{
	SPI_ClkPha_1Edge  = 0x0,
	SPI_ClkPha_2Edge  = 0x1

} SPI_CLKPHA_TypeDef;

typedef enum
{
	SPI_Protcl_Motorola = 0x0,
	SPI_Protcl_NationalSemiMW = 0x2

} SPI_PROTCL_TypeDef;

typedef enum
{
	SPI_MWProtclHandShake_DISABLE = 0x0,
	SPI_MWProtclHandShake_ENABLE = 0x1

} SPI_MWProtclHandShake_TypeDef;

typedef enum
{
	SPI_MWProtclDIR_Rx = 0x0,
	SPI_MWProtclDIR_Tx = 0x1

} SPI_MWProtclDIR_TypeDef;

typedef enum
{
	SPI_MWProtclMode_Discontinue = 0x0,
	SPI_MWProtclMode_Continue = 0x1

} SPI_MWProtclMode_TypeDef;

typedef enum
{	
	SPI_MWProtclComdSize_1Bits = 0x0,
	SPI_MWProtclComdSize_2Bits = 0x1,
	SPI_MWProtclComdSize_3Bits = 0x2,	
	SPI_MWProtclComdSize_4Bits = 0x3,
	SPI_MWProtclComdSize_5Bits = 0x4,
	SPI_MWProtclComdSize_6Bits = 0x5,
	SPI_MWProtclComdSize_7Bits = 0x6,
	SPI_MWProtclComdSize_8Bits = 0x7,
	SPI_MWProtclComdSize_9Bits = 0x8,
	SPI_MWProtclComdSize_10Bits = 0x9,
	SPI_MWProtclComdSize_11Bits = 0xA,
	SPI_MWProtclComdSize_12Bits = 0xB,
	SPI_MWProtclComdSize_13Bits = 0xC,
	SPI_MWProtclComdSize_14Bits = 0xD,
	SPI_MWProtclComdSize_15Bits = 0xE,
	SPI_MWProtclComdSize_16Bits = 0xF

} SPI_MWProtclComdSize_Typedef;	

typedef enum
{	
	SPI_DataSize_4Bits = 0x3,
	SPI_DataSize_5Bits = 0x4,
	SPI_DataSize_6Bits = 0x5,
	SPI_DataSize_7Bits = 0x6,
	SPI_DataSize_8Bits = 0x7,
	SPI_DataSize_9Bits = 0x8,
	SPI_DataSize_10Bits = 0x9,
	SPI_DataSize_11Bits = 0xA,
	SPI_DataSize_12Bits = 0xB,
	SPI_DataSize_13Bits = 0xC,
	SPI_DataSize_14Bits = 0xD,
	SPI_DataSize_15Bits = 0xE,
	SPI_DataSize_16Bits = 0xF

} SPI_DataSize_Typedef;

typedef enum
{
	SPI_ITFlag_MMC = SPI_IM_MMCM,
	SPI_ITFlag_RXF = SPI_IM_RXFM,
	SPI_ITFlag_RXOV = SPI_IM_RXOVM,
	SPI_ITFlag_RXUD = SPI_IM_RXUDM,
	SPI_ITFlag_TXOV = SPI_IM_TXOVM,
	SPI_ITFlag_TXE = SPI_IM_TXEM,
	SPI_ITFlag_ALL = 0x3F

} SPI_ITFlag_TypeDef;

typedef enum
{
	SPI_RawITFlag_RXF = SPI_RIS_RXFR,
	SPI_RawITFlag_RXOV = SPI_RIS_RXOVR,
	SPI_RawITFlag_RXUD = SPI_RIS_RXUDR,
	SPI_RawITFlag_TXOV = SPI_RIS_TXOVR,
	SPI_RawITFlag_TXE = SPI_RIS_TXER,

} SPI_RawITFlag_TypeDef;

typedef enum
{
	SPI_ClearITFlag_TXOV = 0x0,
	SPI_ClearITFlag_RXOV = 0x1,
	SPI_ClearITFlag_RXUD = 0x2,
	SPI_ClearITFlag_MMC = 0x3,	
	SPI_ClearITFlag_ALL = 0x4

} SPI_ClearITFlag_TypeDef;

typedef struct
{   
  SPI_Mode_TypeDef SPI_Mode; 

	SPI_PROTCL_TypeDef SPI_Protcl;	

  SPI_CLKPOL_TypeDef SPI_CPOL;                

  SPI_CLKPHA_TypeDef SPI_CPHA;

  SPI_DataSize_Typedef SPI_DataSize;

	uint16_t SPI_BaudRatePrescaler;

	uint16_t SPI_DataNum;

	SPI_MWProtclComdSize_Typedef SPI_MWProtclComdSize;
	SPI_MWProtclDIR_TypeDef SPI_MWProtclDir;
	SPI_MWProtclMode_TypeDef SPI_MWProtclMode;
	SPI_MWProtclHandShake_TypeDef SPI_MWProtclHandShake;

	uint8_t SPI_RxFIFOThreshValue;
	uint8_t SPI_TxFIFOThreshValue;

	FunctionalState SPI_NSSel;

} SPI_InitTypeDef;


void SPI_DeInit(SPI_TypeDef* SPIx);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);	 
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState);

void SPI_ITConfig(SPI_TypeDef* SPIx, SPI_ITFlag_TypeDef SPI_ITFlag, FunctionalState NewState);
void SPI_DMAModeConfig( SPI_TypeDef* SPIx, \
												uint8_t SPI_DMARxTrigLevel, \
                        uint8_t SPI_DMATxTrigLevel, \
                        FunctionalState SPI_DMARxTrigNewState, \
												FunctionalState SPI_DMATxTrigNewState );

FlagStatus SPI_GetFlagStatus(SPI_TypeDef* SPIx, uint8_t SPI_FlagStatus);
ITStatus SPI_GetRawITStatus(SPI_TypeDef* SPIx, SPI_RawITFlag_TypeDef SPI_ITFlag);
ITStatus SPI_GetITStatus(SPI_TypeDef* SPIx, SPI_ITFlag_TypeDef SPI_ITFlag);
void SPI_ClearITFlag(SPI_TypeDef* SPIx, SPI_ClearITFlag_TypeDef SPI_ITFlag);

uint8_t SPI_GetTxFIFOAvaDataCounter(SPI_TypeDef* SPIx);
uint8_t SPI_GetRxFIFOAvaDataCounter(SPI_TypeDef* SPIx);

uint16_t SPI_ReceiveData(SPI_TypeDef* SPIx);
void SPI_SendData(SPI_TypeDef* SPIx, uint16_t Data);

#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_SPI_H */


/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
