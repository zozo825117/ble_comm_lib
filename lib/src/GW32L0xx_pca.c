/**
  ******************************************************************************
  * @file    GW32L0xx_pca.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_pca.h"

/**
	* @brief  Deinitialize PCA to PCA register reset value.
	* @param  PCAx: where x is 1 to 4. 
	* 	@arg  PCA_1, PCA_2, PCA_3, PCA_4
	*/
void PCA_DeInit(PCA_TypeDef* PCAx)
{
	uint32_t PCA_PERI_RESET;
	
	/* Select which PCA periperal to be deinitialized */
	PCA_PERI_RESET = ( PCAx == PCA_1 ? RMU_PERI_RESET0_PCA1 : \
										 PCAx == PCA_2 ? RMU_PERI_RESET0_PCA2 : \
										 PCAx == PCA_3 ? RMU_PERI_RESET0_PCA3 : RMU_PERI_RESET0_PCA4	);
	do
	{
		/* Restore PCA peripheral register to the reset value */
		PERI_RST_CTRL0 |= PCA_PERI_RESET;
		
	} while ( (PERI_RST_CTRL0 & PCA_PERI_RESET) != PCA_PERI_RESET );
	
	/* Switch to work in normal mode */
	PERI_RST_CTRL0 &= ~PCA_PERI_RESET;
}

/**
	* @brief  Initialize PCA_InitStruct with specified parameters.
	*/
void PCA_StructInit(PCA_InitTypeDef* PCA_InitStruct)
{
	PCA_InitStruct->PCA_Mode = PCA_Mode_NO;
	PCA_InitStruct->PCA_CntClkSel = PCA_CntClkSel_1_64PCLK;
	PCA_InitStruct->PCA_CCAPMSel = PCA_CCAPMSel_NO;
	PCA_InitStruct->PCA_CaptToggleEdge = PCA_CaptToggleEdge_NO;
	PCA_InitStruct->PCA_CmpMode = PCA_CmpMode_NO;
}

/**
	* @brief  Initialize PCA module with specified parameters as PCA_InitStruct.
	* @param  PCAx: where x is 1 to 4. 
	* 	@arg  PCA_1, PCA_2, PCA_3, PCA_4
	*/
void PCA_Init(PCA_TypeDef* PCAx, PCA_InitTypeDef* PCA_InitStruct)
{	
	uint32_t tmpreg = 0;
	
	if (PCA_InitStruct->PCA_Mode == PCA_Mode_NO)
	{
		return;
	}
	
	if (PCA_InitStruct->PCA_CCAPMSel != PCA_CCAPMSel_NO && PCA_InitStruct->PCA_Mode == PCA_Mode_CMP)
	{
		volatile uint32_t RegAddr = (PCAx == PCA_1) ? PCA_1_BASEADDR : \
			                          (PCAx == PCA_2) ? PCA_2_BASEADDR : \
																(PCAx == PCA_3) ? PCA_3_BASEADDR : PCA_4_BASEADDR;
		
		tmpreg = *(volatile uint32_t *)( (RegAddr + 0x10) + 4 * PCA_InitStruct->PCA_CCAPMSel );
		
		switch (PCA_InitStruct->PCA_CmpMode)
		{
			case PCA_CmpMode_SWCounter:
				tmpreg |= PCA_CCAPMx_ECOM;
				tmpreg &= ~(PCA_CCAPMx_CAPP | PCA_CCAPMx_CAPN);
				tmpreg |= PCA_CCAPMx_MAT;
				tmpreg &= ~PCA_CCAPMx_TOG;
				tmpreg &= ~PCA_CCAPMx_PWM;
				break;			
			case PCA_CmpMode_HSOutput:
				tmpreg |= PCA_CCAPMx_ECOM;
				tmpreg &= ~(PCA_CCAPMx_CAPP | PCA_CCAPMx_CAPN);
				tmpreg |= PCA_CCAPMx_MAT;
				tmpreg |= PCA_CCAPMx_TOG;
				tmpreg &= ~PCA_CCAPMx_PWM;				
				break;
			case PCA_CmpMode_WDT:
				if (PCA_InitStruct->PCA_CCAPMSel == PCA_CCAPMSel_CCAP4)
				{					
					tmpreg |= PCA_CCAPMx_ECOM;
					tmpreg &= ~(PCA_CCAPMx_CAPP | PCA_CCAPMx_CAPN);
					tmpreg |= PCA_CCAPMx_MAT;
					tmpreg &= ~PCA_CCAPMx_TOG;
					tmpreg &= ~PCA_CCAPMx_PWM;
				}				
				break;
			case PCA_CmpMode_PWM:
				tmpreg |= PCA_CCAPMx_ECOM;
				tmpreg &= ~(PCA_CCAPMx_CAPP | PCA_CCAPMx_CAPN);
				tmpreg &= ~PCA_CCAPMx_TOG;
				tmpreg |= PCA_CCAPMx_PWM;
				tmpreg &= ~PCA_CCAPMx_ECCF;		
				break;
			default:
				break;
		}
		
		*(volatile uint32_t *)( (RegAddr + 0x10) + 4 * PCA_InitStruct->PCA_CCAPMSel ) = tmpreg;		
	}
	
	if (PCA_InitStruct->PCA_CCAPMSel != PCA_CCAPMSel_NO && PCA_InitStruct->PCA_Mode == PCA_Mode_CAP)
	{
		volatile uint32_t RegAddr = (PCAx == PCA_1) ? PCA_1_BASEADDR : \
			                          (PCAx == PCA_2) ? PCA_2_BASEADDR : \
																(PCAx == PCA_3) ? PCA_3_BASEADDR : PCA_4_BASEADDR;		
		
		tmpreg = *(volatile uint32_t *)( (RegAddr + 0x10) + 4 * PCA_InitStruct->PCA_CCAPMSel );	
		
		tmpreg &= ~PCA_CCAPMx_MAT;
		tmpreg &= ~PCA_CCAPMx_TOG;
		tmpreg &= ~PCA_CCAPMx_PWM;
		tmpreg &= ~(PCA_CCAPMx_CAPP | PCA_CCAPMx_CAPN);
		tmpreg |= (PCA_InitStruct->PCA_CaptToggleEdge << 4);
		
		*(volatile uint32_t *)( (RegAddr + 0x10) + 4 * PCA_InitStruct->PCA_CCAPMSel ) = tmpreg;		
	}
	
	tmpreg = PCAx->CMOD;		
	tmpreg &= ~PCA_CMOD_CPS;
	tmpreg |= (PCA_InitStruct->PCA_CntClkSel << 1);
	if (PCA_InitStruct->PCA_CmpMode == PCA_CmpMode_WDT && PCA_InitStruct->PCA_CCAPMSel == PCA_CCAPMSel_CCAP4)
	{
		tmpreg |= PCA_CMOD_WDTE;
	}
	else
	{
		tmpreg &= ~PCA_CMOD_WDTE;
	}	
	PCAx->CMOD = tmpreg;
}

/**
	* @brief  Enable or disable PCA module.
	* @param  PCAx: where x is 1 to 4. 
	* 	@arg  PCA_1, PCA_2, PCA_3, PCA_4
	*/
void PCA_Cmd(PCA_TypeDef* PCAx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		do
		{
			PCAx->CCON |= PCA_CCON_CR;
			
		} while ( (PCAx->CCON & PCA_CCON_CR) != PCA_CCON_CR );
	}
	else
	{
		do
		{
			PCAx->CCON &= ~PCA_CCON_CR;

		} while ( (PCAx->CCON & PCA_CCON_CR) == PCA_CCON_CR );
	}
}

/**
	* @brief  Configurate PCA interrupt flag to enabled or disabled status.
	* @param  PCAx: where x is 1 to 4. 
	* 	@arg  PCA_1, PCA_2, PCA_3, PCA_4
	* @param  PCA_ITFlag, As follow:
	*		@arg  PCA_ITFlag_CCF0
	*		@arg  PCA_ITFlag_CCF1
	*		@arg  PCA_ITFlag_CCF2
	*		@arg  PCA_ITFlag_CCF3
	*	  @arg  PCA_ITFlag_CCF4
	*	  @arg  PCA_ITFlag_CF
	*   @ARG  PCA_ITFlag_ALL
	*/
void PCA_ITConfig(PCA_TypeDef* PCAx, PCA_ITFlag_TypeDef PCA_ITFlag, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		switch (PCA_ITFlag)
		{
			case PCA_ITFlag_CCF0:
				PCAx->CCAPM0 |= PCA_CCAPMx_ECCF;
				break;
			case PCA_ITFlag_CCF1:
				PCAx->CCAPM1 |= PCA_CCAPMx_ECCF;
				break;
			case PCA_ITFlag_CCF2:
				PCAx->CCAPM2 |= PCA_CCAPMx_ECCF;
				break;
			case PCA_ITFlag_CCF3:
				PCAx->CCAPM3 |= PCA_CCAPMx_ECCF;
				break;
			case PCA_ITFlag_CCF4:
				PCAx->CCAPM4 |= PCA_CCAPMx_ECCF;
				break;
			case PCA_ITFlag_CF:
				PCAx->CMOD |= PCA_CMOD_ECF;
				break;
			default:
				PCAx->CCAPM0 |= PCA_CCAPMx_ECCF;
				PCAx->CCAPM1 |= PCA_CCAPMx_ECCF;
				PCAx->CCAPM2 |= PCA_CCAPMx_ECCF;
				PCAx->CCAPM3 |= PCA_CCAPMx_ECCF;
				PCAx->CCAPM4 |= PCA_CCAPMx_ECCF;
				PCAx->CMOD |= PCA_CMOD_ECF;				
				break;
		}
	}
	else
	{
		switch (PCA_ITFlag)
		{
			case PCA_ITFlag_CCF0:
				PCAx->CCAPM0 &= ~PCA_CCAPMx_ECCF;
				break;
			case PCA_ITFlag_CCF1:
				PCAx->CCAPM1 &= ~PCA_CCAPMx_ECCF;
				break;
			case PCA_ITFlag_CCF2:
				PCAx->CCAPM2 &= ~PCA_CCAPMx_ECCF;
				break;
			case PCA_ITFlag_CCF3:
				PCAx->CCAPM3 &= ~PCA_CCAPMx_ECCF;
				break;
			case PCA_ITFlag_CCF4:
				PCAx->CCAPM4 &= ~PCA_CCAPMx_ECCF;
				break;
			case PCA_ITFlag_CF:
				PCAx->CMOD &= ~PCA_CMOD_ECF;
				break;
			default:
				PCAx->CCAPM0 &= ~PCA_CCAPMx_ECCF;
				PCAx->CCAPM1 &= ~PCA_CCAPMx_ECCF;
				PCAx->CCAPM2 &= ~PCA_CCAPMx_ECCF;
				PCAx->CCAPM3 &= ~PCA_CCAPMx_ECCF;
				PCAx->CCAPM4 &= ~PCA_CCAPMx_ECCF;
				PCAx->CMOD &= ~PCA_CMOD_ECF;				
				break;
		}
	}
}

/**
	* @brief  Get status of PCA interrupt flag.
	* @param  PCAx: where x is 1 to 4. 
	* 	@arg  PCA_1, PCA_2, PCA_3, PCA_4
	* @param  PCA_ITFlag, As follow:
	*		@arg  PCA_ITFlag_CCF0
	*		@arg  PCA_ITFlag_CCF1
	*		@arg  PCA_ITFlag_CCF2
	*		@arg  PCA_ITFlag_CCF3
	*	  @arg  PCA_ITFlag_CCF4
	*	  @arg  PCA_ITFlag_CF
	*   @ARG  PCA_ITFlag_ALL
	*/
ITStatus PCA_GetITStatus(PCA_TypeDef* PCAx, PCA_ITFlag_TypeDef PCA_ITFlag)
{
	return (PCAx->CCON & PCA_ITFlag) == PCA_ITFlag ? SET : RESET;
}

/**
	* @brief  Clear PCA interrupt flag.
	* @param  PCAx: where x is 1 to 4. 
	* 	@arg  PCA_1, PCA_2, PCA_3, PCA_4
	* @param  PCA_ITFlag, As follow:
	*		@arg  PCA_ITFlag_CCF0
	*		@arg  PCA_ITFlag_CCF1
	*		@arg  PCA_ITFlag_CCF2
	*		@arg  PCA_ITFlag_CCF3
	*	  @arg  PCA_ITFlag_CCF4
	*	  @arg  PCA_ITFlag_CF
	*   @ARG  PCA_ITFlag_ALL
	*/
void PCA_ClearITFlag(PCA_TypeDef* PCAx, PCA_ITFlag_TypeDef PCA_ITFlag)
{
	PCAx->CCON &= ~(PCA_ITFlag);
}

/**
	* @brief  Set HSB value of PCA counter.
	* @param  PCAx: where x is 1 to 4. 
	* 	@arg  PCA_1, PCA_2, PCA_3, PCA_4
	*/
void PCA_SetCounterHSB(PCA_TypeDef* PCAx, uint8_t CounterHSB)
{
	PCAx->CH = CounterHSB;
}

/**
	* @brief  Set LSB value of PCA counter.
	* @param  PCAx: where x is 1 to 4. 
	* 	@arg  PCA_1, PCA_2, PCA_3, PCA_4
	*/
void PCA_SetCounterLSB(PCA_TypeDef* PCAx, uint8_t CounterLSB)
{
	PCAx->CL = CounterLSB;
}

/**
	* @brief  Get HSB value of PCA counter.
	* @param  PCAx: where x is 1 to 4. 
	* 	@arg  PCA_1, PCA_2, PCA_3, PCA_4
	*/
uint8_t PCA_GetCounterHSB(PCA_TypeDef* PCAx)
{
	return PCAx->CH;
}

/**
	* @brief  Get LSB value of PCA counter.
	* @param  PCAx: where x is 1 to 4. 
	* 	@arg  PCA_1, PCA_2, PCA_3, PCA_4
	*/
uint8_t PCA_GetCounterLSB(PCA_TypeDef* PCAx)
{
	return PCAx->CL;
}

/**
	* @brief  Get value of PCA counter.
	* @param  PCAx: where x is 1 to 4. 
	* 	@arg  PCA_1, PCA_2, PCA_3, PCA_4
	*/
uint16_t PCA_GetCounter(PCA_TypeDef* PCAx)
{
	uint16_t vBuff = PCAx->CH << 8 ;
	return vBuff | PCAx->CL;
}

/**
	* @brief  Set HSB value of PCA CCAPM.
	* @param  PCAx: where x is 1 to 4. 
	* 	@arg  PCA_1, PCA_2, PCA_3, PCA_4
	* @param  PCA_CCAPMSel, as follow
	* 	@arg  PCA_CCAPMSel_CCAP0
	* 	@arg  PCA_CCAPMSel_CCAP1
	* 	@arg  PCA_CCAPMSel_CCAP2
	* 	@arg	PCA_CCAPMSel_CCAP3
	* 	@arg	PCA_CCAPMSel_CCAP4
	*/
void PCA_SetCapturerHSB(PCA_TypeDef* PCAx, PCA_CCAPMSel_TypeDef PCA_CCAPMSel, uint8_t CapturerHSB)
{
	if (PCA_CCAPMSel != PCA_CCAPMSel_NO)
	{
		volatile uint32_t RegAddr = (PCAx == PCA_1) ? PCA_1_BASEADDR : \
																(PCAx == PCA_2) ? PCA_2_BASEADDR : \
																(PCAx == PCA_3) ? PCA_3_BASEADDR : PCA_4_BASEADDR;
		
		*(volatile uint32_t *)( (RegAddr + 0x24) + 8 * PCA_CCAPMSel ) = CapturerHSB;
	}
}

/**
	* @brief  Set LSB value of PCA CCAPM.
	* @param  PCAx: where x is 1 to 4. 
	* 	@arg  PCA_1, PCA_2, PCA_3, PCA_4
	* @param  PCA_CCAPMSel, as follow
	* 	@arg  PCA_CCAPMSel_CCAP0
	* 	@arg  PCA_CCAPMSel_CCAP1
	* 	@arg  PCA_CCAPMSel_CCAP2
	* 	@arg	PCA_CCAPMSel_CCAP3
	* 	@arg	PCA_CCAPMSel_CCAP4
	*/
void PCA_SetCapturerLSB(PCA_TypeDef* PCAx, PCA_CCAPMSel_TypeDef PCA_CCAPMSel, uint8_t CapturerLSB)
{
	if (PCA_CCAPMSel != PCA_CCAPMSel_NO)
	{
		volatile uint32_t RegAddr = (PCAx == PCA_1) ? PCA_1_BASEADDR : \
																(PCAx == PCA_2) ? PCA_2_BASEADDR : \
																(PCAx == PCA_3) ? PCA_3_BASEADDR : PCA_4_BASEADDR;
		
		*(volatile uint32_t *)( (RegAddr + 0x28) + 8 * PCA_CCAPMSel ) = CapturerLSB;
	}
}

/**
	* @brief  Get HSB value of PCA CCAPM.
	* @param  PCAx: where x is 1 to 4. 
	* 	@arg  PCA_1, PCA_2, PCA_3, PCA_4
	* @param  PCA_CCAPMSel, as follow
	* 	@arg  PCA_CCAPMSel_CCAP0
	* 	@arg  PCA_CCAPMSel_CCAP1
	* 	@arg  PCA_CCAPMSel_CCAP2
	* 	@arg	PCA_CCAPMSel_CCAP3
	* 	@arg	PCA_CCAPMSel_CCAP4
	*/
uint8_t PCA_GetCapturerHSB(PCA_TypeDef* PCAx, PCA_CCAPMSel_TypeDef PCA_CCAPMSel)
{
	if (PCA_CCAPMSel != PCA_CCAPMSel_NO)
	{
		volatile uint32_t RegAddr = (PCAx == PCA_1) ? PCA_1_BASEADDR : \
																(PCAx == PCA_2) ? PCA_2_BASEADDR : \
																(PCAx == PCA_3) ? PCA_3_BASEADDR : PCA_4_BASEADDR;
		
		return *(volatile uint32_t *)( (RegAddr + 0x24) + 8 * PCA_CCAPMSel );
	}
	else
	{
		return 0;
	}
}

/**
	* @brief  Get LSB value of PCA CCAPM.
	* @param  PCAx: where x is 1 to 4. 
	* 	@arg  PCA_1, PCA_2, PCA_3, PCA_4
	* @param  PCA_CCAPMSel, as follow
	* 	@arg  PCA_CCAPMSel_CCAP0
	* 	@arg  PCA_CCAPMSel_CCAP1
	* 	@arg  PCA_CCAPMSel_CCAP2
	* 	@arg	PCA_CCAPMSel_CCAP3
	* 	@arg	PCA_CCAPMSel_CCAP4
	* 	@arg 	PCA_CCAPMSel_NO
	*/
uint8_t PCA_GetCapturerLSB(PCA_TypeDef* PCAx, PCA_CCAPMSel_TypeDef PCA_CCAPMSel)
{
	if (PCA_CCAPMSel != PCA_CCAPMSel_NO)
	{
		volatile uint32_t RegAddr = (PCAx == PCA_1) ? PCA_1_BASEADDR : \
																(PCAx == PCA_2) ? PCA_2_BASEADDR : \
																(PCAx == PCA_3) ? PCA_3_BASEADDR : PCA_4_BASEADDR;
		
		return *(volatile uint32_t *)( (RegAddr + 0x28) + 8 * PCA_CCAPMSel );
	}
	else
	{
		return 0;
	}
}

/**
	* @brief  Get value of PCA CCAPM.
	* @param  PCAx: where x is 1 to 4. 
	* 	@arg  PCA_1, PCA_2, PCA_3, PCA_4
	* @param  PCA_CCAPMSel, as follow
	* 	@arg  PCA_CCAPMSel_CCAP0
	* 	@arg  PCA_CCAPMSel_CCAP1
	* 	@arg  PCA_CCAPMSel_CCAP2
	* 	@arg	PCA_CCAPMSel_CCAP3
	* 	@arg	PCA_CCAPMSel_CCAP4
	* 	@arg 	PCA_CCAPMSel_NO
	*/
uint16_t PCA_GetCapturer(PCA_TypeDef* PCAx, PCA_CCAPMSel_TypeDef PCA_CCAPMSel)
{
	if (PCA_CCAPMSel != PCA_CCAPMSel_NO)
	{
		volatile uint32_t RegAddr = (PCAx == PCA_1) ? PCA_1_BASEADDR : \
                    (PCAx == PCA_2) ? PCA_2_BASEADDR : \
                    (PCAx == PCA_3) ? PCA_3_BASEADDR : PCA_4_BASEADDR;

		uint32_t vBuff = *(volatile uint32_t *)( (RegAddr + 0x24) + 8 * PCA_CCAPMSel ) << 8;
		return  vBuff | *(volatile uint32_t *)( (RegAddr + 0x28) + 8 * PCA_CCAPMSel );
	}
	else
	{
		return 0;
	}
}

/**
* @brief  Set Polarity of PCA channels output level accoording to specified parameters.
	* @param  PCAx: where x is 1 to 4. 
	* 	@arg  PCA_1, PCA_2, PCA_3, PCA_4
	* @param  PCA_CCAPMSel, as follow
	* 	@arg  PCA_CCAPMSel_CCAP0
	* 	@arg  PCA_CCAPMSel_CCAP1
	* 	@arg  PCA_CCAPMSel_CCAP2
	* 	@arg	PCA_CCAPMSel_CCAP3
	* 	@arg	PCA_CCAPMSel_CCAP4
	* 	@arg 	PCA_CCAPMSel_NO
	* @param  PCA_CCAPOPolarity, as follow
	* 	@arg	PCA_CCAPOPolarity_Low
	* 	@arg 	PCA_CCAPOPolarity_High
	*/
void PCA_CCAPOPolarityConfig(PCA_TypeDef* PCAx, PCA_CCAPMSel_TypeDef PCA_CCAPMSel, PCA_CCAPOPolarity_TypeDef PCA_CCAPOPolarity)
{
	if (PCA_CCAPMSel != PCA_CCAPMSel_NO)
	{
		if (PCA_CCAPOPolarity != PCA_CCAPOPolarity_Low)
		{
			PCAx->CCAPO |= (PCA_CCAPOPolarity_High << PCA_CCAPMSel);
		}
		else
		{
			PCAx->CCAPO &= ~(PCA_CCAPOPolarity_High << PCA_CCAPMSel);		
		}
	}
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
