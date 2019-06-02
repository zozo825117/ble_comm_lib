/**
  ******************************************************************************
  * @file    GW32L0xx_port.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the PORT 
  *          firmware library. 
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *

  ******************************************************************************
  */

#ifndef __GW32L0XX_PORT_H
#define __GW32L0XX_PORT_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"


#define IS_PORT_ALL_PERIPH(PERIPH) ( ((PERIPH) == PORT_0) || \
                                     ((PERIPH) == PORT_1) || \
                                     ((PERIPH) == PORT_2) || \
                                     ((PERIPH) == PORT_3) || \
                                     ((PERIPH) == PORT_4) || \
                                     ((PERIPH) == PORT_5) || \
									                   ((PERIPH) == PORT_6) )

typedef enum
{
  PORT_Mode_OUT = 0x0,
  PORT_Mode_IN  = 0x1	

} PORT_Mode_TypeDef;

#define IS_PORT_MODE(MODE)  ( ((MODE) == PORT_Mode_IN) || ((MODE) == PORT_Mode_OUT) )

typedef enum
{ 
  PORT_OutType_PP = 0x0,
  PORT_OutType_OD = 0x1

} PORT_OutType_TypeDef;

#define IS_PORT_OUTTYPE(OUTTYPE) ( ((OUTTYPE) == PORT_OutType_PP) || ((OUTTYPE) == PORT_OutType_OD) )

typedef enum
{
  PORT_PH_NoPullHigh = 0x0,
  PORT_PH_PullHigh = 0x1

} PORT_PH_TypeDef;

#define IS_PORT_PH(PH) ( ((PH) == PORT_PH_NoPullHigh) || ((PH) == PORT_PH_PullHigh) )

typedef enum
{
  PORT_DS_DriveSinkNormal = 0x0,
  PORT_DS_DriveSinkStrength = 0x1

} PORT_DS_TypeDef;

#define IS_PORT_DS(DS) ( ((DS) == PORT_DS_DriveSinkNormal) || ((DS) == PORT_DS_DriveSinkStrength) )

typedef enum
{
  PORT_Properity_Digital = 0x0,
  PORT_Properity_Analog = 0x1

} PORT_Properity_TypeDef;

#define IS_PORT_PROPERITY(PROPERITY) ( ((PROPERITY) == PORT_Properity_Digital) || ((PROPERITY) == PORT_Properity_Analog) )

typedef struct
{
  uint32_t PORT_Pin;              

  PORT_Properity_TypeDef PORT_Properity;

  PORT_Mode_TypeDef PORT_Mode;     

  PORT_OutType_TypeDef PORT_OutType;  

  PORT_PH_TypeDef PORT_PullHigh;     

  PORT_DS_TypeDef PORT_DriveSink;

} PORT_InitTypeDef;

typedef enum
{
	PORT_EXTI_InputSource_NO = 0x0,

	PORT_EXTI_InputSource_Level = 0x1,
	PORT_EXTI_InputSource_Edge = 0x2

} PORT_EXTI_InputSourceSel_TypeDef;

#define IS_PORT_EXTI_INPUTSOURCESEL(SEL) ( ((SEL) == PORT_EXTI_InputSource_Level) || \
																					 ((SEL) == PORT_EXTI_InputSource_Edge) )

typedef enum
{
	PORT_EXTI_Trigger_NO	= 0x0,

  PORT_EXTI_EdgeTrigger_Falling = 0x1,
  PORT_EXTI_EdgeTrigger_Rising = 0x2,
  PORT_EXTI_EdgeTrigger_Falling_Rising = 0x3,

  PORT_EXTI_LevelTrigger_Low = 0x1,
  PORT_EXTI_LevelTrigger_High = 0x2,
  PORT_EXTI_LevelTrigger_Low_High = 0x3

} PORT_EXTI_Trigger_TypeDef;

#define IS_PORT_EXTI_TRIGGER_EDGE(TRIGGER) ( ((TRIGGER) == PORT_EXTI_EdgeTrigger_Falling) || \
																			       ((TRIGGER) == PORT_EXTI_EdgeTrigger_Rising) || \
                                             ((TRIGGER) == PORT_EXTI_EdgeTrigger_Falling_Rising) )
#define IS_PORT_EXTI_TRIGGER_LEVEL(TRIGGER) ( ((TRIGGER) == PORT_EXTI_LevelTrigger_Low) || \
								                              ((TRIGGER) == PORT_EXTI_LevelTrigger_High) || \
								                              ((TRIGGER) == PORT_EXTI_LevelTrigger_Low_High) )

typedef struct
{ 
	PORT_EXTI_InputSourceSel_TypeDef PORT_EXTI_InputSource;
  PORT_EXTI_Trigger_TypeDef PORT_EXTI_Trigger; 
  FunctionalState PORT_EXTI_Cmd;

} PORT_EXTI_InitTypeDef;

typedef enum
{ 
  Bit_RESET = 0,
  Bit_SET

} BitAction;

#define IS_PORT_BIT_ACTION(ACTION) ( ((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET) )

#define PORT_Pin_0                 ((uint16_t)0x0001)  /*!< Pin 0 selected    */
#define PORT_Pin_1                 ((uint16_t)0x0002)  /*!< Pin 1 selected    */
#define PORT_Pin_2                 ((uint16_t)0x0004)  /*!< Pin 2 selected    */
#define PORT_Pin_3                 ((uint16_t)0x0008)  /*!< Pin 3 selected    */
#define PORT_Pin_4                 ((uint16_t)0x0010)  /*!< Pin 4 selected    */
#define PORT_Pin_5                 ((uint16_t)0x0020)  /*!< Pin 5 selected    */
#define PORT_Pin_6                 ((uint16_t)0x0040)  /*!< Pin 6 selected    */
#define PORT_Pin_7                 ((uint16_t)0x0080)  /*!< Pin 7 selected    */
#define PORT_Pin_8                 ((uint16_t)0x0100)  /*!< Pin 8 selected    */
#define PORT_Pin_9                 ((uint16_t)0x0200)  /*!< Pin 9 selected    */
#define PORT_Pin_10                ((uint16_t)0x0400)  /*!< Pin 10 selected   */
#define PORT_Pin_11                ((uint16_t)0x0800)  /*!< Pin 11 selected   */
#define PORT_Pin_12                ((uint16_t)0x1000)  /*!< Pin 12 selected   */
#define PORT_Pin_13                ((uint16_t)0x2000)  /*!< Pin 13 selected   */
#define PORT_Pin_14                ((uint16_t)0x4000)  /*!< Pin 14 selected   */
#define PORT_Pin_15                ((uint16_t)0x8000)  /*!< Pin 15 selected   */
#define PORT_Pin_All               ((uint16_t)0xFFFF)  /*!< All pins selected */

#define IS_PORT_PIN(PIN) ((PIN) != (uint16_t)0x00)

#define IS_GET_PORT_PIN(PIN) ( ((PIN) == PORT_Pin_0) || \
                               ((PIN) == PORT_Pin_1) || \
                               ((PIN) == PORT_Pin_2) || \
                               ((PIN) == PORT_Pin_3) || \
                               ((PIN) == PORT_Pin_4) || \
                               ((PIN) == PORT_Pin_5) || \
                               ((PIN) == PORT_Pin_6) || \
                               ((PIN) == PORT_Pin_7) || \
                               ((PIN) == PORT_Pin_8) || \
                               ((PIN) == PORT_Pin_9) || \
                               ((PIN) == PORT_Pin_10) || \
                               ((PIN) == PORT_Pin_11) || \
                               ((PIN) == PORT_Pin_12) || \
                               ((PIN) == PORT_Pin_13) || \
                               ((PIN) == PORT_Pin_14) || \
                               ((PIN) == PORT_Pin_15) )

#define PORT_PinSource0            ((uint8_t)0x00)
#define PORT_PinSource1            ((uint8_t)0x01)
#define PORT_PinSource2            ((uint8_t)0x02)
#define PORT_PinSource3            ((uint8_t)0x03)
#define PORT_PinSource4            ((uint8_t)0x04)
#define PORT_PinSource5            ((uint8_t)0x05)
#define PORT_PinSource6            ((uint8_t)0x06)
#define PORT_PinSource7            ((uint8_t)0x07)
#define PORT_PinSource8            ((uint8_t)0x08)
#define PORT_PinSource9            ((uint8_t)0x09)
#define PORT_PinSource10           ((uint8_t)0x0A)
#define PORT_PinSource11           ((uint8_t)0x0B)
#define PORT_PinSource12           ((uint8_t)0x0C)
#define PORT_PinSource13           ((uint8_t)0x0D)
#define PORT_PinSource14           ((uint8_t)0x0E)
#define PORT_PinSource15           ((uint8_t)0x0F)

#define IS_PORT_PIN_SOURCE(PINSOURCE) ( ((PINSOURCE) == PORT_PinSource0) || \
                                        ((PINSOURCE) == PORT_PinSource1) || \
                                        ((PINSOURCE) == PORT_PinSource2) || \
                                        ((PINSOURCE) == PORT_PinSource3) || \
                                        ((PINSOURCE) == PORT_PinSource4) || \
                                        ((PINSOURCE) == PORT_PinSource5) || \
                                        ((PINSOURCE) == PORT_PinSource6) || \
                                        ((PINSOURCE) == PORT_PinSource7) || \
                                        ((PINSOURCE) == PORT_PinSource8) || \
                                        ((PINSOURCE) == PORT_PinSource9) || \
                                        ((PINSOURCE) == PORT_PinSource10) || \
                                        ((PINSOURCE) == PORT_PinSource11) || \
                                        ((PINSOURCE) == PORT_PinSource12) || \
                                        ((PINSOURCE) == PORT_PinSource13) || \
                                        ((PINSOURCE) == PORT_PinSource14) || \
                                        ((PINSOURCE) == PORT_PinSource15) )

#define PORT_AF_0            ((uint8_t)0x00) /* GPIO */

#define PORT_AF_1            ((uint8_t)0x01) /* UART1, UART2, UART3, UART4, UART5, UART6 */

#define PORT_AF_2            ((uint8_t)0x02) /* IrDA1, IrDA2, UART3, UART5, UART6, RTC */

#define PORT_AF_3            ((uint8_t)0x03) /* SPI1_M, SPI2_M, SPI3_M, SPI4_M */

#define PORT_AF_4            ((uint8_t)0x04) /* SPI1_S, SPI2_S, SPI3_S, SPI4_S */

#define PORT_AF_5            ((uint8_t)0x05) /* PCLK, IRC16M, IRC38K, ADC_CLK_OUT, I2C1, I2C2, 7816, VC, LVD, BASETIMER, HCLK, XTAL32K */

#define PORT_AF_6            ((uint8_t)0x06) /* HCLK, XTAL32K, XTAL32M, IRC38K, TIMER1, TIMER2, TIMER3, TIMER4, VC, LVD, BUZZER */

#define PORT_AF_7            ((uint8_t)0x07) /* PCA1, PCA2, PCA3, PCA4, VC, LVD, TIMER1, TIMER2, TIMER3, TIMER4 */

#define IS_PORT_AF(AF)     ( ((AF) == PORT_AF_0) || ((AF) == PORT_AF_1) || \
														 ((AF) == PORT_AF_2) || ((AF) == PORT_AF_3) || \
														 ((AF) == PORT_AF_4) || ((AF) == PORT_AF_5) || \
														 ((AF) == PORT_AF_6) || ((AF) == PORT_AF_7) )


void PORT_DeInit(void);
void PORT_Init(PORT_TypeDef* PORTx, PORT_InitTypeDef* PORT_InitStruct);
void PORT_StructInit(PORT_InitTypeDef* PORT_InitStruct);
void PORT_PinLockConfig(PORT_TypeDef* PORTx, uint16_t PORT_Pin);

BitAction PORT_ReadInputDataBit(PORT_TypeDef* PORTx, uint16_t PORT_Pin);
uint16_t PORT_ReadInputData(PORT_TypeDef* PORTx);
BitAction PORT_ReadOutputDataBit(PORT_TypeDef* PORTx, uint16_t PORT_Pin);
uint16_t PORT_ReadOutputData(PORT_TypeDef* PORTx);
void PORT_SetBits(PORT_TypeDef* PORTx, uint16_t PORT_Pin);
void PORT_ResetBits(PORT_TypeDef* PORTx, uint16_t PORT_Pin);
void PORT_WriteBit(PORT_TypeDef* PORTx, uint16_t PORT_Pin, BitAction BitVal);
void PORT_Write(PORT_TypeDef* PORTx, uint16_t PortVal);
void PORT_ToggleBit(PORT_TypeDef* PORTx, uint16_t PORT_Pin);

// PORT_EXIT
void PORT_EXTI_Init(PORT_TypeDef* PORTx, uint8_t PORT_PinSource, PORT_EXTI_InitTypeDef* PORT_EXTI_InitStruct);
void PORT_EXTI_StructInit(PORT_EXTI_InitTypeDef* PORT_EXTI_InitStruct);

ITStatus PORT_EXTI_GetITStatus(PORT_TypeDef* PORTx, uint16_t PORT_Pin);
void PORT_EXTI_ClearITFlag(PORT_TypeDef* PORTx, uint16_t PORT_Pin);
void PORT_EXTI_ITConfig(PORT_TypeDef* PORTx, uint16_t PORT_Pin, FunctionalState NewState);

// PORT_AF
void PORT_PinAFConfig(PORT_TypeDef* PORTx, uint8_t PORT_PinSource, uint8_t PORT_AF);

#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_PORT_H */


/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
