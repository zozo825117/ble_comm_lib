/**
  ******************************************************************************
  * @file    GW32L0xx_cmu.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_cmu.h"

/**
  * @param  CMU_HSE: specifies the new state of the HSE.
  *         This parameter can be one of the following values:
  *		@arg 	CMU_HSE_OFF: turn OFF the HSE oscillator
  *   @arg 	CMU_HSE_ON: turn ON the HSE oscillator
  * @retval None
  */
void CMU_HSECmd(CMU_CLKStartUp_TypeDef CMU_CLKStartUpTime, CMU_HSEDriver_TypeDef CMU_HSEDriver, uint16_t CMU_HSE_STATE)
{	
	if (CMU_HSE_STATE != CMU_HSE_OFF)
	{
		/* Store value of XHF_CTRL register */ 
		volatile uint32_t tmpreg = XHF_CTRL;
		
		/* Clear STARTUP and DRIVER bit to refresh */
		tmpreg &= ~(CMU_XHF_CTRL_XHF_STARTUP | CMU_XHF_CTRL_XHF_DRIVER);
		
		/* Fill STARTUP and DRIVER bit with specified parameters */
	  tmpreg |= ( (CMU_CLKStartUpTime << 3) | CMU_HSEDriver );
		
		/* Refresh new value of XHF_CTRL register */
		XHF_CTRL = tmpreg;
		
		do
		{
			/* Enable HSE clock */
			SYSCLK0 |= CMU_SYSCLK0_XHF_EN;
			
		} while ( (SYSCLK0 & CMU_SYSCLK0_XHF_EN) != CMU_SYSCLK0_XHF_EN );
	}
	else
	{
		do
		{
			/* Disable HSE clock */
			SYSCLK0 &= ~CMU_SYSCLK0_XHF_EN;
			
		} while ( (SYSCLK0 & CMU_SYSCLK0_XHF_EN) == CMU_SYSCLK0_XHF_EN );
	}
}

/**
  * @param  CMU_HSI: specifies the new state of the HSI.
  *         This parameter can be one of the following values:
  * 	@arg  CMU_HSI_OFF: turn OFF the HSI oscillator
  *   @arg  CMU_HSI_ON: turn ON the HSI oscillator
  * @retval None
  */
void CMU_HSIConfig(CMU_IRC16M_Trim_TypeDef CMU_IRC16M_Trim, uint16_t CMU_HSI_STATE)
{
	if (CMU_HSI_STATE != CMU_HSI_OFF)
	{
		/* Store value of IRC16M_CTRL register */
		uint32_t tmpreg = IRC16M_CTRL;
		
		/* Clear TRIM bits to refresh */
		tmpreg &= ~CMU_IRC16M_CTRL_IRC16M_TRIM;

		#ifndef __TEST_CHIP	
		/* Fill value of TRIM with specified paramters */
		tmpreg |= (uint8_t)( (CMU_IRC16M_Trim == CMU_IRC16M_Trim_16M) ? (CAL0 >> 0) : \
												 (CMU_IRC16M_Trim == CMU_IRC16M_Trim_8M)  ? (CAL0 >> 8) : \
												 (CMU_IRC16M_Trim == CMU_IRC16M_Trim_4M)  ? (CAL1 >> 0) : (CAL1 >> 8) );
		#else
		/* Fill value of TRIM with specified paramters */		
		tmpreg |= 0xDF;	
		#endif
	
		/* Refresh value of IRC16M_CTRL register */
		IRC16M_CTRL = tmpreg;

		do
		{
			/* Enable HSI clock */
			SYSCLK0 |= CMU_SYSCLK0_IRC16M_EN;
			
		} while ( (SYSCLK0 & CMU_SYSCLK0_IRC16M_EN) != CMU_SYSCLK0_IRC16M_EN );
	}
	else
	{
		do
		{
			/* Disable HSI clock */
			SYSCLK0 &= ~CMU_SYSCLK0_IRC16M_EN;
			
		} while ( (SYSCLK0 & CMU_SYSCLK0_IRC16M_EN) == CMU_SYSCLK0_IRC16M_EN );
	}
}

/**
  * @param  CMU_LSE: specifies the new state of the LSE.
  *         This parameter can be one of the following values:
  *		@arg  CMU_LSE_OFF: turn OFF the LSE oscillator
  *   @arg  CMU_LSE_ON: turn ON the LSE oscillator
  * @retval None
  */
void CMU_LSEConfig(CMU_CLKStartUp_TypeDef CMU_CLKStartUpTime, CMU_LSEDriver_TypeDef CMU_LSEDriver, uint16_t CMU_LSE_STATE)
{
	if (CMU_LSE_STATE != CMU_LSE_OFF)
	{
		/* Store value of XLF_CTRL register */
		volatile uint32_t tmpreg = XLF_CTRL;
		
		/* Clear STARTUP and DRIVER bits to refresh */
		tmpreg &= ~(CMU_XLF_CTRL_XLF_STARTUP | CMU_XLF_CTRL_XLF_DRIVER);
		
		/* Fill value of STARTUP and DRIVER bits with specified parameters */
		tmpreg |= (CMU_CLKStartUpTime << 4 | CMU_LSEDriver);
		
		/* Refresh value of XLF_CTRL register */
		XLF_CTRL = tmpreg;

		do
		{
			/* Enable LSE clock */
			SYSCLK0 |= CMU_SYSCLK0_XLF_EN;
			
		} while ( (SYSCLK0 & CMU_SYSCLK0_XLF_EN) != CMU_SYSCLK0_XLF_EN );
	}
	else
	{
		do
		{
			/* Disable LSE clock */
			SYSCLK0 &= ~CMU_SYSCLK0_XLF_EN;
			
		} while ( (SYSCLK0 & CMU_SYSCLK0_XLF_EN) == CMU_SYSCLK0_XLF_EN );
	}
}

/**
  * @param  CMU_LSI: specifies the new state of the LSI.
  *         This parameter can be one of the following values:
  *   @arg  CMU_LSI_OFF: turn OFF the LSI oscillator
  *   @arg  CMU_LSI_ON: turn ON the LSI oscillator
  * @retval None
  */
void CMU_LSIConfig(CMU_CLKStartUp_TypeDef CMU_CLKStartUpTime, uint16_t CMU_LSI_STATE)
{
	if (CMU_LSI_STATE != CMU_LSI_OFF)
	{
		/* Store value of IRC38K_CTRL register */
		uint32_t tmpreg = IRC38K_CTRL;
		
		/* Clear STARTUP and TRIM bits to refresh */
		tmpreg &= ~(CMU_IRC38K_CTRL_IRC38K_STARTUP | CMU_IRC38K_CTRL_IRC38K_TRIM);
		
		#ifndef __TEST_CHIP
		/* Fill value of STARTUP and TRIM bits with specified parameters */
		tmpreg |= ( (CMU_CLKStartUpTime << 6) | ( (CAL4 >> 8) & CMU_IRC38K_CTRL_IRC38K_TRIM ) );
		#else
		/* Fill value of STARTUP and TRIM bits with specified parameters */		
		tmpreg |= ( (CMU_CLKStartUpTime << 6) | (0x9 & CMU_IRC38K_CTRL_IRC38K_TRIM) );
		#endif
		
		/* Refresh value of IRC38K_CTRL register */
		IRC38K_CTRL = tmpreg;
		
		do
		{
			/* Enable LSI clock */
			SYSCLK0 |= CMU_SYSCLK0_IRC38K_EN;
			
		} while ( (SYSCLK0 & CMU_SYSCLK0_IRC38K_EN) != CMU_SYSCLK0_IRC38K_EN );
	}
	else
	{
		do
		{
			/* Disable LSI Clock */
			SYSCLK0 &= ~CMU_SYSCLK0_IRC38K_EN;
			
		} while ( (SYSCLK0 & CMU_SYSCLK0_IRC38K_EN) == CMU_SYSCLK0_IRC38K_EN );
	}
}

/**
  * @param  CMU_IRC40K: specifies the new state of the LSI.
  *         This parameter can be one of the following values:
  *		@arg  CMU_IRC40K_OFF: turn OFF the IRC40K oscillator
  *   @arg  CMU_IRC40K_ON: turn ON the IRC40K oscillator
  * @retval None
  */
void CMU_IRC40KConfig(uint16_t CMU_IRC40K_STATE)
{
	if (CMU_IRC40K_STATE != CMU_IRC40K_OFF)
	{
		do
		{
			/* Enable IRC40K clock */
			SYSCLK1 |= CMU_SYSCLK1_IRC40K_EN;
			
		} while ( (SYSCLK1 & CMU_SYSCLK1_IRC40K_EN) != CMU_SYSCLK1_IRC40K_EN );
	}
	else
	{
		do
		{
			/* Disable IRC40K clock */
			SYSCLK1 &= ~CMU_SYSCLK1_IRC40K_EN;
			
		} while ( (SYSCLK1 & CMU_SYSCLK1_IRC40K_EN) == CMU_SYSCLK1_IRC40K_EN );			
	}
}
	
/**
  * @param  CMU_SysClkSource: specifies the clock source used as system clock.
  * 	@arg  CMU_SysClkSource_HSI             
  * 	@arg 	CMU_SysClkSource_HSE             
  * 	@arg 	CMU_SysClkSource_LSI             
  * 	@arg 	CMU_SysClkSource_LSE
  */
void CMU_SysClkConfig(CMU_SysClkSource_TypeDef CMU_SysClkSource)
{	
	do 
	{
		/* Store value of SYSCLK0 register */
		volatile uint32_t tmpreg = SYSCLK0;
		
		/* Clear SYSCLK_SEL bit to refresh */
		tmpreg &= ~CMU_SYSCLK0_SYSCLK_SEL;
			
		/* Fill SYSCLK_SEL bit with specified parameters */
		tmpreg |= CMU_SysClkSource;
			
		/* Refresh new value of SYSCLK0 register */
		SYSCLK0 = tmpreg;
		
	} while ( (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) != CMU_SysClkSource );
} 

/**
  * @retval The clock source used as system clock. The returned value can
  *         be one of the following:
  * 	@arg  CMU_SysClkSource_HSI             
  * 	@arg 	CMU_SysClkSource_HSE             
  * 	@arg 	CMU_SysClkSource_LSI             
  * 	@arg 	CMU_SysClkSource_LSE
  */
CMU_SysClkSource_TypeDef CMU_GetSysClkSource(void)
{
	return ( (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) >> 4 ) == 0x1 ? CMU_SysClkSource_HSE : \
				 ( (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) >> 4 ) == 0x2 ? CMU_SysClkSource_LSI : \
				 ( (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) >> 4 ) == 0x3 ? CMU_SysClkSource_LSE : CMU_SysClkSource_HSI;
}

/**
  * @brief  Configures the AHB clock (HCLK).
  * @param  CMU_SYSCLK_Div: defines the AHB clock divider. This clock is derived from 
  *         the system clock (SYSCLK).
  *         This parameter can be one of the following values:
  *   @arg  CMU_SYSCLK_Div1: AHB clock = SYSCLK
  *   @arg  CMU_SYSCLK_Div2: AHB clock = SYSCLK/2
  *   @arg  CMU_SYSCLK_Div4: AHB clock = SYSCLK/4
  *   @arg  CMU_SYSCLK_Div8: AHB clock = SYSCLK/8
  *   @arg  CMU_SYSCLK_Div16: AHB clock = SYSCLK/16
  *   @arg  CMU_SYSCLK_Div64: AHB clock = SYSCLK/64
  *   @arg  CMU_SYSCLK_Div128: AHB clock = SYSCLK/128
  * @retval None.
  */
void CMU_HCLKConfig(uint32_t CMU_SYSCLK_Div)
{
	do
	{
		/* Store value of SYSCLK0 register */
		volatile uint32_t tmpreg = SYSCLK0;
		
		/* Clear AHB_CLK_DIV bit to refresh */
		tmpreg &= ~CMU_SYSCLK0_AHB_CLK_DIV;
		
		/* Fill AHB_CLK_DIV bit with specified parameters */
		tmpreg |= CMU_SYSCLK_Div;
		
		/* Refresh new value of SYSCLK0 register */
		SYSCLK0 = tmpreg;
		
	} while ( (SYSCLK0 & CMU_SYSCLK0_AHB_CLK_DIV) != CMU_SYSCLK_Div );
}

/**
  * @brief  Configures the Low Speed APB clock (PCLK).
  * @param  CMU_HCLK: defines the APB1 clock divider. This clock is derived from 
  *         the AHB clock (HCLK).
  *         This parameter can be one of the following values:
  *   @arg  CMU_HCLK_Div1: APB clock = HCLK
  *   @arg  CMU_HCLK_Div2: APB clock = HCLK/2
  *   @arg  CMU_HCLK_Div4: APB clock = HCLK/4
  *   @arg  CMU_HCLK_Div8: APB clock = HCLK/8
  * @retval None.
  */
void CMU_PCLKConfig(uint32_t CMU_HCLK_Div)
{
	do
	{
		/* Store value of SYSCLK0 register */
		volatile uint32_t tmpreg = SYSCLK0;
		
		/* Clear APB_CLK_DIV bit to refresh */
		tmpreg &= ~CMU_SYSCLK0_APB_CLK_DIV;
		
		/* Fill APB_CLK_DIV bit with specified parameters */
		tmpreg |= CMU_HCLK_Div;
		
		/* Refresh new value of SYSCLK0 register */
		SYSCLK0 = tmpreg;
		
	} while ( (SYSCLK0 & CMU_SYSCLK0_APB_CLK_DIV) != CMU_HCLK_Div );
}

/**
	* @brief  Get frequence of system clock.
	*/
uint32_t CMU_GetSysClkFreq(void)
{
	return (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) == CMU_SYSCLK0_SYSCLK_SEL_XHFOSC ? HSE_VALUE : \
				 (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) == CMU_SYSCLK0_SYSCLK_SEL_IRC38K ? LSI_VALUE : \
				 (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) == CMU_SYSCLK0_SYSCLK_SEL_XLFOSC ? LSE_VALUE : HSI_VALUE;
}

/**
	* @brief  Get frequence of advance high bus clock.
	*/
uint32_t CMU_GetHCLKFreq(void)
{
	uint32_t SYSCLK = ( (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) == CMU_SYSCLK0_SYSCLK_SEL_XHFOSC ? HSE_VALUE : \
												       (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) == CMU_SYSCLK0_SYSCLK_SEL_IRC38K ? LSI_VALUE : \
											         (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) == CMU_SYSCLK0_SYSCLK_SEL_XLFOSC ? LSE_VALUE : HSI_VALUE );
		
	return SYSCLK >> ( (SYSCLK0 & CMU_SYSCLK0_AHB_CLK_DIV) >> 6 );
}
	
/**
	* @brief  Get frequence of peripheral clock.
	*/
uint32_t CMU_GetPCLKFreq(void)
{
	uint32_t SYSCLK = ( (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) == CMU_SYSCLK0_SYSCLK_SEL_XHFOSC ? HSE_VALUE : \
															 (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) == CMU_SYSCLK0_SYSCLK_SEL_IRC38K ? LSI_VALUE : \
											         (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) == CMU_SYSCLK0_SYSCLK_SEL_XLFOSC ? LSE_VALUE : HSI_VALUE );
		
    uint32_t HCLK = SYSCLK >> ( (SYSCLK0 & CMU_SYSCLK0_AHB_CLK_DIV) >> 6 );
		
	return HCLK >> ( (SYSCLK0 & CMU_SYSCLK0_APB_CLK_DIV) >> 9 );
}

/** 
  * @brief Select which low speed clock as asynchronous clock source in LPUART module.
  * @param CMU_LPUART_CLK: as follow
  * 	@arg CMU_LPUARTCLK_IRC38K 
  * 	@arg CMU_LPUARTCLK_LSE
	*/
void CMU_LPUARTCLKConfig(uint8_t CMU_LPUART_CLK)
{
	volatile uint32_t tmpreg = SYSCLK1;
	
	tmpreg &= ~CMU_SYSCLK1_LPUART_CS;
	tmpreg |= (uint8_t)( (CMU_LPUART_CLK == CMU_LPUARTCLK_LSE) ? CMU_LPUARTCLK_LSE : CMU_LPUARTCLK_IRC38K );
	
	SYSCLK1 = tmpreg;
}

/**
  * @brief  Select which low speed clock as asynchronous clock source in LCD module.
  * @param  CMU_LCD_CLK: as follow
  * 	@arg  CMU_LCDCLK_IRC38K 
  * 	@arg  CMU_LCDCLK_LSE
  */
void CMU_LCDCLKConfig(uint8_t CMU_LCD_CLK)
{
	volatile uint32_t tmpreg = SYSCLK1;
	
	tmpreg &= ~CMU_SYSCLK1_LCD_CS;	
	tmpreg |= (uint8_t)( (CMU_LCD_CLK == CMU_LCDCLK_LSE) ? CMU_LCDCLK_LSE : CMU_LCDCLK_IRC38K );
	
	SYSCLK1 = tmpreg;
}

/** 	
	* @brief  Select which low speed clock as asynchronous clock source in WDT module.
  * @param  CMU_WDT_CLK: as follow
  *		@arg  CMU_WDTCLK_IRC38K 
  *		@arg  CMU_WDTCLK_LSE
  *		@arg  CMU_WDTCLK_IRC40K
*/
void CMU_WDTCLKConfig(uint8_t CMU_WDT_CLK)
{
	volatile uint32_t tmpreg = SYSCLK1;
	
	tmpreg &= ~CMU_SYSCLK1_WDT_CS;
	tmpreg |= (uint8_t)( (CMU_WDT_CLK == CMU_WDTCLK_LSE) ? CMU_WDTCLK_LSE : \
										 ( (CMU_WDT_CLK == CMU_WDTCLK_IRC38K) ? CMU_WDTCLK_IRC38K : CMU_WDTCLK_IRC40K) );
	
	SYSCLK1 = tmpreg;
}

/** 
	* @brief  Select which low speed clock as asynchronous clock source in BASETIMER module.
  * @param  CMU_BASETM_CLK: as follow
  *		@arg  CMU_BASETMCLK_IRC38K
  *		@arg  CMU_BASETMCLK_LSE
*/
void CMU_BASETMCLKConfig(uint8_t CMU_BASETM_CLK)
{
	volatile uint32_t tmpreg = SYSCLK1;
	
	tmpreg &= ~CMU_SYSCLK1_BASETM_CS;	
	tmpreg |= (uint8_t)( (CMU_BASETM_CLK == CMU_BASETMCLK_LSE) ? CMU_BASETMCLK_LSE : CMU_BASETMCLK_IRC38K );
	
	SYSCLK1 = tmpreg;
}

/** 
	* @brief  Select which low speed clock as asynchronous clock source in RTC module.
  * @param  CMU_RTC_CLK: as follow
  *		@arg  CMU_RTCCLK_IRC38K 
  *		@arg  CMU_RTCCLK_LSE
*/
void CMU_RTCCLKConfig(uint8_t CMU_RTC_CLK)
{
	volatile uint32_t tmpreg = SYSCLK1;
	
	tmpreg &= ~CMU_SYSCLK1_RTC_CS;
	tmpreg |= (uint8_t)( (CMU_RTC_CLK == CMU_RTCCLK_LSE) ? CMU_RTCCLK_LSE : CMU_RTCCLK_IRC38K );
	
	SYSCLK1 = tmpreg;
}

/** 
	* @brief Enable function that Core access error instructions,
  *        make system reset and lock core.
  */
void CMU_LockUpCmd(FunctionalState NewState)
{
	volatile uint32_t tmpreg = SYSCLK1;
	
	if (NewState != DISABLE)
  {
    tmpreg |= CMU_SYSCLK1_LOOKUP_EN;
  }
  else
  {
    tmpreg &= ~CMU_SYSCLK1_LOOKUP_EN;
  }
	
	SYSCLK1 = tmpreg;	
}

/** 
	* @brief Enable parity check circuit in RAM.
  */
void CMU_RAM_PARCmd(FunctionalState NewState)
{
	volatile uint32_t tmpreg = SYSCLK1;
	
	if (NewState != DISABLE)
  {
    tmpreg |= CMU_SYSCLK1_RAM_PAR_EN;
  }
  else
  {
    tmpreg &= ~CMU_SYSCLK1_RAM_PAR_EN;
  }
	
	SYSCLK1 = tmpreg;		
}

/**
  * @brief  Enables or disables the Low Speed APB (APB) peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.
  * @param  CMU_APBPeriph0: specifies the APB peripheral to gates its clock.
  *         This parameter can be any combination of the following values:
  *   @arg  CMU_APBPeriph0_RNG
  *   @arg  CMU_APBPeriph0_DES
  *   @arg  CMU_APBPeriph0_ADC
  *   @arg  CMU_APBPeriph0_BUZZER  
  *   @arg  CMU_APBPeriph0_CRC
  *   @arg  CMU_APBPeriph0_DMA
  *   @arg  CMU_APBPeriph0_FLASH
  *   @arg  CMU_APBPeriph0_PCA4
  *   @arg  CMU_APBPeriph0_PCA3 
  *   @arg  CMU_APBPeriph0_PCA2
  *   @arg  CMU_APBPeriph0_PCA1         
  *   @arg  CMU_APBPeriph0_TIMER4
  *   @arg  CMU_APBPeriph0_TIMER3
  *   @arg  CMU_APBPeriph0_TIMER2 
  *   @arg  CMU_APBPeriph0_TIMER1
  *   @arg  CMU_APBPeriph0_SCI7816      
  *   @arg  CMU_APBPeriph0_I2C2
  *   @arg  CMU_APBPeriph0_I2C1 
  *   @arg  CMU_APBPeriph0_SPI4
  *   @arg  CMU_APBPeriph0_SPI3
  *   @arg  CMU_APBPeriph0_SPI2
  *   @arg  CMU_APBPeriph0_SPI1
  *   @arg  CMU_APBPeriph0_UART6
  *   @arg  CMU_APBPeriph0_UART5
  *   @arg  CMU_APBPeriph0_UART4
  *   @arg  CMU_APBPeriph0_UART3
  *   @arg  CMU_APBPeriph0_UART2
  *   @arg  CMU_APBPeriph0_UART1	
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CMU_APBPeriph0ClockCmd(uint32_t CMU_APBPeriph0, FunctionalState NewState)
{
	if (NewState != DISABLE)
  {
    PERI_CLK_CTRL0 |= CMU_APBPeriph0;
  }
  else
  {
    PERI_CLK_CTRL0 &= ~CMU_APBPeriph0;
  }
}

/**
  * @brief  Enables or disables the APB1 peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is disabled and the application software has to enable this clock before 
  *         using it.    
  * @param  CMU_APBPeriph1: specifies the APB1 peripheral to gates its clock.
  *         This parameter can be any combination of the following values:
  *   @arg  CMU_APBPeriph1_LCD
  *   @arg  CMU_APBPeriph1_WDT
  *   @arg  CMU_APBPeriph1_BASETM
  *   @arg  CMU_APBPeriph1_RTC
  *   @arg  CMU_APBPeriph1_PORT  
  *   @arg  CMU_APBPeriph1_BKRAM 
  * @param  NewState: new state of the specified peripheral clock.
  *         This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void CMU_APBPeriph1ClockCmd(uint8_t CMU_APBPeriph1, FunctionalState NewState)
{  
  if (NewState != DISABLE)
  {
    PERI_CLK_CTRL1 |= CMU_APBPeriph1;
  }
  else
  {
    PERI_CLK_CTRL1 &= ~CMU_APBPeriph1;
  }
}

/**
  * @brief  Checks whether the specified CMU_ClOCK is set or not.
  * @param  CMU_SysClkSource: specifies the flag to check.
  *         This parameter can be one of the following values:
  * 	@arg  CMU_SysClkSource_HSI             
  * 	@arg 	CMU_SysClkSource_HSE             
  * 	@arg 	CMU_SysClkSource_LSI             
  * 	@arg 	CMU_SysClkSource_LSE
  * @retval The new state of SET or RESET.
  */
FlagStatus CMU_WaitForSysClkStartUp(CMU_SysClkSource_TypeDef CMU_SysClkSource)
{
	volatile uint16_t Status = 0;
	
	switch (CMU_SysClkSource)
	{
		case CMU_SysClkSource_HSE:
			XHF_CTRL &= ~CMU_FLAG_HSERDY;
			Status = (XHF_CTRL & CMU_FLAG_HSERDY);
			break;
		case CMU_SysClkSource_LSI:
			IRC38K_CTRL &= ~CMU_FLAG_LSIRDY;
			Status = (IRC38K_CTRL & CMU_FLAG_LSIRDY);
			break;
		case CMU_SysClkSource_LSE:
			XLF_CTRL &= ~CMU_FLAG_LSERDY;
			Status = (XLF_CTRL & CMU_FLAG_LSERDY);
			break;
		default:
			IRC16M_CTRL &= ~CMU_FLAG_HSIRDY;
			Status = (IRC16M_CTRL & CMU_FLAG_HSIRDY);
		  break;			
	}

  return Status != 0 ? SET : RESET;	
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
