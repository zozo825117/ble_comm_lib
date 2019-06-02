/**
  ******************************************************************************
 * @file     system_GW32L.c
 * @author   GW_IOM
 * @version  V1.0.4
 * @date     10-18-2018
 * @brief    CMSIS Device System Source File for
 *           GW32L Device Series
  ******************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */
   /*All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/

#include "GW32L.h"

/* Configurate system clock as specified device */
#if defined (GW32L0xx_xx)
//	#define SYSCLK_FREQ_HSE     HSE_VALUE
//	#define SYSCLK_FREQ_38KHz   LSI_VALUE
//	#define SYSCLK_FREQ_32KHz   LSE_VALUE
#else
//	#define SYSCLK_FREQ_HSE     HSE_VALUE
#endif

/*!< Uncomment the following line if you need to relocate your vector Table in
     Internal SRAM. */ 
//	#define VECT_TAB_SRAM
#define VECT_TAB_OFFSET  0x0 /*!< Vector Table base offset field. 
                                  This value must be a multiple of 0x200. */

/*******************************************************************************
*  Clock Definitions
*******************************************************************************/
#ifdef SYSCLK_FREQ_HSE
  uint32_t SystemCoreClock         = SYSCLK_FREQ_HSE;         /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_38KHz
  uint32_t SystemCoreClock         = SYSCLK_FREQ_38KHz;       /*!< System Clock Frequency (Core Clock) */
#elif defined SYSCLK_FREQ_32KHz
  uint32_t SystemCoreClock         = SYSCLK_FREQ_32KHz;       /*!< System Clock Frequency (Core Clock) */
#else /*!< HSI Selected as System Clock source */
  uint32_t SystemCoreClock         = HSI_VALUE;               /*!< System Clock Frequency (Core Clock) */
#endif

/** @brief GW32L0xx_xx System_Private_FunctionPrototypes
  */
static void SetSysClock(void);

#ifdef SYSCLK_FREQ_HSE
	static void SetSysClockToHSE(void);
#elif defined SYSCLK_FREQ_38KHz
  static void SetSysClockTo38K(void);
#elif defined SYSCLK_FREQ_32KHz
  static void SetSysClockTo32K(void);
#endif

/**
  * Update SystemCoreClock variable
  *
  * @param  none
  * @return none
  *
  * @brief  Updates the SystemCoreClock with current core Clock
  *         retrieved from cpu registers.
  */
void SystemCoreClockUpdate(void)
{
	uint32_t vBuff = ((SYSCLK0 & CMU_SYSCLK0_AHB_CLK_DIV) >> 6);
	SystemCoreClock = ( (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) == CMU_SYSCLK0_SYSCLK_SEL_XHFOSC ? HSE_VALUE : \
											(SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) == CMU_SYSCLK0_SYSCLK_SEL_IRC38K ? LSI_VALUE : \
											(SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) == CMU_SYSCLK0_SYSCLK_SEL_XLFOSC ? LSE_VALUE : HSI_VALUE ) >> ( vBuff );
}

/**
  * Initialize the system
  *
  * @param  none
  * @return none
  *
  * @brief  Setup the microcontroller system.
  *         Initialize the System.
  */
void SystemInit(void)
{
	uint32_t tmp = 0x5A5AEECC;

	/* Chip initialize */		
	if (tmp == 0x5A5AEECC)
	{
		/* Disable interrupt request */
		__disable_irq();

		do 
		{
			/* Deinitialize peripheral clock */
			PERI_CLK_CTRL0 = 0x0;
			PERI_CLK_CTRL1 = 0x0;

		} while ( PERI_CLK_CTRL0 != 0x0 && PERI_CLK_CTRL1 != 0x0 );

		if (tmp == 0x5A5AEECC)
		{
			/* Disable interrupt request */
			__disable_irq();

			do 
			{					
				/* restore system clock */
				SYSCLK0 = 0x1;			
				SYSCLK1 = 0x3;

			} while ( SYSCLK0 != 0x1 && SYSCLK1 != 0x3 );
		}
		else
		{
			/* Disable interrupt request */
			__disable_irq();

			/* Restore peripheral clock register reset value */
			PERI_CLK_CTRL0 = 0xFFFFFFFF;
			PERI_CLK_CTRL1 = 0xFF;			
		}
	}

	/* Enable interrupt request */		
	__enable_irq();

  /* Configure the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers */
  /* Configure the Flash Latency cycles and enable prefetch buffer */
  SetSysClock();

#ifdef VECT_TAB_SRAM
  SCB->VTOR = SRAM_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal SRAM. */
#else
  SCB->VTOR = FLASH_BASE | VECT_TAB_OFFSET; /* Vector Table Relocation in Internal FLASH. */
#endif	
}

/**
  * @brief  Configures the System clock frequency, HCLK, PCLK2 and PCLK1 prescalers.
  * @param  None
  * @retval None
  */
static void SetSysClock(void)
{
#ifdef SYSCLK_FREQ_HSE
  SetSysClockToHSE();
#elif defined SYSCLK_FREQ_38KHz
  SetSysClockTo38K();
#elif defined SYSCLK_FREQ_32KHz
  SetSysClockTo32K();
#endif

 /* If none of the define above is enabled, the HSI is used as System clock
    source (default after reset) */ 
}

#ifdef SYSCLK_FREQ_HSE
static void SetSysClockToHSE(void)
{
	__IO uint32_t tmpreg = 0;

	/* Enable PORT peripheral clock */
	PERI_CLK_CTRL1 |= CMU_PERI_CLK1_PORT_EN;

	/* Configurate P6.7/P6.8 to analog port pin  */
	PORT_6->Pn_SEL0 |= (PORT_Px_PB7 | PORT_Px_PB8);

	/* Set Startup time and diver of HSE */
	XHF_CTRL = (CMU_XHF_CTRL_XHF_STARTUP | CMU_XHF_CTRL_XHF_DRIVER);

	do
	{
		/* Enable HSE clock */
		SYSCLK0 |= CMU_SYSCLK0_XHF_EN;

	} while ( (SYSCLK0 & CMU_SYSCLK0_XHF_EN) != CMU_SYSCLK0_XHF_EN );

		/* Clear HSE stable bit */
	XHF_CTRL &= ~CMU_XHF_CTRL_XHF_STABLE;

	/* Wait for stably of HSE */
	while ( (XHF_CTRL & CMU_XHF_CTRL_XHF_STABLE) != CMU_XHF_CTRL_XHF_STABLE );

	if (HSE_VALUE > 16000000)
	{
		do
		{
			/* Flash read wait cycle */
			FLASH->FLASH_CTRL |= FLASH_CTRL_READ_WAIT_CYCLE;

		} while ( (FLASH->FLASH_CTRL & FLASH_CTRL_READ_WAIT_CYCLE) != FLASH_CTRL_READ_WAIT_CYCLE );
	}
	else
	{
		do
		{
			/* Flash read wait cycle */
			FLASH->FLASH_CTRL &= ~FLASH_CTRL_READ_WAIT_CYCLE;

		} while ( (FLASH->FLASH_CTRL & FLASH_CTRL_READ_WAIT_CYCLE) == FLASH_CTRL_READ_WAIT_CYCLE );		
	}	

	do
	{
		/* Store value of SYSCLK0 register */
		tmpreg = SYSCLK0;

		/* Clear SYSCLK_SEL bit to refresh */
		tmpreg &= ~CMU_SYSCLK0_SYSCLK_SEL;

		/* HSI switch to HSE */
		tmpreg |= CMU_SYSCLK0_SYSCLK_SEL_XHFOSC;

		/* Refresh new value of SYSCLK0 register */
		SYSCLK0 = tmpreg;

	}	while ( (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) != CMU_SYSCLK0_SYSCLK_SEL_XHFOSC );

	do
	{
		/* Disable HSI */
		SYSCLK0 &= ~CMU_SYSCLK0_IRC16M_EN;

	} while (	(SYSCLK0 & CMU_SYSCLK0_IRC16M_EN) == CMU_SYSCLK0_IRC16M_EN );

	do
	{
		/* HCLK = SYSCLK */
		tmpreg = SYSCLK0;
		tmpreg &= ~CMU_SYSCLK0_AHB_CLK_DIV;
		tmpreg |= CMU_SYSCLK0_AHB_CLK_DIV_DIV1;
		SYSCLK0 = tmpreg;

	} while ( (SYSCLK0 & CMU_SYSCLK0_AHB_CLK_DIV) != CMU_SYSCLK0_AHB_CLK_DIV_DIV1 );

	do
	{
		/* PCLK = HCLK */
		tmpreg = SYSCLK0;
		tmpreg &= ~CMU_SYSCLK0_APB_CLK_DIV;
		tmpreg |= CMU_SYSCLK0_APB_CLK_DIV_DIV1;
		SYSCLK0 = tmpreg;

	}	while ( (SYSCLK0 & CMU_SYSCLK0_APB_CLK_DIV) != CMU_SYSCLK0_APB_CLK_DIV_DIV1 );
}

#elif defined SYSCLK_FREQ_38KHz
static void SetSysClockTo38K(void)
{
	__IO uint32_t tmpreg = 0;

	/* Set Startup time and diver of LSI */
	IRC38K_CTRL = ( CMU_IRC38K_CTRL_IRC38K_STARTUP | ( (CAL4 >> 8) & CMU_IRC38K_CTRL_IRC38K_TRIM ) );

	do
	{
		/* Enable LSI clock */
		SYSCLK0 |= CMU_SYSCLK0_IRC38K_EN;

	} while ( (SYSCLK0 & CMU_SYSCLK0_IRC38K_EN) != CMU_SYSCLK0_IRC38K_EN );

		/* Clear LSI stable bit */
	IRC38K_CTRL &= ~CMU_IRC38K_CTRL_IRC38K_STABLE;

	/* Wait for stably of LSI */
	while ( (IRC38K_CTRL & CMU_IRC38K_CTRL_IRC38K_STABLE) != CMU_IRC38K_CTRL_IRC38K_STABLE );

	do
	{
		/* Store value of SYSCLK0 register */
		tmpreg = SYSCLK0;

		/* Clear SYSCLK_SEL bit to refresh */
		tmpreg &= ~CMU_SYSCLK0_SYSCLK_SEL;

		/* HSI switch to LSI */
		tmpreg |= CMU_SYSCLK0_SYSCLK_SEL_IRC38K;

		/* Refresh new value of SYSCLK0 register */
		SYSCLK0 = tmpreg;

	}	while ( (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) != CMU_SYSCLK0_SYSCLK_SEL_IRC38K );

	do
	{
		/* Disable HSI */
		SYSCLK0 &= ~CMU_SYSCLK0_IRC16M_EN;

	} while (	(SYSCLK0 & CMU_SYSCLK0_IRC16M_EN) == CMU_SYSCLK0_IRC16M_EN );

	do
	{
		/* HCLK = SYSCLK */
		tmpreg = SYSCLK0;
		tmpreg &= ~CMU_SYSCLK0_AHB_CLK_DIV;
		tmpreg |= CMU_SYSCLK0_AHB_CLK_DIV_DIV1;
		SYSCLK0 = tmpreg;

	} while ( (SYSCLK0 & CMU_SYSCLK0_AHB_CLK_DIV) != CMU_SYSCLK0_AHB_CLK_DIV_DIV1 );

	do
	{
		/* PCLK = HCLK */
		tmpreg = SYSCLK0;
		tmpreg &= ~CMU_SYSCLK0_APB_CLK_DIV;
		tmpreg |= CMU_SYSCLK0_APB_CLK_DIV_DIV1;
		SYSCLK0 = tmpreg;

	}	while ( (SYSCLK0 & CMU_SYSCLK0_APB_CLK_DIV) != CMU_SYSCLK0_APB_CLK_DIV_DIV1 );	
}

#elif defined SYSCLK_FREQ_32KHz
static void SetSysClockTo32K(void)
{
	__IO uint32_t tmpreg = 0;

	/* Enable PORT peripheral clock */
	PERI_CLK_CTRL1 |= CMU_PERI_CLK1_PORT_EN;

	/* Configurate P0.14/P0.15 to analog port pin  */
	PORT_0->Pn_SEL0 |= (PORT_Px_PB14 | PORT_Px_PB15);

	/* Set Startup time and diver of LSE */
	XLF_CTRL = (CMU_XLF_CTRL_XLF_STARTUP | CMU_XLF_CTRL_XLF_DRIVER);

	do
	{
		/* Enable LSE clock */
		SYSCLK0 |= CMU_SYSCLK0_XLF_EN;

	} while ( (SYSCLK0 & CMU_SYSCLK0_XLF_EN) != CMU_SYSCLK0_XLF_EN );	

	/* Clear LSE stable bit */
	XLF_CTRL &= ~CMU_XLF_CTRL_XLF_STABLE;

	/* Wait for stably of LSE */
	while ( (XLF_CTRL & CMU_XLF_CTRL_XLF_STABLE) != CMU_XLF_CTRL_XLF_STABLE );	

	do
	{
		/* Store value of SYSCLK0 register */
		tmpreg = SYSCLK0;

		/* Clear SYSCLK_SEL bit to refresh */
		tmpreg &= ~CMU_SYSCLK0_SYSCLK_SEL;

		/* HSI switch to LSE */
		tmpreg |= CMU_SYSCLK0_SYSCLK_SEL_XLFOSC;

		/* Refresh new value of SYSCLK0 register */
		SYSCLK0 = tmpreg;

	}	while ( (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) != CMU_SYSCLK0_SYSCLK_SEL_XLFOSC );

	do
	{
		/* Disable HSI */
		SYSCLK0 &= ~CMU_SYSCLK0_IRC16M_EN;

	} while (	(SYSCLK0 & CMU_SYSCLK0_IRC16M_EN) == CMU_SYSCLK0_IRC16M_EN );

	do
	{
		/* HCLK = SYSCLK */
		tmpreg = SYSCLK0;
		tmpreg &= ~CMU_SYSCLK0_AHB_CLK_DIV;
		tmpreg |= CMU_SYSCLK0_AHB_CLK_DIV_DIV1;
		SYSCLK0 = tmpreg;

	} while ( (SYSCLK0 & CMU_SYSCLK0_AHB_CLK_DIV) != CMU_SYSCLK0_AHB_CLK_DIV_DIV1 );

	do
	{
		/* PCLK = HCLK */
		tmpreg = SYSCLK0;
		tmpreg &= ~CMU_SYSCLK0_APB_CLK_DIV;
		tmpreg |= CMU_SYSCLK0_APB_CLK_DIV_DIV1;
		SYSCLK0 = tmpreg;

	}	while ( (SYSCLK0 & CMU_SYSCLK0_APB_CLK_DIV) != CMU_SYSCLK0_APB_CLK_DIV_DIV1 );
}

#endif
/******************* (C) COPYRIGHT 2018 GWRTI *****END OF FILE****/
