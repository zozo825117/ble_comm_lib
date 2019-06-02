/**
  ******************************************************************************
  * @file    GW32L0xx_dma.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the DMA 
  *          firmware library. 
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *

  ******************************************************************************
  */

#ifndef __GW32L0XX_DMA_H
#define __GW32L0XX_DMA_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

typedef enum
{ 
	DMA_ChannelSel_CH0 = 0x0,
	DMA_ChannelSel_CH1 = 0x1	

} DMA_ChannelSel_TypeDef;

typedef enum
{
	DMA_ITFlag_Tc = 0x0,
	DMA_ITFlag_BlkTc = 0x1,
	DMA_ITFlag_SrcTc = 0x2,
	DMA_ITFlag_DstTc = 0x3,
	DMA_ITFlag_Err = 0x4

} DMA_ITFlag_TypeDef;

typedef enum
{
	DMA_TransDir_M2M = 0x0,
	DMA_TransDir_M2P = 0x1,
	DMA_TransDir_P2M = 0x2,
	DMA_TransDir_P2P = 0x3

} DMA_TransDir_TypeDef;	

typedef enum
{
	DMA_Mode_DstScatter = 0x0,
	DMA_Mode_SrcGather = 0x1,
	DMA_Mode_Normal = 0x2

} DMA_Mode_TypeDef;

typedef enum
{
	DMA_BurstLen_1 = 0x0,
	DMA_BurstLen_4 = 0x1,
	DMA_BurstLen_8 = 0x2,
	DMA_BurstLen_16 = 0x3,
	DMA_BurstLen_32 = 0x4,
	DMA_BurstLen_64 = 0x5,
	DMA_BurstLen_128 = 0x6,
	DMA_BurstLen_256 = 0x7

} DMA_BurstLen_TypeDef;

typedef enum 
{
	DMA_AddrDir_Inc = 0x0,
	DMA_AddrDir_Dec = 0x1,
	DMA_AddrDir_Hold = 0x2

} DMA_AddrDir_TypeDef;

typedef enum
{
	DMA_TransDataSize_8Bits = 0x0,
	DMA_TransDataSize_16Bits = 0x1,
	DMA_TransDataSize_32Bits = 0x2,

} DMA_TransDataSize_TypeDef;

typedef enum 
{
	DMA_Priority_Low = 0x0,
	DMA_Priority_High = 0x1

} DMA_Priority_TypeDef;

typedef enum
{
	DMA_HandShakeLevelPol_High = 0x0,
	DMA_HandShakeLevelPol_Low	= 0x1

} DMA_HandShakeLevelPol_TypeDef;

typedef enum
{
	DMA_HandShakeSel_HardWare = 0x0,
	DMA_HandShakeSel_SoftWare = 0x1

} DMA_HandShakeSel_TypeDef;

typedef enum
{
	DMA_PerHandShakeInput_HS0 = 0x0,
	DMA_PerHandShakeInput_HS1 = 0x1,
	DMA_PerHandShakeInput_HS2 = 0x2,
	DMA_PerHandShakeInput_HS3 = 0x3

} DMA_PerHandShakeInput_TypeDef;

typedef struct
{	
  uint32_t DMA_SrcAddr; 
  uint32_t DMA_DstAddr; 

  DMA_TransDir_TypeDef DMA_TransDir;

	DMA_Mode_TypeDef DMA_Mode;

  DMA_BurstLen_TypeDef DMA_SrcBurstLen;        
  DMA_BurstLen_TypeDef DMA_DstBurstLen; 

  DMA_AddrDir_TypeDef DMA_SrcAddrDir;      
  DMA_AddrDir_TypeDef DMA_DstAddrDir;          

  DMA_TransDataSize_TypeDef DMA_SrcTransDataSize; 
  DMA_TransDataSize_TypeDef DMA_DstTransDataSize;

	uint16_t DMA_TransBlkSize;

	DMA_HandShakeLevelPol_TypeDef DMA_SrcHandShakeLevelPol;
	DMA_HandShakeLevelPol_TypeDef DMA_DstHandShakeLevelPol;

	DMA_HandShakeSel_TypeDef DMA_SrcHandShakeSel;
	DMA_HandShakeSel_TypeDef DMA_DstHandShakeSel;

  DMA_Priority_TypeDef DMA_Priority;

	uint8_t DMA_DstPerReq;
	uint8_t DMA_SrcPerReq;
	DMA_PerHandShakeInput_TypeDef DMA_DstPerHandShakeInput;
	DMA_PerHandShakeInput_TypeDef DMA_SrcPerHandShakeInput;

	uint32_t DMA_SrcAddrGatherDataCnt;
	uint32_t DMA_SrcAddrGatherIntervalCnt;

	uint32_t DMA_DstAddrScatterDataCnt;
	uint32_t DMA_DstAddrScatterIntervalCnt;

	FunctionalState DMA_GlobalIntEn;

} DMA_InitTypeDef;

void DMA_DeInit(void);
void DMA_Init(DMA_ChannelSel_TypeDef DMA_ChannelSel, DMA_InitTypeDef* DMA_InitStruct);
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct);
void DMA_Cmd(DMA_ChannelSel_TypeDef DMA_ChannelSel, FunctionalState NewState);
void DMA_ITConfig(DMA_ChannelSel_TypeDef DMA_ChannelSel, DMA_ITFlag_TypeDef DMA_ITFlag, FunctionalState NewState);

ITStatus DMA_GetRawITStatus(DMA_ChannelSel_TypeDef DMA_ChannelSel, DMA_ITFlag_TypeDef DMA_ITFlag);
ITStatus DMA_GetITStatus(DMA_ChannelSel_TypeDef DMA_ChannelSel, DMA_ITFlag_TypeDef DMA_ITFlag);
ITStatus DMA_GetCombineITStatus(DMA_ITFlag_TypeDef DMA_ITFlag);
void DMA_ClearITFlag(DMA_ChannelSel_TypeDef DMA_ChannelSel, DMA_ITFlag_TypeDef DMA_ITFlag);	

FlagStatus DMA_GetCompletedFlagStatus(DMA_ChannelSel_TypeDef DMA_ChannelSel);

#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_DMA_H */


/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
