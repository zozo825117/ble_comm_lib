/**
  ******************************************************************************
  * @file    GW32L0xx_conf.h 
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   Library configuration file.
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *

  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW32L0XX_CONF_H
#define __GW32L0XX_CONF_H

/* Includes ------------------------------------------------------------------*/
/* Comment the line below to disable peripheral header file inclusion */
#include "GW32L0xx_port.h"
#include "GW32L0xx_cmu.h"
#include "GW32L0xx_uart.h"
#include "GW32L0xx_i2c.h"
#include "GW32L0xx_dma.h"
#include "GW32L0xx_spi.h"
#include "GW32L0xx_timer.h"
#include "GW32L0xx_pca.h"
#include "GW32L0xx_rtc.h"
#include "GW32L0xx_wdt.h"
#include "GW32L0xx_adc.h"
#include "GW32L0xx_vc.h"
#include "GW32L0xx_lvd.h"
#include "GW32L0xx_flash.h"
#include "GW32L0xx_ram.h"
#include "GW32L0xx_buzzer.h"
#include "GW32L0xx_crc.h"
#include "GW32L0xx_des.h"
#include "GW32L0xx_rng.h"
#include "GW32L0xx_lcd.h"
#include "GW32L0xx_pmu.h"
#include "GW32L0xx_rmu.h"
#include "GW32L0xx_systick.h"
#include "GW32L0xx_misc.h"

//
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Uncomment the line below to expanse the "assert_param" macro in the 
   Standard Peripheral Library drivers code */

// #define USE_FULL_ASSERT    1

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ( (expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__) )
/* Exported functions ------------------------------------------------------- */
	void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

#endif /* __GW32L0XX__CONF_H */

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
