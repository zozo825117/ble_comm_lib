/**
  ******************************************************************************
  * @file    GW32L0xx_lcd.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the LCD
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW32L0XX_LCD_H
#define __GW32L0XX_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

typedef enum
{
	LCD_ITInterval_1Frame = 0x0,
	LCD_ITInterval_2Frame = 0x1,
	LCD_ITInterval_3Frame = 0x2,
	LCD_ITInterval_4Frame = 0x3,
	LCD_ITInterval_5Frame = 0x4,
	LCD_ITInterval_6Frame = 0x5,
	LCD_ITInterval_7Frame = 0x6,
	LCD_ITInterval_8Frame = 0x7,
	LCD_ITInterval_9Frame = 0x8,
	LCD_ITInterval_10Frame = 0x9,
	LCD_ITInterval_11Frame = 0xA,
	LCD_ITInterval_12Frame = 0xB,
	LCD_ITInterval_13Frame = 0xC,
	LCD_ITInterval_14Frame = 0xD,
	LCD_ITInterval_15Frame = 0xE,
	LCD_ITInterval_16Frame = 0xF

} LCD_ITInterval_TypeDef;

typedef enum
{
	LCD_Blinky_Disable = 0x0,
	LCD_Blinky_Enable = 0x1

} LCD_Blinky_TypeDef;

typedef enum
{
	LCD_IRH_Disable = 0x0,
	LCD_IRH_Enable = 0x1

} LCD_IRH_TypeDef;

typedef enum
{
	LCD_IRL_Disable = 0x0,
	LCD_IRL_Enable = 0x1

} LCD_IRL_TypeDef;

typedef enum
{
	LCD_ChargePump_Disable = 0x0,
	LCD_ChargePump_Enable = 0x1

} LCD_ChargePump_TypeDef;

typedef enum
{
	LCD_Mode_StaticsDisplay = 0x0,
	LCD_Mode_2COMDisplay = 0x1,
	LCD_Mode_3COMDisplay = 0x2,
	LCD_Mode_4COMDisplay = 0x3,
	LCD_Mode_6COMDisplay = 0x5,
	LCD_Mode_8COMDisplay = 0x6	

} LCD_Mode_TypeDef;

typedef enum
{
	LCD_Bias_1_3 = 0x0,
	LCD_Bias_1_2 = 0x1

} LCD_Bias_TypeDef;

typedef enum
{
	LCD_ChargePumpClk_2KHz = 0x0,
	LCD_ChargePumpClk_4KHz = 0x1,
	LCD_ChargePumpClk_8KHz = 0x2,
	LCD_ChargePumpClk_16KHz = 0x3

} LCD_ChargePumpClk_TypeDef;

typedef enum
{
	LCD_FrameRefreshRate_64 = 0x0,
	LCD_FrameRefreshRate_128 = 0x1,
	LCD_FrameRefreshRate_256 = 0x2,
	LCD_FrameRefreshRate_512 = 0x3

} LCD_FrameRefreshRate_TypeDef;

typedef enum
{
	LCD_RAML_0 = 0x0,
	LCD_RAML_1 = 0x1,
	LCD_RAML_2 = 0x2,
	LCD_RAML_3 = 0x3,
	LCD_RAML_4 = 0x4,
	LCD_RAML_5 = 0x5,
	LCD_RAML_6 = 0x6,
	LCD_RAML_7 = 0x7

} LCD_RAML_TypeDef;

typedef enum
{
	LCD_RAMH_0 = 0x0,
	LCD_RAMH_1 = 0x1,
	LCD_RAMH_2 = 0x2,
	LCD_RAMH_3 = 0x3,
	LCD_RAMH_4 = 0x4,
	LCD_RAMH_5 = 0x5,
	LCD_RAMH_6 = 0x6,
	LCD_RAMH_7 = 0x7

} LCD_RAMH_TypeDef;

typedef enum
{
	LCD_COM_0 = 0x0,
	LCD_COM_1 = 0x1,
	LCD_COM_2 = 0x2,
	LCD_COM_3 = 0x3,
	LCD_COM_4 = 0x4,
	LCD_COM_5 = 0x5,
	LCD_COM_6 = 0x6,
	LCD_COM_7 = 0x7

} LCD_COM_TypeDef;

typedef struct
{
	LCD_Mode_TypeDef LCD_Mode;
	LCD_Bias_TypeDef LCD_Bias;

	LCD_IRH_TypeDef LCD_IRH;
	LCD_IRL_TypeDef	LCD_IRL;	
	LCD_ChargePump_TypeDef LCD_ChargePump;
	LCD_ChargePumpClk_TypeDef LCD_ChargePumpClk;

	LCD_FrameRefreshRate_TypeDef LCD_FrameRefreshRate;

	LCD_Blinky_TypeDef LCD_Blinky;

	LCD_ITInterval_TypeDef LCD_ITInterval;

} LCD_InitTypeDef;

void LCD_DeInit(void);
void LCD_StructInit(LCD_InitTypeDef* LCD_InitStruct);
void LCD_Init(LCD_InitTypeDef* LCD_InitStruct);
void LCD_Cmd(FunctionalState NewState);

void LCD_ITConfig(FunctionalState NewState);
ITStatus LCD_GetITStatus(void);	 
void LCD_ClearITFlag(void);

void LCD_RAMLInit(LCD_RAML_TypeDef LCD_RAML);
void LCD_RAMHInit(LCD_RAMH_TypeDef LCD_RAMH);

void LCD_SetRAMData(LCD_COM_TypeDef LCD_COM, uint8_t LCD_SEG, uint32_t LCD_RAM_Data);

#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_LCD_H*/

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
