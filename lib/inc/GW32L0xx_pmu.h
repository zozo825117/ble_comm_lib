/**
  ******************************************************************************
  * @file    GW32L0xx_pmu.h
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file contains all the functions prototypes for the PMU
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GW32L0XX_PMU_H
#define __GW32L0XX_PMU_H

#ifdef __cplusplus
 extern "C" {
#endif

#include "GW32L.h"

typedef enum
{
	PMU_EnterMode_Now = 0x0,
	PMU_EnterMode_AfterIsrRoute = 0x1

} PMU_EnterMode_TypeDef;	

void PMU_EnterSleepMode(PMU_EnterMode_TypeDef PMU_EnterSleep);
void PMU_EnterDeepSleep3Mode(PMU_EnterMode_TypeDef PMU_EnterDeepSleep3);
void PMU_EnterDeepSleep4Mode(PMU_EnterMode_TypeDef PMU_EnterDeepSleep4);
void PMU_EnterPowerDown3Mode(void);
void PMU_EnterPowerDown4Mode(void);


#ifdef __cplusplus
}
#endif

#endif /* __GW32L0XX_PMU_H*/

/**
  * @}
  */

/**
  * @}
  */ 

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
