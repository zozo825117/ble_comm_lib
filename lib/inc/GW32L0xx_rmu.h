/**
  ******************************************************************************
  * @file    GW32L0xx_rmu.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the RMU
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW32L0XX_RMU_H
#define __GW32L0XX_RMU_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

#define RMU_APBPeriph0_RNG                  RMU_PERI_RESET0_RNG 							
#define RMU_APBPeriph0_DES                  RMU_PERI_RESET0_DES
#define RMU_APBPeriph0_ADC                  RMU_PERI_RESET0_ADC
#define RMU_APBPeriph0_BUZZER               RMU_PERI_RESET0_BUZZER
#define RMU_APBPeriph0_CRC                  RMU_PERI_RESET0_CRC
#define RMU_APBPeriph0_DMA                  RMU_PERI_RESET0_DMA
#define RMU_APBPeriph0_FLASH                RMU_PERI_RESET0_FLASH
#define RMU_APBPeriph0_PCA4                 RMU_PERI_RESET0_PCA4
#define RMU_APBPeriph0_PCA3                 RMU_PERI_RESET0_PCA3
#define RMU_APBPeriph0_PCA2                 RMU_PERI_RESET0_PCA2
#define RMU_APBPeriph0_PCA1                 RMU_PERI_RESET0_PCA1
#define RMU_APBPeriph0_TIMER4               RMU_PERI_RESET0_TIMER4
#define RMU_APBPeriph0_TIMER3               RMU_PERI_RESET0_TIMER3
#define RMU_APBPeriph0_TIMER2               RMU_PERI_RESET0_TIMER2
#define RMU_APBPeriph0_TIMER1               RMU_PERI_RESET0_TIMER1	
#define RMU_APBPeriph0_SCI7816              RMU_PERI_RESET0_SCI7816
#define RMU_APBPeriph0_I2C2                 RMU_PERI_RESET0_I2C2											
#define RMU_APBPeriph0_I2C1                 RMU_PERI_RESET0_I2C1
#define RMU_APBPeriph0_SPI4                 RMU_PERI_RESET0_SPI4
#define RMU_APBPeriph0_SPI3                 RMU_PERI_RESET0_SPI3
#define RMU_APBPeriph0_SPI2                 RMU_PERI_RESET0_SPI2
#define RMU_APBPeriph0_SPI1                 RMU_PERI_RESET0_SPI1
#define RMU_APBPeriph0_UART6                RMU_PERI_RESET0_UART6
#define RMU_APBPeriph0_UART5                RMU_PERI_RESET0_UART5
#define RMU_APBPeriph0_UART4                RMU_PERI_RESET0_UART4
#define RMU_APBPeriph0_UART3                RMU_PERI_RESET0_UART3
#define RMU_APBPeriph0_UART2                RMU_PERI_RESET0_UART2
#define RMU_APBPeriph0_UART1                RMU_PERI_RESET0_UART1

#define RMU_APBPeriph1_LCD                  RMU_PERI_RESET1_LCD				
#define RMU_APBPeriph1_WDT                  RMU_PERI_RESET1_WDT					
#define RMU_APBPeriph1_BASETIMER            RMU_PERI_RESET1_BASETIMER			
#define RMU_APBPeriph1_RTC                  RMU_PERI_RESET1_RTC					
#define RMU_APBPeriph1_PORT                 RMU_PERI_RESET1_PORT				
#define RMU_APBPeriph1_BKRAM                RMU_PERI_RESET1_BKRAM	 

typedef enum
{
	RMU_PDModeResetSource_WDTInt = RMU_RESET_FLAG_WDT_PD,
	RMU_PDModeResetSource_VCInt = RMU_RESET_FLAG_VC_PD,
	RMU_PDModeResetSource_RTCInt = RMU_RESET_FLAG_RTC_PD,
	RMU_PDModeResetSource_LVDInt = RMU_RESET_FLAG_LVD_PD,
	RMU_PDModeResetSource_PORTInt = RMU_RESET_FLAG_PORT_PD,
	RMU_PDModeResetSource_BASETIMERInt = RMU_RESET_FLAG_BASETIMER_PD,
	RMU_ResetSource_PDMode = RMU_RESET_FLAG_PD,
	RMU_ResetSource_LVD = RMU_RESET_FLAG_LVD_RST,
	RMU_ResetSource_SYSREQ = RMU_RESET_FLAG_SYSREQ_RST,	
	RMU_ResetSource_LOOKUP = RMU_RESET_FLAG_LOOKUP_RST,
	RMU_ResetSource_PCA = RMU_RESET_FLAG_PCA_RST,
	RMU_ResetSource_WDT = RMU_RESET_FLAG_WDT_RST,
	RMU_ResetSource_RSTPin = RMU_RESET_FLAG_RSTP,	
	RMU_ResetSource_CORE_POR = RMU_RESET_FLAG_CORE_POR,
	RMU_ResetSource_AO_POR = RMU_RESET_FLAG_AO_POR	

} RMU_ResetSource_TypeDef;

FlagStatus RMU_GetResetFlag(RMU_ResetSource_TypeDef RMU_ResetSource);
void RMU_ClearResetFlag(RMU_ResetSource_TypeDef RMU_ResetSource);

void RMU_Periph0ResetCmd(uint32_t RMU_Periph0, FunctionalState NewState);
void RMU_Periph1ResetCmd(uint8_t RMU_Periph1, FunctionalState NewState);

#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_RMU_H*/

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/

