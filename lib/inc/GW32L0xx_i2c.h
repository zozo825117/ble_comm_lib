/**
  ******************************************************************************
  * @file    GW32L0xx_i2c.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the I2C 
  *          firmware library. 
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *

  ******************************************************************************
  */

#ifndef __GW32L0XX_I2C_H
#define __GW32L0XX_I2C_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

typedef enum 
{
	I2C_Mode_Master = 0x0,
	I2C_Mode_Slave = 0x1

} I2C_Mode_TypeDef;	 

typedef enum 
{
	I2C_AddrType_7Bits = 0x0,
	I2C_AddrType_10Bits = 0x1
} I2C_AddrType_TypeDef;

typedef enum
{
	I2C_ClearITFlag_ALL = 0x0,
	I2C_ClearITFlag_RXU = 0x1,
	I2C_ClearITFlag_RXO = 0x2,
	I2C_ClearITFlag_TXO = 0x3,
	I2C_ClearITFlag_RDR = 0x4,
	I2C_ClearITFlag_TXA = 0x5,
	I2C_ClearITFlag_RXD = 0x6,
	I2C_ClearITFlag_ACT = 0x7,
	I2C_ClearITFlag_SPDET = 0x8,
	I2C_ClearITFlag_SDET = 0x9,
	I2C_ClearITFlag_GC = 0xA,

	I2C_ClearITFlag_RSDET = 0xB

} I2C_ClearITFlag_TypeDef;


typedef struct
{
	I2C_Mode_TypeDef I2C_Mode;

	I2C_AddrType_TypeDef I2C_AddrType;
	uint16_t I2C_MstAccessAddr;
	uint16_t I2C_SlvAddr;

	uint16_t I2C_SCLHighLevel;
	uint16_t I2C_SCLLowLevel;

	uint16_t I2C_SDASetUpTime;
	uint16_t I2C_SDATxHoldTime;
  uint16_t I2C_SDARxHoldTime;

	uint8_t I2C_SpikeTime;

	uint8_t I2C_RxFIFOThreshValue;
	uint8_t I2C_TxFIFOThreshValue;

} I2C_InitTypeDef;	

void I2C_DeInit(I2C_TypeDef* I2Cx);
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);	 
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);	 

void I2C_ITConfig(I2C_TypeDef* I2Cx, uint16_t I2C_ITMask, FunctionalState NewState);
void I2C_DMAModeConfig( I2C_TypeDef* I2Cx, \
												uint8_t I2C_DMARxTrigThreshLevel, \
                        uint8_t I2C_DMATxTrigThreshLevel, \
                        FunctionalState I2C_DMARxTrigNewState, \
												FunctionalState I2C_DMATxTrigNewState );
void I2C_AbrtConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);

FlagStatus I2C_GetEnabledFlagStatus(I2C_TypeDef* I2Cx, uint8_t I2C_EnabledStatus);
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint8_t I2C_FLAG);
ITStatus I2C_GetRawITStatus(I2C_TypeDef* I2Cx, uint16_t I2C_ITStatus);
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint16_t I2C_ITStatus);

void I2C_ClearITFlag(I2C_TypeDef* I2Cx, I2C_ClearITFlag_TypeDef I2C_ITFlag);

void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data);
void I2C_SendDataWithStop(I2C_TypeDef* I2Cx, uint8_t Data);
void I2C_SendDataWithRestartRead(I2C_TypeDef* I2Cx);
void I2C_SendDataWithRead(I2C_TypeDef* I2Cx);
void I2C_SendDataWithReadStop(I2C_TypeDef* I2Cx);
void I2C_SendDataWithRestartReadStop(I2C_TypeDef* I2Cx);
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx);

#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_PORT_H */


/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
