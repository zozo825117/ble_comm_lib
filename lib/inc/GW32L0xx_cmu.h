/**
  ******************************************************************************
  * @file    GW32L0xx_cmu.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the CMU
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW32L0XX_CMU_H
#define __GW32L0XX_CMU_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

typedef enum
{
	CMU_IRC16M_Trim_2M  = 0x2,
	CMU_IRC16M_Trim_4M	= 0x4,
	CMU_IRC16M_Trim_8M	= 0x8,
	CMU_IRC16M_Trim_16M	= 0x16

} CMU_IRC16M_Trim_TypeDef;

typedef enum
{
	CMU_CLKStartUpTime0 = 0x0,
	CMU_CLKStartUpTime1 = 0x1,
	CMU_CLKStartUpTime2 = 0x2,
	CMU_CLKStartUpTime3 = 0x3

} CMU_CLKStartUp_TypeDef;

typedef enum
{
	CMU_HSEDriver0  = 0x0,
	CMU_HSEDriver1  = 0x1,
	CMU_HSEDriver2  = 0x2,
	CMU_HSEDriver3  = 0x3,
	CMU_HSEDriver4  = 0x4,
	CMU_HSEDriver5  = 0x5,
	CMU_HSEDriver6  = 0x6,
	CMU_HSEDriver7  = 0x7

} CMU_HSEDriver_TypeDef;

typedef enum
{
	CMU_LSEDriver0  = 0x0,
	CMU_LSEDriver1  = 0x1,
	CMU_LSEDriver2  = 0x2,
	CMU_LSEDriver3  = 0x3,
	CMU_LSEDriver4  = 0x4,
	CMU_LSEDriver5  = 0x5,
	CMU_LSEDriver6  = 0x6,
	CMU_LSEDriver7  = 0x7,	
	CMU_LSEDriver8  = 0x8,
	CMU_LSEDriver9  = 0x9,
	CMU_LSEDriver10 = 0xA,	
	CMU_LSEDriver11 = 0xB,
	CMU_LSEDriver12 = 0xC,
	CMU_LSEDriver13 = 0xD,	
	CMU_LSEDriver14 = 0xE,
	CMU_LSEDriver15 = 0xF

} CMU_LSEDriver_TypeDef;

typedef enum
{	
	CMU_SysClkSource_HSI = CMU_SYSCLK0_SYSCLK_SEL_IRC16M,
	CMU_SysClkSource_HSE = CMU_SYSCLK0_SYSCLK_SEL_XHFOSC,
	CMU_SysClkSource_LSI = CMU_SYSCLK0_SYSCLK_SEL_IRC38K,
	CMU_SysClkSource_LSE = CMU_SYSCLK0_SYSCLK_SEL_XLFOSC

} CMU_SysClkSource_TypeDef;

#define IS_CMU_SYSCLK_SOURCE(SOURCE)     ( ((SOURCE) == CMU_SysClkSource_HSI) || \
                                           ((SOURCE) == CMU_SysClkSource_HSE) || \
                                           ((SOURCE) == CMU_SysClkSource_LSI) || \
                                           ((SOURCE) == CMU_SysClkSource_LSE) )

#define CMU_SYSCLK_Div1                  CMU_SYSCLK0_AHB_CLK_DIV_DIV1
#define CMU_SYSCLK_Div2                  CMU_SYSCLK0_AHB_CLK_DIV_DIV2
#define CMU_SYSCLK_Div4                  CMU_SYSCLK0_AHB_CLK_DIV_DIV4
#define CMU_SYSCLK_Div8                  CMU_SYSCLK0_AHB_CLK_DIV_DIV8
#define CMU_SYSCLK_Div16                 CMU_SYSCLK0_AHB_CLK_DIV_DIV16
#define CMU_SYSCLK_Div64                 CMU_SYSCLK0_AHB_CLK_DIV_DIV64
#define CMU_SYSCLK_Div128                CMU_SYSCLK0_AHB_CLK_DIV_DIV128
#define IS_CMU_HCLK(HCLK)                ( ((HCLK) == CMU_SYSCLK_Div1) || ((HCLK) == CMU_SYSCLK_Div2) || \
																					 ((HCLK) == CMU_SYSCLK_Div4) || ((HCLK) == CMU_SYSCLK_Div8) || \
																				   ((HCLK) == CMU_SYSCLK_Div16) || ((HCLK) == CMU_SYSCLK_Div64) || \
																				   ((HCLK) == CMU_SYSCLK_Div128) )

#define CMU_HCLK_Div1                    CMU_SYSCLK0_APB_CLK_DIV_DIV1
#define CMU_HCLK_Div2                    CMU_SYSCLK0_APB_CLK_DIV_DIV2
#define CMU_HCLK_Div4                    CMU_SYSCLK0_APB_CLK_DIV_DIV4
#define CMU_HCLK_Div8                    CMU_SYSCLK0_APB_CLK_DIV_DIV8
#define IS_CMU_PCLK(PCLK) 							 ( ((PCLK) == CMU_HCLK_Div1) || ((PCLK) == CMU_HCLK_Div2) || \
																					 ((PCLK) == CMU_HCLK_Div4) || ((PCLK) == CMU_HCLK_Div8) )

#define CMU_LSE_OFF                      CMU_SYSCLK0_XLF_EN_LSEOFF
#define CMU_LSE_ON                       CMU_SYSCLK0_XLF_EN_LSEON
#define IS_CMU_LSE(LSE) 								 ( ((LSE) == CMU_LSE_OFF) || ((LSE) == CMU_LSE_ON) )

#define CMU_LSI_OFF                      CMU_SYSCLK0_IRC38K_EN_LSIOFF
#define CMU_LSI_ON                       CMU_SYSCLK0_IRC38K_EN_LSION
#define IS_CMU_LSI(LSI) 								 ( ((LSI) == CMU_LSI_OFF) || ((LSI) == CMU_LSI_ON) )

#define CMU_HSE_OFF                      CMU_SYSCLK0_XHF_EN_HSEOFF
#define CMU_HSE_ON                       CMU_SYSCLK0_XHF_EN_HSEON
#define IS_CMU_HSE(HSE) 								 ( ((HSE) == CMU_HSE_OFF) || ((HSE) == CMU_HSE_ON) )

#define CMU_HSI_OFF                      CMU_SYSCLK0_IRC16M_EN_HSIOFF
#define CMU_HSI_ON                       CMU_SYSCLK0_IRC16M_EN_HSION
#define IS_CMU_HSI(HSI) 							   ( ((HSI) == CMU_HSI_OFF) || ((HSI) == CMU_HSI_ON) )							

#define CMU_IRC40K_OFF                   CMU_SYSCLK1_IRC40K_ENOFF
#define CMU_IRC40K_ON                    CMU_SYSCLK1_IRC40K_ENON
#define IS_CMU_IRC40K(IRC40K)            ( ((IRC40K) == CMU_SYSCLK1_IRC40K_ENOFF) || ((IRC40K) == CMU_SYSCLK1_IRC40K_ENON) )

#define CMU_LPUARTCLK_IRC38K             CMU_SYSCLK1_LPUART_CS_IRC38K
#define CMU_LPUARTCLK_LSE                CMU_SYSCLK1_LPUART_CS_LSE 

#define CMU_LCDCLK_IRC38K                CMU_SYSCLK1_LCD_CS_IRC38K 		    	
#define CMU_LCDCLK_LSE                   CMU_SYSCLK1_LCD_CS_LSE 					

#define CMU_WDTCLK_IRC40K                CMU_SYSCLK1_WDT_CS_IRC40K 				
#define CMU_WDTCLK_LSE                   CMU_SYSCLK1_WDT_CS_LSE 				
#define CMU_WDTCLK_IRC38K                CMU_SYSCLK1_WDT_CS_IRC38K 		    	

#define CMU_BASETMCLK_IRC38K             CMU_SYSCLK1_BASETM_CS_IRC38K 		    
#define CMU_BASETMCLK_LSE                CMU_SYSCLK1_BASETM_CS_LSE 				

#define CMU_RTCCLK_IRC38K                CMU_SYSCLK1_RTC_CS_IRC38K 		    	
#define CMU_RTCCLK_LSE                   CMU_SYSCLK1_RTC_CS_LSE

#define CMU_APBPeriph0_RNG               CMU_PERI_CLK0_RNG_EN								
#define CMU_APBPeriph0_DES               CMU_PERI_CLK0_DES_EN
#define CMU_APBPeriph0_ADC               CMU_PERI_CLK0_ADC_EN
#define CMU_APBPeriph0_BUZZER            CMU_PERI_CLK0_BUZZER_EN
#define CMU_APBPeriph0_CRC               CMU_PERI_CLK0_CRC_EN
#define CMU_APBPeriph0_DMA               CMU_PERI_CLK0_DMA_EN
#define CMU_APBPeriph0_FLASH             CMU_PERI_CLK0_FLASH_EN
#define CMU_APBPeriph0_PCA4              CMU_PERI_CLK0_PCA4_EN
#define CMU_APBPeriph0_PCA3              CMU_PERI_CLK0_PCA3_EN
#define CMU_APBPeriph0_PCA2              CMU_PERI_CLK0_PCA2_EN
#define CMU_APBPeriph0_PCA1              CMU_PERI_CLK0_PCA1_EN
#define CMU_APBPeriph0_TIMER4            CMU_PERI_CLK0_TIMER4_EN
#define CMU_APBPeriph0_TIMER3            CMU_PERI_CLK0_TIMER3_EN
#define CMU_APBPeriph0_TIMER2            CMU_PERI_CLK0_TIMER2_EN	
#define CMU_APBPeriph0_TIMER1            CMU_PERI_CLK0_TIMER1_EN	
#define CMU_APBPeriph0_SCI7816           CMU_PERI_CLK0_SCI7816_EN
#define CMU_APBPeriph0_I2C2              CMU_PERI_CLK0_I2C2_EN											
#define CMU_APBPeriph0_I2C1              CMU_PERI_CLK0_I2C1_EN
#define CMU_APBPeriph0_SPI4              CMU_PERI_CLK0_SPI4_EN
#define CMU_APBPeriph0_SPI3              CMU_PERI_CLK0_SPI3_EN
#define CMU_APBPeriph0_SPI2              CMU_PERI_CLK0_SPI2_EN
#define CMU_APBPeriph0_SPI1              CMU_PERI_CLK0_SPI1_EN
#define CMU_APBPeriph0_UART6             CMU_PERI_CLK0_UART6_EN
#define CMU_APBPeriph0_UART5             CMU_PERI_CLK0_UART5_EN
#define CMU_APBPeriph0_UART4             CMU_PERI_CLK0_UART4_EN
#define CMU_APBPeriph0_UART3             CMU_PERI_CLK0_UART3_EN
#define CMU_APBPeriph0_UART2             CMU_PERI_CLK0_UART2_EN
#define CMU_APBPeriph0_UART1             CMU_PERI_CLK0_UART1_EN

#define CMU_APBPeriph1_LCD               CMU_PERI_CLK1_LCD_EN				
#define CMU_APBPeriph1_WDT               CMU_PERI_CLK1_WDT_EN					
#define CMU_APBPeriph1_BASETM            CMU_PERI_CLK1_BASETM_EN				
#define CMU_APBPeriph1_RTC               CMU_PERI_CLK1_RTC_EN					
#define CMU_APBPeriph1_PORT              CMU_PERI_CLK1_PORT_EN				
#define CMU_APBPeriph1_BKRAM             CMU_PERI_CLK1_BKRAM_EN					

#define CMU_FLAG_HSIRDY                  CMU_IRC16M_CTRL_IRC16M_STABLE
#define CMU_FLAG_HSERDY                  CMU_XHF_CTRL_XHF_STABLE
#define CMU_FLAG_LSERDY                  CMU_XLF_CTRL_XLF_STABLE
#define CMU_FLAG_LSIRDY                  CMU_IRC38K_CTRL_IRC38K_STABLE

void CMU_HSECmd(CMU_CLKStartUp_TypeDef CMU_CLKStartUpTime, CMU_HSEDriver_TypeDef CMU_HSEDriver, uint16_t CMU_HSE_STATE);
void CMU_HSIConfig(CMU_IRC16M_Trim_TypeDef CMU_IRC16M_Trim, uint16_t CMU_HSI_STATE);
void CMU_LSEConfig(CMU_CLKStartUp_TypeDef CMU_CLKStartUpTime, CMU_LSEDriver_TypeDef CMU_LSEDriver, uint16_t CMU_LSE_STATE);
void CMU_LSIConfig(CMU_CLKStartUp_TypeDef CMU_CLKStartUpTime, uint16_t CMU_LSI_STATE);
void CMU_IRC40KConfig(uint16_t CMU_IRC40K_STATE);

void CMU_SysClkConfig(CMU_SysClkSource_TypeDef CMU_SysClkSource);
CMU_SysClkSource_TypeDef CMU_GetSysClkSource(void);

void CMU_HCLKConfig(uint32_t CMU_SYSCLK_Div);
void CMU_PCLKConfig(uint32_t CMU_HCLK_Div);

uint32_t CMU_GetSysClkFreq(void);
uint32_t CMU_GetHCLKFreq(void);
uint32_t CMU_GetPCLKFreq(void);

void CMU_LPUARTCLKConfig(uint8_t CMU_LPUART_CLK);
void CMU_LCDCLKConfig(uint8_t CMU_LCD_CLK);
void CMU_WDTCLKConfig(uint8_t CMU_WDT_CLK);
void CMU_BASETMCLKConfig(uint8_t CMU_BASETM_CLK);
void CMU_RTCCLKConfig(uint8_t CMU_RTC_CLK);
void CMU_LockUpCmd(FunctionalState NewState);
void CMU_RAM_PARCmd(FunctionalState NewState);

void CMU_APBPeriph0ClockCmd(uint32_t CMU_APBPeriph0, FunctionalState NewState);
void CMU_APBPeriph1ClockCmd(uint8_t CMU_APBPeriph1, FunctionalState NewState);

FlagStatus CMU_WaitForSysClkStartUp(CMU_SysClkSource_TypeDef CMU_SysClkSource);

#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_CMU_H */

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
