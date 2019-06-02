/**
  ******************************************************************************
  * @file    GW32L0xx_uart.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the UART 
  *          firmware library. 
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

#ifndef __GW32L0XX_UART_H
#define __GW32L0XX_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

#define UART_IT_MDMStatusIE                   UART_INTENR_DSIE
#define UART_IT_LineStatusIE                  UART_INTENR_LSIE
#define UART_IT_TXREmptyIE                   	UART_INTENR_TXREE
#define UART_IT_ReceiveData_RXFIFOTimeOutIE  	UART_INTENR_RDAIE
#define UART_IT_All                           (UART_INTENR_DSIE | UART_INTENR_LSIE | UART_INTENR_TXREE | UART_INTENR_RDAIE)

#define UART_LSFLAG_RXFIFOError              	UART_LNSR_RXFIFOE                       
#define UART_LSFLAG_TXEmpty               		UART_LNSR_TXEMPT                        
#define UART_LSFLAG_TXREmpty_TXFIFOFull       UART_LNSR_TXRE                          
#define UART_LSFLAG_BreakInterrupt            UART_LNSR_BKI                           
#define UART_LSFLAG_FrameError                UART_LNSR_FME                          
#define UART_LSFLAG_ParityError               UART_LNSR_PARE                          
#define UART_LSFLAG_OverFlowError             UART_LNSR_OFE                           
#define UART_LSFLAG_DataReady              	  UART_LNSR_DATARDY                       

#define UART_MDMSFLAG_DCD                			UART_MDMSR_DCD                      
#define UART_MDMSFLAG_RI                 			UART_MDMSR_RI                      
#define UART_MDMSFLAG_DSR                			UART_MDMSR_DSR               
#define UART_MDMSFLAG_CTS                			UART_MDMSR_CTS                   
#define UART_MDMSFLAG_DCDA               			UART_MDMSR_DCDA                   
#define UART_MDMSFLAG_RIA                			UART_MDMSR_RIA                 
#define UART_MDMSFLAG_DSRA               			UART_MDMSR_DSRA                      
#define UART_MDMSFLAG_CTSA               			UART_MDMSR_CTSA      	 


typedef enum
{
	UART_DataLength_5Bits = 0x0,
	UART_DataLength_6Bits = 0x1,
	UART_DataLength_7Bits = 0x2,
	UART_DataLength_8Bits = 0x3	

} UART_DataLength_Typedef;

typedef enum
{
	UART_StopBits_1Bit = 0x0,
	UART_StopBits_1P5Bits = 0x1,
	UART_StopBits_2Bits = 0x2

} UART_StopBits_Typedef;

typedef enum
{
	UART_Parity_None = 0x0,
	UART_Parity_Even = 0x1,
	UART_Parity_Odd	= 0x2,	
	UART_Parity_Force_0 = 0x3,
	UART_Parity_Force_1 = 0x4

} UART_Parity_Typedef;

typedef enum
{
	UART_HardwareFlowControl_None = 0x0,
	UART_HardwareFlowControl_RTS = 0x1,
	UART_HardwareFlowControl_CTS = 0x2,
	UART_HardwareFlowControl_RTS_CTS = 0x3

} UART_HardwareFlowcontrol_Typedef;

typedef enum
{
	UART_IntID_MDMStatus = 0x0,
	UART_IntID_None = 0x1,
	UART_IntID_TXREmpty = 0x2,
	UART_IntID_ReceiveData = 0x4,
	UART_IntID_LineStatus = 0x6,
	UART_IntID_RXFIFOTimeOut = 0xC

} UART_IntID_Typedef;

typedef enum
{
	UART_RXFIFOThreshValue_1_32FULL = 0x0,
	UART_RXFIFOThreshValue_8_32FULL = 0x1,
	UART_RXFIFOThreshValue_16_32FULL = 0x2,
	UART_RXFIFOThreshValue_30_32FULL = 0x3

} UART_RxFIFOThreshValue_TypeDef;

typedef enum
{
	UART_TXFIFOThreshValue_0_32FULL = 0x0,
	UART_TXFIFOThreshValue_2_32FULL = 0x1,
	UART_TXFIFOThreshValue_8_32FULL = 0x2,
	UART_TXFIFOThreshValue_16_32FULL = 0x3

} UART_TxFIFOThreshValue_TypeDef;

typedef struct
{
  uint32_t UART_BaudRate;          

  UART_DataLength_Typedef UART_DataLength;         

  UART_StopBits_Typedef UART_StopBits;           

  UART_Parity_Typedef UART_Parity;               

  UART_HardwareFlowcontrol_Typedef UART_HardwareFlowControl;	

} UART_InitTypeDef;

void UART_DeInit(UART_TypeDef* UARTx);
void UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct);
void UART_StructInit(UART_InitTypeDef* UART_InitStruct);

void UART_ITConfig(UART_TypeDef* UARTx, uint8_t UART_IT, FunctionalState NewState);
void UART_FIFOModeConfig( UART_TypeDef* UARTx, \
													UART_TxFIFOThreshValue_TypeDef TxFIFOThreshValue, \
													UART_RxFIFOThreshValue_TypeDef RxFIFOThreshValue, \
													FunctionalState NewState);
void UART_PTXREModeConfig(UART_TypeDef* UARTx, FunctionalState NewState);

ITStatus UART_GetITStatus(UART_TypeDef* UARTx, UART_IntID_Typedef UART_IntID);
FlagStatus UART_GetLineStatus(UART_TypeDef* UARTx, uint16_t UART_LSFlag);
FlagStatus UART_GetMDMStatus(UART_TypeDef* UARTx, uint16_t UART_MDMSFlag);

void UART_SendData(UART_TypeDef* UARTx, uint8_t Data);
uint8_t UART_ReceiveData(UART_TypeDef* UARTx);

#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_UART_H */


/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
