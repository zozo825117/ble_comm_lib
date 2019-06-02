/**
  ******************************************************************************
  * @file    GW32L0xx_timer.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides all the Timer firmware functions.
  *
 @verbatim
**/

#include "GW32L0xx_timer.h"

/**
	* @brief  Deinitializes the TIMERx peripheral registers to their default reset values.
	* @param  TIMx: where x can be 1 to 4 and BASETIMER to select the TIMERx peripheral.
	* 	@arg  TIMER_1, TIMER_2, TIMER_3, TIMER_4, BASETIMER
	* @retval None
	*/
void TIMER_DeInit(TIMER_TypeDef* TIMERx)
{
	uint32_t TIMER_PERI_RESET;
	
	/* Select which TIMER periperal to be deinitialized */
	TIMER_PERI_RESET = ( TIMERx == TIMER_1 ? RMU_PERI_RESET0_TIMER1 : \
											 TIMERx == TIMER_2 ? RMU_PERI_RESET0_TIMER2 : \
											 TIMERx == TIMER_3 ? RMU_PERI_RESET0_TIMER3 : \
											 TIMERx == TIMER_4 ? RMU_PERI_RESET0_TIMER4 : RMU_PERI_RESET1_BASETIMER );
	
	if (TIMER_PERI_RESET != RMU_PERI_RESET1_BASETIMER)
	{
		do
		{
			/* Restore TIMER peripheral register to the reset value */
			PERI_RST_CTRL0 |= TIMER_PERI_RESET;
			
		} while ( (PERI_RST_CTRL0 & TIMER_PERI_RESET) != TIMER_PERI_RESET );
		
		/* Switch to work in normal mode */
		PERI_RST_CTRL0 &= ~TIMER_PERI_RESET;
	}
	else
	{
		do
		{
			/* Restore BASETIMER peripheral register to the reset value */
			PERI_RST_CTRL1 |= TIMER_PERI_RESET;
			
		} while ( (PERI_RST_CTRL1 & TIMER_PERI_RESET) != TIMER_PERI_RESET );
		
		/* Switch to work in normal mode */
		PERI_RST_CTRL1 &= ~TIMER_PERI_RESET;		
	}
}

/**
	* @brief  Fills each TIMER_InitStruct member with its default value.
	* @param  TIMER_InitStruct: pointer to a TIMER_InitStruct structure which will
	*         be initialized.
	* @retval None
	*/
void TIMER_StructInit(TIMER_InitTypeDef* TIMER_InitStruct)
{
	TIMER_InitStruct->TIMER_Mode = TIMER_Mode_FreeCounter;
	TIMER_InitStruct->TIMER_CntClkSel = TIMER_CntClkSel_APBusClk;
	TIMER_InitStruct->TIMER_PWMOutput = TIMER_PWMOutput_Disable;
	TIMER_InitStruct->TIMER_GateCtrl = TIMER_GateCtrl_Disable;
}

/**
	* @brief  Initializes the TIMER according to the specified
	*         parameters in the TIMER_InitStruct.
	* @param  TIMERx: where x can be 1 to 4, and BASETIMER
	* 	@arg  TIMER_1, TIMER_2, TIMER_3, TIMER_4, BASETIMER
	* @param  TIMER_InitStruct: pointer to a TIMER_InitTypeDef structure
	*         that contains the configuration information for the specified TIMER peripheral.
	* @retval None
	*/
void TIMER_Init(TIMER_TypeDef* TIMERx, TIMER_InitTypeDef* TIMER_InitStruct)
{	
	uint32_t tmpreg = 0;
	
	tmpreg = TIMERx->CTRL;	
	TIMERx->CTRL &= ~(TIMER_TMxCTRL_EN);	
	tmpreg &= ~(TIMER_TMxCTRL_PWM);
	tmpreg |= (TIMER_InitStruct->TIMER_PWMOutput << 3);
	tmpreg &= ~(TIMER_TMxCTRL_MODE);
	tmpreg |= (TIMER_InitStruct->TIMER_Mode << 1);
	TIMERx->CTRL = tmpreg;
	
	if (TIMERx != BASETIMER)
	{
		volatile uint8_t Bitpos = ( (TIMERx == TIMER_1) ? 0 : \
																(TIMERx == TIMER_2) ? 1 : \
																(TIMERx == TIMER_3) ? 2 : 3 );
		tmpreg = TIMERS_GATE;
		tmpreg &= ~( (TIMER_TMxsGATE_TM1CT | TIMER_TMxsGATE_TM1Gate) << Bitpos * 2 );
		tmpreg |= ( ((TIMER_InitStruct->TIMER_CntClkSel << 1) | TIMER_InitStruct->TIMER_GateCtrl) << Bitpos * 2 );
		TIMERS_GATE = tmpreg;
	}
	else
	{
		tmpreg = BTIMERS_GATE;
		tmpreg &= ~(BTIMER_BTMGATE_TMCT | BTIMER_BTMGATE_TMGate);
		tmpreg |= ( TIMER_InitStruct->TIMER_CntClkSel << 1 | TIMER_InitStruct->TIMER_GateCtrl );
		BTIMERS_GATE = tmpreg;

		tmpreg = TIMERx->CTRL;	
		TIMERx->CTRL &= ~(TIMER_TMxCTRL_EN);
		tmpreg |= BTIMER_BTMCTRL_INTMASK;
		TIMERx->CTRL = tmpreg;
	}
}

/**
	* @brief  Enable or disable TIMER module.
	* @param  TIMERx: where x can be 1 to 4, and BASETIMER
	* 	@arg  TIMER_1, TIMER_2, TIMER_3, TIMER_4, BASETIMER
	*/
void TIMER_Cmd(TIMER_TypeDef* TIMERx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		do
		{
			TIMERx->CTRL |= TIMER_TMxCTRL_EN;
			
		} while ( (TIMERx->CTRL & TIMER_TMxCTRL_EN) != TIMER_TMxCTRL_EN );
	}
	else
	{
		TIMERx->CTRL &= ~TIMER_TMxCTRL_EN;	
	}
}

/**
	* @brief	Configurate TIMER interrupt flag to be enabled or disabled. 
	* @param  TIMERx: where x can be 1 to 4
	* 	@arg  TIMER_1, TIMER_2, TIMER_3, TIMER_4
	*/
void TIMER_ITConfig(TIMER_TypeDef* TIMERx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		TIMERx->CTRL &= ~TIMER_TMxCTRL_INTMASK;
	}
	else
	{
		TIMERx->CTRL |= TIMER_TMxCTRL_INTMASK;	
	}
}

/**
	* @brief  Get status of all TIMER raw intterrupt flag.
	* @retval As follow, and the values can been combined
	*		@arg  0x1: TIMER1 interrupt
	*		@arg  0x2: TIMER2 interrupt
	*		@arg  0x4: TIMER3 interrupt
	*		@arg  0x8: TIMER4 interrupt
	*/
uint8_t TIMER_GetAllRawITStatus(void)
{
	return TIMERS_RawINTSTS & 0xF;
}

/**
	* @brief  Get status of TIMER intterrupt flag.
	* @param  TIMERx: where x can be 1 to 4
	* 	@arg  TIMER_1, TIMER_2, TIMER_3, TIMER_4
	* @retval SET or RESET
	*/
ITStatus TIMER_GetITStatus(TIMER_TypeDef* TIMERx)
{
	return (TIMERx->INTSTS == TIMER_TMxINTSTS) ? SET : RESET;
}

/**
	* @brief  Get status of all TIMER intterrupt flag.
	* @retval As follow, and the values can been combined
	*		@arg  0x1: TIMER1 interrupt
	*		@arg  0x2: TIMER2 interrupt
	*		@arg  0x4: TIMER3 interrupt
	*		@arg  0x8: TIMER4 interrupt
	*/
uint8_t TIMER_GetAllITStatus(void)
{
	return TIMERS_INTSTS & 0xF;
}

/**
	* @brief  Clear TIMER intterrupt flag.
	* @param  TIMERx: where x can be 1 to 4
	* 	@arg  TIMER_1, TIMER_2, TIMER_3, TIMER_4
	*/
void TIMER_ClearITFlag(TIMER_TypeDef* TIMERx)
{
	TIMERx->INTCLR = TIMERx->INTCLR;
}

/**
	* @brief  Clear all TIMER intterrupt flag.
	*/
void TIMER_ClearAllITFlag(void)
{
	TIMERS_INTCLR	= TIMERS_INTCLR;
}

/**
	* @brief  Set value of TIMER load conuter0.
	* @param  TIMERx: where x can be  1 to 4, and BASETIMER
	* 	@arg  TIMER_1, TIMER_2, TIMER_3, TIMER_4, BASETIMER
	*/
void TIMER_SetLoadCounter0(TIMER_TypeDef* TIMERx, uint32_t Counter)
{
	TIMERx->LOADCOUNT0 = Counter;
}

/**
	* @brief  Set value of TIMER load conuter1.
	* @param  TIMERx: where x can be  1 to 4, and BASETIMER
	* 	@arg  TIMER_1, TIMER_2, TIMER_3, TIMER_4, BASETIMER
	*/
void TIMER_SetLoadCounter1(TIMER_TypeDef* TIMERx, uint32_t Counter)
{
	if (TIMERx != BASETIMER)
	{
		volatile uint8_t Regoffset = (TIMERx == TIMER_1) ? 0 : \
															   (TIMERx == TIMER_2) ? 1 : \
															   (TIMERx == TIMER_3) ? 2 : 3;
		
		*(volatile uint32_t *)( (TIMER_1_BASEADDR + 0xB0) + 4 * Regoffset ) = Counter;
	}
	else
	{
		BASETIMER_LOADCOUNT1 = Counter;		
	}
}

/**
	* @brief  Set value of TIMER load conuter0.
	* @param  TIMERx: where x can be  1 to 4, and BASETIMER
	* 	@arg  TIMER_1, TIMER_2, TIMER_3, TIMER_4, BASETIMER
	*/
uint32_t TIMER_GetCurrentCounter(TIMER_TypeDef* TIMERx)
{
	return TIMERx->CURCOUNT;
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
