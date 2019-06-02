/**
  ******************************************************************************
  * @file    GW32L0xx_adc.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the ADC
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW32L0XX_ADC_H
#define __GW32L0XX_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

#define ADC_SampleChannelSel_NO     (0x00) 
#define ADC_SampleChannelSel_CH0    (0x01) 
#define ADC_SampleChannelSel_CH1    (0x02) 
#define ADC_SampleChannelSel_CH2    (0x04) 
#define ADC_SampleChannelSel_CH3    (0x08) 
#define ADC_SampleChannelSel_CH4    (0x10) 
#define ADC_SampleChannelSel_CH5    (0x20) 
#define ADC_SampleChannelSel_CH6    (0x40) 
#define ADC_SampleChannelSel_CH7    (0x80)	 


typedef enum
{
	ADC_SampleCycleSel_3Cycles	= 0x0,
	ADC_SampleCycleSel_1Cycles	= 0x1,
	ADC_SampleCycleSel_6Cycles	= 0x2,
	ADC_SampleCycleSel_9Cycles	= 0x3

} ADC_SampleCycleSel_TypeDef;

typedef enum
{
	ADC_SignalAmpEn_DISABLE = 0x0,
	ADC_SignalAmpEn_ENABLE = 0x1

} ADC_SignalAmpEn_TypeDef;

typedef enum
{
	ADC_RefVoltSel_2P5V = 0x0,
	ADC_RefVoltSel_1P5V = 0x1,
	ADC_RefVoltSel_PORT0_Pin_12 = 0x3

} ADC_RefVoltSel_TypeDef;

typedef enum
{
	ADC_InputSignalSel_PORT0_Pin_0 = 0x0,
	ADC_InputSignalSel_PORT0_Pin_1 = 0x1,
	ADC_InputSignalSel_PORT0_Pin_2 = 0x2,
	ADC_InputSignalSel_PORT0_Pin_3 = 0x3,
	ADC_InputSignalSel_PORT0_Pin_4 = 0x4,
	ADC_InputSignalSel_PORT0_Pin_5 = 0x5,
	ADC_InputSignalSel_PORT0_Pin_6 = 0x6,
	ADC_InputSignalSel_InternalSignalSource = 0x7

} ADC_InputSignalSel_TypeDef;

typedef enum
{
	ADC_InterSigSourceSel_0P5VCC_1VCC = 0x0,
	ADC_InterSigSourceSel_TS = 0x1,
	ADC_InterSigSourceSel_BGR_1P2V = 0x3

} ADC_InterSigSourceSel_TypeDef;

typedef enum
{
	ADC_InterSignalSourceVCCDiv_1VCC = 0x0,
	ADC_InterSignalSourceVCCDiv_0P5VCC = 0x1

} ADC_InterSignalSourceVCCDiv_TypeDef;

typedef enum
{
	ADC_ClkSel_PCLK = 0x0,
	ADC_ClkSel_1_2PCLK = 0x1l,
	ADC_ClkSel_1_4PCLK = 0x2,
	ADC_ClkSel_1_8PCLK = 0x3

} ADC_ClkSel_TypeDef;

typedef enum
{
	ADC_ConvMode_Single = 0x0,
	ADC_ConvMode_Continuous = 0x1

} ADC_ConvMode_TypeDef;

typedef enum
{
	ADC_ResultSel_Result_0 = 0x0,
	ADC_ResultSel_Result_1 = 0x1,
	ADC_ResultSel_Result_2 = 0x2,
	ADC_ResultSel_Result_3 = 0x3,
	ADC_ResultSel_Result_4 = 0x4,
	ADC_ResultSel_Result_5 = 0x5,
	ADC_ResultSel_Result_6 = 0x6,
	ADC_ResultSel_Result_7 = 0x7,	
	ADC_ResultSel_Result_ACC = 0xFF

} ADC_ResultSel_TypeDef;

typedef enum
{
	ADC_PeriphRefModuleSel_1 = 0x0,
	ADC_PeriphRefModuleSel_2 = 0x5

} ADC_PeriphRefModuleSel_TypeDef;

typedef enum
{
	ADC_PeriphRefTrigSource_PORT_0 = 0x01,
	ADC_PeriphRefTrigSource_PORT_1 = 0x02,
	ADC_PeriphRefTrigSource_PORT_2 = 0x03,
	ADC_PeriphRefTrigSource_PORT_3 = 0x04,
	ADC_PeriphRefTrigSource_PORT_4 = 0x05,
	ADC_PeriphRefTrigSource_PORT_5 = 0x06,
	ADC_PeriphRefTrigSource_PORT_6 = 0x07,
	ADC_PeriphRefTrigSource_TIMER_0 = 0x08,
	ADC_PeriphRefTrigSource_TIMER_1 = 0x09,
	ADC_PeriphRefTrigSource_TIMER_2 = 0xA,
	ADC_PeriphRefTrigSource_TIMER_3 = 0x0B,
	ADC_PeriphRefTrigSource_BASETIMER = 0x0C,
	ADC_PeriphRefTrigSource_UART_1 = 0x0D,
	ADC_PeriphRefTrigSource_UART_2 = 0x0E,
	ADC_PeriphRefTrigSource_UART_3 = 0x0F,
	ADC_PeriphRefTrigSource_UART_4 = 0x10,
	ADC_PeriphRefTrigSource_UART_5 = 0x11,
	ADC_PeriphRefTrigSource_UART_6 = 0x12,
	ADC_PeriphRefTrigSource_SPI_1 = 0x13,
	ADC_PeriphRefTrigSource_SPI_2 = 0x14,
	ADC_PeriphRefTrigSource_SPI_3 = 0x15,
	ADC_PeriphRefTrigSource_SPI_4 = 0x16,
	ADC_PeriphRefTrigSource_PCA_1 = 0x17,
	ADC_PeriphRefTrigSource_PCA_2 = 0x18,
	ADC_PeriphRefTrigSource_PCA_3 = 0x19,
	ADC_PeriphRefTrigSource_PCA_4 = 0x1A,
	ADC_PeriphRefTrigSource_VC = 0x1B,
	ADC_PeriphRefTrigSource_LVD = 0x1C,
	ADC_PeriphRefTrigSource_LCD = 0x1D,
	ADC_PeriphRefTrigSource_DMA = 0x1E,
	ADC_PeriphRefTrigSource_RTC = 0x1F,

} ADC_PeriphRefTrigSource_TypeDef;

typedef enum
{
	ADC_ResultAccEn_DISABLE = 0x0,
	ADC_ResultAccEn_ENABLE = 0x1

}	ADC_ResultAccEn_TypeDef;


typedef struct
{
	ADC_ConvMode_TypeDef ADC_ConvMode;

	ADC_ClkSel_TypeDef ADC_ClkSel;

	ADC_RefVoltSel_TypeDef ADC_RefVoltSel;
	ADC_InputSignalSel_TypeDef ADC_InputSignalSel;	
	ADC_InterSigSourceSel_TypeDef	ADC_InterSigSourceSel;	
	ADC_SignalAmpEn_TypeDef	ADC_SignalAmpEn;

	ADC_SampleCycleSel_TypeDef ADC_SampleCycleSel;

	uint8_t ADC_SampleChannelSel;

	ADC_ResultAccEn_TypeDef ADC_ResultAccEn;

	uint8_t ADC_ContinuousSamplePeriod;

} ADC_InitTypeDef;	

void ADC_DeInit(void);
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct);
void ADC_Init(ADC_InitTypeDef* ADC_InitStruct);

void ADC_Cmd(FunctionalState NewState);
void ADC_TempSensorCmd(FunctionalState NewState);
void ADC_SoftwareStartConvCmd(FunctionalState NewState);	 
void ADC_PeriphReflectTrigConvCmd( ADC_PeriphRefModuleSel_TypeDef ADC_PeriphReflectModuleSel, 
	                                 ADC_PeriphRefTrigSource_TypeDef ADC_PeriphRefTrigSource, 
                                   FunctionalState NewState);
void ADC_BGRCmd(FunctionalState NewState);

void ADC_InterSignalSourceVCCConfig(ADC_InterSignalSourceVCCDiv_TypeDef ADC_InterSignalSourceVCCDiv);

uint32_t ADC_GetResult(ADC_ResultSel_TypeDef ADC_ResultSel);
void ADC_SetContinuousSampleCounter(uint8_t ADC_ContinuousSampleCounter);

FlagStatus ADC_GetConvCompletedFlagStatus(void);

ITStatus ADC_GetITStatus(void);
void ADC_ClearITFlag(void);

void ADC_ClearResultAcc(FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_ADC_H */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
