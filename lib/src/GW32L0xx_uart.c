/**
  ******************************************************************************
  * @file    GW32L0xx_uart.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides all the UART firmware functions.
  *
 @verbatim
**/

#include "GW32L0xx_uart.h"

/**
  * @brief  Deinitializes the UARTx peripheral registers to their default reset values.
  * @param  USARTx: Select the UART peripheral. 
  *         This parameter can be one of the following values.
  * 	@arg  UART_1, UART_2, UART_3, UART_4, UART_5, UART_6.
  * @retval None
	*/	
void UART_DeInit(UART_TypeDef* UARTx)
{
	uint32_t UART_PERI_RESET;
	
	/* Select which uart periperal to be deinitialized */
	UART_PERI_RESET = ( UARTx == UART_1 ? RMU_PERI_RESET0_UART1 : \
											UARTx == UART_2 ? RMU_PERI_RESET0_UART2 : \
											UARTx == UART_3 ? RMU_PERI_RESET0_UART3 : \
											UARTx == UART_4 ? RMU_PERI_RESET0_UART4 : \
											UARTx == UART_5 ? RMU_PERI_RESET0_UART5 : RMU_PERI_RESET0_UART6 );	
	do
	{
		/* Restore port peripheral register to the reset value */
		PERI_RST_CTRL0 |= UART_PERI_RESET;
		
	} while ( (PERI_RST_CTRL0 & UART_PERI_RESET) != UART_PERI_RESET );
	
	/* Switch to work in normal mode */
	PERI_RST_CTRL0 &= ~UART_PERI_RESET;	
}

/**
  * @brief  Fills each UART_InitStruct member with its default value.
  * @param  USART_InitStruct: pointer to a UART_InitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void UART_StructInit(UART_InitTypeDef* UART_InitStruct)
{
	/* UART_InitStruct members default value */	
	UART_InitStruct->UART_BaudRate = 9600;
	UART_InitStruct->UART_DataLength = UART_DataLength_8Bits;
	UART_InitStruct->UART_StopBits = UART_StopBits_1Bit;
	UART_InitStruct->UART_Parity = UART_Parity_Even;
	UART_InitStruct->UART_HardwareFlowControl = UART_HardwareFlowControl_None;  
}

/**
	* @brief  Initializes the UARTx peripheral according to the specified
  *         parameters in the UART_InitStruct .
  * @param  UARTx: Select the UART or the UART peripheral. 
  *   			This parameter can be one of the following values.
  * 	@arg  UART_1, USART_2, UART_3, UART_4, UART_5, UART_6.
  * @param  UART_InitStruct: pointer to a UART_InitTypeDef structure
  *         that contains the configuration information for the specified UART 
  *         peripheral.
  * @retval None
  */
void UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct)
{
	volatile uint8_t tmpreg = 0;
	
	/* Before Programing BDL/BDH must enable BDRAE bit */
	UARTx->LNCR |= UART_LNCR_BDRAE;
	
	if (UARTx != UART_6)
	{
		
		uint32_t SYSCLK = ( (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) == CMU_SYSCLK0_SYSCLK_SEL_XHFOSC ? HSE_VALUE : \
												(SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) == CMU_SYSCLK0_SYSCLK_SEL_IRC38K ? LSI_VALUE : \
											  (SYSCLK0 & CMU_SYSCLK0_SYSCLK_SEL) == CMU_SYSCLK0_SYSCLK_SEL_XLFOSC ? LSE_VALUE : HSI_VALUE );
		
		uint32_t HCLK = SYSCLK >> ( (SYSCLK0 & CMU_SYSCLK0_AHB_CLK_DIV) >> 6 );
		
		uint32_t PCLK = HCLK >> ( (SYSCLK0 & CMU_SYSCLK0_APB_CLK_DIV) >> 9 );

		float BDRT_FLT = (float)PCLK / UART_InitStruct->UART_BaudRate / 16;
		
		UARTx->BDL = (uint8_t)( (uint32_t)(BDRT_FLT + 0.5) > (uint32_t)BDRT_FLT ? (uint32_t)BDRT_FLT + 1 : (uint32_t)BDRT_FLT );						
		UARTx->BDH = (uint8_t)( ((uint32_t)(BDRT_FLT + 0.5) > (uint32_t)BDRT_FLT ? (uint32_t)BDRT_FLT + 1 : (uint32_t)BDRT_FLT) >> 8 );
	}
	else
	{ 
		uint32_t LPUARTCLK = ( (SYSCLK1 & CMU_SYSCLK1_LPUART_CS) != CMU_LPUARTCLK_IRC38K ? LSE_VALUE : LSI_VALUE );
		
		float BDRT_FLT = (float)LPUARTCLK / UART_InitStruct->UART_BaudRate / 4;
		
		UARTx->BDL = (uint8_t)( (uint32_t)(BDRT_FLT + 0.5) > (uint32_t)BDRT_FLT ? (uint32_t)BDRT_FLT + 1 : (uint32_t)BDRT_FLT );						
		UARTx->BDH = (uint8_t)( ((uint32_t)(BDRT_FLT + 0.5) > (uint32_t)BDRT_FLT ? (uint32_t)BDRT_FLT + 1 : (uint32_t)BDRT_FLT) >> 8 );		
	}
	
	/* After setting BDL/BDH must disable BDRAE bit */
	UARTx->LNCR &= ~UART_LNCR_BDRAE;

	/* Restore value of LNCR register */
	tmpreg = UARTx->LNCR;

	/* Clear DLENS bit to refresh */
	tmpreg &= ~UART_LNCR_DLENS;
	
	/* Fill DLENS bit with specified paramters */
	tmpreg |= ( (UART_InitStruct->UART_DataLength == UART_DataLength_8Bits) ? UART_DataLength_8Bits : \
							(UART_InitStruct->UART_DataLength == UART_DataLength_7Bits) ? UART_DataLength_7Bits : \
							(UART_InitStruct->UART_DataLength == UART_DataLength_6Bits) ? UART_DataLength_6Bits : UART_DataLength_5Bits );

	/* clear STOP bit to refresh */
	tmpreg &= ~UART_LNCR_STOP;

	/* Fill STOP bit with specified parameters */
	tmpreg |= ( (UART_InitStruct->UART_StopBits != UART_StopBits_1Bit) ? UART_LNCR_STOP : 0 );
	
	/* Configurate initial value of PARITY bit */
	if (UART_InitStruct->UART_Parity == UART_Parity_None)
	{
		tmpreg &= ~UART_LNCR_PAREN;
	}
	else
	{
		tmpreg |= UART_LNCR_PAREN;
		
		switch (UART_InitStruct->UART_Parity)
		{
			case UART_Parity_Force_0:
				tmpreg |= UART_LNCR_FPAR;
				tmpreg |= UART_LNCR_PARS;
				break;
			case UART_Parity_Force_1:
				tmpreg |= UART_LNCR_FPAR;
				tmpreg &= ~UART_LNCR_PARS;
				break;
			default:
				tmpreg &= ~UART_LNCR_FPAR;		
				if (UART_InitStruct->UART_Parity == UART_Parity_Even)
					tmpreg |= UART_LNCR_PARS;
				else	
					tmpreg &= ~UART_LNCR_PARS;				
				break;
		}
	}

	/* Update value of LNCR register */
	UARTx->LNCR = tmpreg;
}

/**
	* @brief  Enable or disable to send interrupt flag to core NVIC.
	* @brief  UARTx, as follow
  * 	@arg  UART_1, USART_2, UART_3, UART_4, UART_5, UART_6.
  * @param  UART_IT: specifies the UART interrupt source to check.
  *   			This parameter can be one of the following values: 
  *   @arg  UART_IT_MDMStatusIE 
  *   @arg  UART_IT_LineStatusIE  
  *   @arg  UART_IT_TXREmptyIE  
  *   @arg  UART_IT_ReceiveData_RXFIFOTimeOutIE
	*   @arg  UART_IT_All
  */
void UART_ITConfig(UART_TypeDef* UARTx, uint8_t UART_IT, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		UARTx->INTENR |= UART_IT;
	}
	else
	{
		UARTx->INTENR &= ~UART_IT;
	}
}

/** 
  * @brief  Configrate uart work at FIFO mode.
  * @param  UARTx, as follow 
  *   @arg  UART1, UART2
  */
void UART_FIFOModeConfig( UART_TypeDef* UARTx, \
													UART_TxFIFOThreshValue_TypeDef TxFIFOThreshValue, \
													UART_RxFIFOThreshValue_TypeDef RxFIFOThreshValue, \
                          FunctionalState NewState)
{
	volatile uint8_t tmpreg = 0;

	/* Restore value of FIFOCR register */
	tmpreg = UARTx->FIFOCR;
	
	if (NewState != DISABLE)
	{
		if ((UARTx->FIFOCR & UART_FIFOCR_FIFOEN) == UART_FIFOCR_FIFOEN)
		{
			/* Reset FIFO if FIFO was enabled */
			tmpreg |= (UART_FIFOCR_TXFIFORST | UART_FIFOCR_RXFIFORST);
		}
		else
		{
			/* Enable FIFO */
			tmpreg |= UART_FIFOCR_FIFOEN;			
		}	
		
		/* Configurate initial threshold value of TXFIFO and RXFIFO */
		tmpreg |= (TxFIFOThreshValue << 4 | RxFIFOThreshValue << 6);
	}
	else
	{
		/* Disable FIFO */
		tmpreg &= ~UART_FIFOCR_FIFOEN;
	}
	
	/* Update value of FIFOCR register */
	UARTx->FIFOCR = tmpreg;
}

/**
	* @brief  Check out if TXFIFO is full in FIFO mode.
	* @param  UARTx, as follow
  *  	@arg  UART1, UART2
  */
void UART_PTXREModeConfig(UART_TypeDef* UARTx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		UARTx->INTENR |= UART_INTENR_PTXRE;
	}
	else
	{
		UARTx->INTENR &= ~UART_INTENR_PTXRE;
	}
}

/**
	* @brief  Get status of enabled interrupt.
	* @param  UARTx, as follow
  *		@arg  UART1, UART2, UART3, UART4, UART5, UART6.
  * @param  UART_IntID: specifies the UART interrupt source to check.
  *         This parameter can be one of the following values:
	* 	@arg  UART_IntID_MDMStatus
	* 	@arg  UART_IntID_None
	* 	@arg  UART_IntID_TXREmpty
	* 	@arg  UART_IntID_ReceiveData
	* 	@arg  UART_IntID_LineStatus
	* 	@arg  UART_IntID_RXFIFOTimeOut  
  */
ITStatus UART_GetITStatus(UART_TypeDef* UARTx, UART_IntID_Typedef UART_IntID)
{
	return ( (UARTx->INTIDR & UART_INTIDR_INIDR) == UART_IntID ) ?  SET : RESET;
}

/**
	* @brief  Get line status of UART.
	* @param  UARTx, as follow
  *  	@arg  UART1, UART2, UART3, UART4, UART5, UART6.
	* @param  UART_LSFlag as follow: 
  *   @arg  UART_LSFLAG_RXFIFOError                                         
  *   @arg  UART_LSFLAG_TXEmpty                                            
	*	  @arg  UART_LSFLAG_TXREmpty_TXFIFOFull                                               
  *	  @arg  UART_LSFLAG_BreakInterrupt                                       
	*	  @arg  UART_LSFLAG_FrameError                                                   
	*		@arg  UART_LSFLAG_ParityError                                                 
	*		@arg  UART_LSFLAG_OverFlowError                                                  
	*		@arg  UART_LSFLAG_DataReady
	*/
FlagStatus UART_GetLineStatus(UART_TypeDef* UARTx, uint16_t UART_LSFlag)
{
	return (UARTx->LNSR & UART_LSFlag) ?  SET : RESET;
}

/**
	* @brief  Get modulator-demodulator status of UART.
	* @param  UARTx, as follow
  * 	@arg  UART1, UART2
	* @param  UART_MDMFlag as follow: 
  *   @arg  UART_MDMSFLAG_DCD                                           
  *   @arg  UART_MDMSFLAG_RI                                             
	*	  @arg  UART_MDMSFLAG_DSR                                                  
	*		@arg  UART_MDMSFLAG_CTS                                                    
	*		@arg  UART_MDMSFLAG_DCDA                                                   
	*		@arg  UART_MDMSFLAG_RIA                                                 
	*		@arg  UART_MDMSFLAG_DSRA                                                  
	*		@arg  UART_MDMSFLAG_CTSA
  */
FlagStatus UART_GetMDMStatus(UART_TypeDef* UARTx, uint16_t UART_MDMSFlag)
{
	return (UARTx->MDMSR & UART_MDMSFlag) ?  SET : RESET;
}	

/**
  * @brief  UART Send data.
	* @param  UARTx, as follow
  *  	@arg  UART1, UART2, UART3, UART4, UART5, UART6.
  */
void UART_SendData(UART_TypeDef* UARTx, uint8_t Data)
{   
  UARTx->TXR = (Data & UART_TXR);
}

/**
  * @brief  UART Receive data.
	* @param  UARTx, as follow
  *  	@arg  UART1, UART2, UART3, UART4, UART5, UART6.
  */
uint8_t UART_ReceiveData(UART_TypeDef* UARTx)
{
	return (UARTx->RXR & UART_RXR);
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
