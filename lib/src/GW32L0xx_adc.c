/**
  ******************************************************************************
  * @file    GW32L0xx_adc.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_adc.h"

/**
	* @brief  Deinitialize ADC relevant register to reset value.
	*/
void ADC_DeInit(void)
{
	do
	{
		/* Restore ADC peripheral register to the reset value */
		PERI_RST_CTRL0 |= RMU_PERI_RESET0_ADC;
		
	} while ( (PERI_RST_CTRL0 & RMU_PERI_RESET0_ADC) != RMU_PERI_RESET0_ADC );
	
	/* Switch to work in normal mode */
	PERI_RST_CTRL0 &= ~RMU_PERI_RESET0_ADC;
}

/**
	* @brief  Fills each ADC_InitStruct member with its default value.
	* @param  ADC_InitStruct : pointer to an ADC_InitTypeDef structure which will be initialized.
	* @retval None
	*/
void ADC_StructInit(ADC_InitTypeDef* ADC_InitStruct)
{
	ADC_InitStruct->ADC_ConvMode = ADC_ConvMode_Single;
	
	ADC_InitStruct->ADC_ClkSel = ADC_ClkSel_PCLK;
	
	ADC_InitStruct->ADC_RefVoltSel = ADC_RefVoltSel_2P5V;	
	ADC_InitStruct->ADC_InputSignalSel = ADC_InputSignalSel_PORT0_Pin_0;
	ADC_InitStruct->ADC_InterSigSourceSel = ADC_InterSigSourceSel_0P5VCC_1VCC;
	ADC_InitStruct->ADC_SignalAmpEn = ADC_SignalAmpEn_DISABLE;
	
	ADC_InitStruct->ADC_SampleCycleSel = ADC_SampleCycleSel_3Cycles;
	
	ADC_InitStruct->ADC_SampleChannelSel = ADC_SampleChannelSel_NO;
	
	ADC_InitStruct->ADC_ResultAccEn = ADC_ResultAccEn_DISABLE;
	
	ADC_InitStruct->ADC_ContinuousSamplePeriod = 0x0;	
}

/**
	* @brief  Initializes the ADCx peripheral according to the specified parameters
	*         in the ADC_InitStruct.
	* @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that contains
	*         the configuration information for the specified ADC peripheral.
	* @retval None
	*/
void ADC_Init(ADC_InitTypeDef* ADC_InitStruct)
{
	volatile uint32_t tmpreg0 = 0, tmpreg = 0;
	
	tmpreg0 = ADC_CTRL0;

	do 
	{
		ADC_CTRL0 &= ~ADC_CTRL0_ADCEN;
		
	} while ((ADC_CTRL0 & ADC_CTRL0_ADCEN) == ADC_CTRL0_ADCEN);
	
	tmpreg = ADC_CTRL2;
	tmpreg &= ~(ADC_InitStruct->ADC_SampleChannelSel);
	tmpreg |= ADC_InitStruct->ADC_SampleChannelSel;
	tmpreg &= ~ADC_CTRL2_ADCCNT;
	tmpreg |= (ADC_InitStruct->ADC_ContinuousSamplePeriod << 8);
	ADC_CTRL2 = tmpreg;

	tmpreg = ADC_CTRL1;
	tmpreg &= ~ADC_CTRL1_CT;
	tmpreg |= (ADC_InitStruct->ADC_ConvMode << 10);
	tmpreg &= ~ADC_CTRL1_RACC_EN;
	tmpreg |= (ADC_InitStruct->ADC_ResultAccEn << 11);
	ADC_CTRL1 = tmpreg;	
	
	tmpreg0 &= ~ADC_CTRL0_CLKS;
	tmpreg0 |= (ADC_InitStruct->ADC_ClkSel << 3);
	tmpreg0 &= ~ADC_CTRL0_SREF;
	tmpreg0 |= (ADC_InitStruct->ADC_RefVoltSel << 10);
	tmpreg0 &= ~ADC_CTRL0_SEL;
	tmpreg0 |= (ADC_InitStruct->ADC_InputSignalSel << 5);
	tmpreg0 &= ~ADC_CTRL0_ISS;
	tmpreg0 |= (ADC_InitStruct->ADC_InterSigSourceSel << 8);
	tmpreg0 &= ~ADC_CTRL0_BUFEN;
	tmpreg0 |= (ADC_InitStruct->ADC_SignalAmpEn << 12);
	tmpreg0 &= ~ADC_CTRL0_SAM;
	tmpreg0 |= (ADC_InitStruct->ADC_SampleCycleSel << 13);
	ADC_CTRL0 = tmpreg0;
}

/**
	* @brief  Enable or disable ADC module.
	*/
void ADC_Cmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{	
		do 
		{		
			volatile uint16_t num = 16 * 30;
			
			ADC_CTRL0 |= ADC_CTRL0_ADCEN;		
			while (num--);
			
		} while ((ADC_CTRL0 & ADC_CTRL0_ADCEN) != ADC_CTRL0_ADCEN);
	}
	else
	{
		ADC_CTRL0 &= ~ADC_CTRL0_ADCEN;
	}
}

/**
	* @brief  Configurate other peripherals to trigge ADC convert.
	*
	* @param  ADC_PeriphReflectModuleSel:
	* 	@arg  ADC_PeriphRefModuleSel_1
	* 	@arg 	ADC_PeriphRefModuleSel_2
	*
	* @param  ADC_PeriphRefTrigSource:
	* 	@arg	ADC_PeriphRefTrigSource_PORT_0
	* 	@arg	ADC_PeriphRefTrigSource_PORT_1
	* 	@arg	ADC_PeriphRefTrigSource_PORT_2
	* 	@arg	ADC_PeriphRefTrigSource_PORT_3
	* 	@arg	ADC_PeriphRefTrigSource_PORT_4
	* 	@arg	ADC_PeriphRefTrigSource_PORT_5
	* 	@arg	ADC_PeriphRefTrigSource_PORT_6
	* 	@arg	ADC_PeriphRefTrigSource_TIMER_0
	* 	@arg	ADC_PeriphRefTrigSource_TIMER_1
	* 	@arg	ADC_PeriphRefTrigSource_TIMER_2
	* 	@arg	ADC_PeriphRefTrigSource_TIMER_3
	* 	@arg	ADC_PeriphRefTrigSource_BASETIMER
	* 	@arg	ADC_PeriphRefTrigSource_UART_1
	* 	@arg	ADC_PeriphRefTrigSource_UART_2
	* 	@arg	ADC_PeriphRefTrigSource_UART_3
	* 	@arg	ADC_PeriphRefTrigSource_UART_4
	* 	@arg	ADC_PeriphRefTrigSource_UART_5
	* 	@arg	ADC_PeriphRefTrigSource_UART_6
	* 	@arg	ADC_PeriphRefTrigSource_SPI_1
	* 	@arg	ADC_PeriphRefTrigSource_SPI_2
	* 	@arg	ADC_PeriphRefTrigSource_SPI_3
	* 	@arg	ADC_PeriphRefTrigSource_SPI_4
	* 	@arg	ADC_PeriphRefTrigSource_PCA_1
	* 	@arg	ADC_PeriphRefTrigSource_PCA_2
	* 	@arg	ADC_PeriphRefTrigSource_PCA_3
	* 	@arg	ADC_PeriphRefTrigSource_PCA_4
	* 	@arg	ADC_PeriphRefTrigSource_VC
	* 	@arg	ADC_PeriphRefTrigSource_LVD
	* 	@arg	ADC_PeriphRefTrigSource_LCD
	* 	@arg	ADC_PeriphRefTrigSource_DMA 
	* 	@arg	ADC_PeriphRefTrigSource_RTC   
	*/
void ADC_PeriphReflectTrigConvCmd( ADC_PeriphRefModuleSel_TypeDef ADC_PeriphReflectModuleSel, 
	                                 ADC_PeriphRefTrigSource_TypeDef ADC_PeriphRefTrigSource, 
                                   FunctionalState NewState)
{
	ADC_CTRL1 &= ~(ADC_CTRL1_TRIGS1 << ADC_PeriphReflectModuleSel);
		
	if (NewState != DISABLE)
	{
		ADC_CTRL1 |= (ADC_PeriphRefTrigSource << ADC_PeriphReflectModuleSel);
	}
}

/**
	* @brief  Enable or disable temperature sensor in chip to power on.
	*/
void ADC_TempSensorCmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		do 
		{			
			volatile uint16_t num = 16 * 20;
			
			ADC_CTRL0 |= ADC_CTRL0_TSEN;
			while (num--);
			
		} while ((ADC_CTRL0 & ADC_CTRL0_TSEN) != ADC_CTRL0_TSEN);
	}
	else
	{
		ADC_CTRL0 &= ~ADC_CTRL0_TSEN;
	}
}

/**
	* @brief  Use Software to make ADC module start to convert.
	*/
void ADC_SoftwareStartConvCmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		ADC_CTRL0 |= ADC_CTRL0_START;
	}
	else
	{
		ADC_CTRL0 &= ~ADC_CTRL0_START;
	}	
}

/**
	* @brief  Enable or disable BGR module.
	*/
void ADC_BGRCmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		do
		{
			volatile uint16_t num = 16 * 30;
			
			BGR_CTRL |= ADC_BGR_CTRL_EN;
			while (num--);
			
		} while ((BGR_CTRL & ADC_BGR_CTRL_EN) != ADC_BGR_CTRL_EN);
	}
	else
	{
		BGR_CTRL &= ~ADC_BGR_CTRL_EN;
	}
}

/**
	* @brief  Enable VCC or 1/2VCC use as input of internal signal source.
	* @param  ADC_InterSigSourceVCCDiv:
	* 	@arg  ADC_InterSignalSourceVCCDiv_1VCC
	*	  @arg  ADC_InterSignalSourceVCCDiv_0P5VCC
	*/
void ADC_InterSignalSourceVCCConfig(ADC_InterSignalSourceVCCDiv_TypeDef ADC_InterSignalSourceVCCDiv)
{
	if (ADC_InterSignalSourceVCCDiv != ADC_InterSignalSourceVCCDiv_1VCC)
	{
		do
		{
			volatile uint32_t num = 16 * 30;
			VC_CTRL0 |= VC_CTRL0_VCCDIV2EN;
			while (num--);
			
		} while ((VC_CTRL0 & VC_CTRL0_VCCDIV2EN) != VC_CTRL0_VCCDIV2EN);
	}
	else
	{
		do
		{
			volatile uint32_t num = 16 * 30;
			
			VC_CTRL0 &= ~VC_CTRL0_VCCDIV2EN;
			while (num--);	
				
		} while ((VC_CTRL0 & VC_CTRL0_VCCDIV2EN) == VC_CTRL0_VCCDIV2EN);
	}
}

/**
	* @brief  Get value of ADC from the specified channel.
	* @param  ADC_ResultSel:
	* 	@arg  ADC_ResultSel_Result_0
	* 	@arg 	ADC_ResultSel_Result_1
	* 	@arg	ADC_ResultSel_Result_2
	* 	@arg	ADC_ResultSel_Result_3
	* 	@arg	ADC_ResultSel_Result_4
	* 	@arg	ADC_ResultSel_Result_5
	* 	@arg	ADC_ResultSel_Result_6
	* 	@arg	ADC_ResultSel_Result_7	
	* 	@arg	ADC_ResultSel_Result_ACC
	*/
uint32_t ADC_GetResult(ADC_ResultSel_TypeDef ADC_ResultSel)
{
	if (ADC_ResultSel != ADC_ResultSel_Result_ACC)
	{
		return  ( (*(volatile uint32_t *)( (ANALOG_CTRL_BASEADDR + 0x80) + 4 * ADC_ResultSel )) & ADC_RESULT_0 );
	}
	else
	{
		return ADC_RESULT_ACC & ADC_RESULT_Acc;
	}
}

/**
	* @brief  Set sampling times of ADC in continuous mode.
	* @param  ADC_ContinuousSampleCounter: range@(0...255)
	*/
void ADC_SetContinuousSampleCounter(uint8_t ADC_ContinuousSampleCounter)
{
	ADC_CTRL2 &= ~ADC_CTRL2_ADCCNT;
	ADC_CTRL2 |= (ADC_ContinuousSampleCounter << 8);
}

/**
	* @brief  Get completed flag of ADC.
	*/
FlagStatus ADC_GetConvCompletedFlagStatus(void)
{
	return (ADC_CTRL0 & ADC_CTRL0_START) != ADC_CTRL0_START ? SET : RESET;
}

/**
	* @brief  Get interrupt flag of ADC.
	*/
ITStatus ADC_GetITStatus(void)
{
	return (ADC_CTRL0 & ADC_CTRL0_INTCLR) != ADC_CTRL0_INTCLR ? SET : RESET;
}

/**
	* @brief  Clear ADC interrupt flag.
	*/
void ADC_ClearITFlag(void)
{
	ADC_CTRL0 &= ~ADC_CTRL0_INTCLR;	
}

/**
	* @brief  Clear value of ACC register.
	*/
void ADC_ClearResultAcc(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		ADC_CTRL1 &= ~ADC_CTRL1_RACC_CLR;
	}
	else
	{
		ADC_CTRL1 |= ADC_CTRL1_RACC_CLR;
	}	
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
