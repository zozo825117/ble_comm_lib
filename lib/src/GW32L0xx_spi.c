/**
  ******************************************************************************
  * @file    GW32L0xx_spi.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides all the SPI firmware functions.
  *
 @verbatim
**/

#include "GW32L0xx_spi.h"

/**
	* @brief  Deinitializes the SPIx peripheral registers to their default
	*         reset values.
	* @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
	*  				As follow:
	*		@arg  SPIM_1, SPIM_2, SPIM_3, SPIM_4                    
	*   @arg  SPIS_1, SPIS_2, SPIS_3, SPIS_4               
	* @retval None
	*/
void SPI_DeInit(SPI_TypeDef* SPIx)
{
	uint32_t SPI_PERI_RESET;
	
	/* Select which SPI periperal to be deinitialized */
	SPI_PERI_RESET = ( SPIx == SPIM_1 ? RMU_PERI_RESET0_SPI1 : \
										 SPIx == SPIM_2 ? RMU_PERI_RESET0_SPI2 : \
										 SPIx == SPIM_3 ? RMU_PERI_RESET0_SPI3 : \
										 SPIx == SPIM_4 ? RMU_PERI_RESET0_SPI4 : \
										 SPIx == SPIS_1 ? RMU_PERI_RESET0_SPI1 : \
										 SPIx == SPIS_2 ? RMU_PERI_RESET0_SPI2 : \
										 SPIx == SPIS_3 ? RMU_PERI_RESET0_SPI3 : RMU_PERI_RESET0_SPI4 );
	do
	{
		/* Restore SPI peripheral register to the reset value */
		PERI_RST_CTRL0 |= SPI_PERI_RESET;
		
	} while ( (PERI_RST_CTRL0 & SPI_PERI_RESET) != SPI_PERI_RESET );
	
	/* Switch to work in normal mode */
	PERI_RST_CTRL0 &= ~SPI_PERI_RESET;
}

/**
	* @brief  Fills each SPI_InitStruct member with its default value.
	* @param  SPI_InitStruct : pointer to a SPI_InitTypeDef structure which will be initialized.
	* @retval None
	*/
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
	SPI_InitStruct->SPI_Mode = SPI_Mode_TxRx;
	
	SPI_InitStruct->SPI_Protcl = SPI_Protcl_Motorola;
	
	SPI_InitStruct->SPI_CPOL = SPI_ClkPol_Low;
	
	SPI_InitStruct->SPI_CPHA = SPI_ClkPha_1Edge;

	SPI_InitStruct->SPI_MWProtclHandShake = SPI_MWProtclHandShake_DISABLE;	
	SPI_InitStruct->SPI_MWProtclComdSize = SPI_MWProtclComdSize_1Bits;
	SPI_InitStruct->SPI_MWProtclMode =SPI_MWProtclMode_Discontinue;
	SPI_InitStruct->SPI_MWProtclDir = SPI_MWProtclDIR_Rx;
	
	SPI_InitStruct->SPI_DataSize = SPI_DataSize_8Bits;

	SPI_InitStruct->SPI_BaudRatePrescaler = 0x0;
	
	SPI_InitStruct->SPI_DataNum = 0x0;
	
	SPI_InitStruct->SPI_RxFIFOThreshValue = 0x0;
	SPI_InitStruct->SPI_TxFIFOThreshValue = 0x0;
	
	SPI_InitStruct->SPI_NSSel = DISABLE;
}

/**
	* @brief  Initializes the SPIx peripheral according to the specified 
	*         parameters in the SPI_InitStruct.
	* @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
	*  				As follow:
	*		@arg  SPIM_1, SPIM_2, SPIM_3, SPIM_4                    
	*   @arg  SPIS_1, SPIS_2, SPIS_3, SPIS_4 
	* @param  SPI_InitStruct: pointer to a SPI_InitTypeDef structure that
	*         contains the configuration information for the specified SPI peripheral.
	* @retval None
	*/
void SPI_Init(SPI_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
    volatile uint32_t tmpreg = 0, tmpreg1 = 0;
	
	tmpreg1 = SPIx->EN;
	
	SPIx->EN &= ~SPI_EN;
	
	tmpreg = SPIx->CTRL0;
	tmpreg &= ~(SPI_CTRL0_MODE);
	tmpreg |= (SPI_InitStruct->SPI_Mode << 8);
	tmpreg &= ~(SPI_CTRL0_SCPOL);
	tmpreg |= (SPI_InitStruct->SPI_CPOL << 7);
	tmpreg &= ~(SPI_CTRL0_SCPH);
	tmpreg |= (SPI_InitStruct->SPI_CPHA << 6);
	tmpreg &= ~(SPI_CTRL0_SPS);
	tmpreg |= (SPI_InitStruct->SPI_Protcl << 4);
	tmpreg &= ~(SPI_CTRL0_DFL);
	tmpreg |= SPI_InitStruct->SPI_DataSize;
	SPIx->CTRL0 = tmpreg;
	
	if ((SPI_PROTCL_TypeDef)(SPI_InitStruct->SPI_Mode) == SPI_Protcl_NationalSemiMW)
	{	
		tmpreg = SPIx->CTRL0;
		tmpreg &= ~(SPI_CTRL0_CFL);
		tmpreg |= (SPI_InitStruct->SPI_MWProtclComdSize << 12);
		SPIx->CTRL0 = tmpreg;
		
		tmpreg = SPIx->MW_CTRL;
		tmpreg &= ~(SPI_MW_CTRL_MWHS);
		tmpreg |= (SPI_InitStruct->SPI_MWProtclHandShake << 2);
		tmpreg &= ~(SPI_MW_CTRL_MWDIR);
		tmpreg |= (SPI_InitStruct->SPI_MWProtclDir << 1);
		tmpreg &= ~(SPI_MW_CTRL_MWMOD);
		tmpreg |= SPI_InitStruct->SPI_MWProtclMode;
		SPIx->MW_CTRL = tmpreg;
	}
	
	if ( (SPIx == SPIM_1) || (SPIx == SPIM_2) || (SPIx == SPIM_3) || (SPIx == SPIM_4) )
	{
		do 
		{
			SPIx->EN &= ~SPI_EN;
			
		} while (SPIx->EN & SPI_EN);
		
		SPIx->CTRL1 = (SPI_InitStruct->SPI_DataNum & 0x0000FFFF);
		
		SPIx->BAUD = SPI_InitStruct->SPI_BaudRatePrescaler;	
		
		SPIx->SSEL = SPI_InitStruct->SPI_NSSel;
	}
	
	SPIx->TXTHL = SPI_InitStruct->SPI_TxFIFOThreshValue;
	SPIx->RXTHL = SPI_InitStruct->SPI_RxFIFOThreshValue;

	SPIx->EN = tmpreg1;
}

/**
	* @brief  Enable or disable SPI module.
	* @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
	*  				As follow:
	*		@arg  SPIM_1, SPIM_2, SPIM_3, SPIM_4                    
	*   @arg  SPIS_1, SPIS_2, SPIS_3, SPIS_4
  */
void SPI_Cmd(SPI_TypeDef* SPIx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		do
		{
			SPIx->EN |= SPI_EN;
			
		} while ( (SPIx->EN & SPI_EN) != SPI_EN );
	}
	else
	{
		SPIx->EN &= ~SPI_EN;
	}
}

/**
	* @breif  Configurate SPI relevant interrupt flag.
	* @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
	*  				As follow:
	*		@arg  SPIM_1, SPIM_2, SPIM_3, SPIM_4
	*   @arg  SPIS_1, SPIS_2, SPIS_3, SPIS_4
	*
	* @param  SPI_ITFlag:
	*   @arg 	SPI_ITFlag_MMC
	*   @arg  SPI_ITFlag_RXF
	*   @arg 	SPI_ITFlag_RXOV
	*   @arg  SPI_ITFlag_RXUD
	*   @qrg 	SPI_ITFlag_TXOV
	*   @arg 	SPI_ITFlag_TXE
	*   @arg 	SPI_ITFlag_ALL
	*/
void SPI_ITConfig(SPI_TypeDef* SPIx, SPI_ITFlag_TypeDef SPI_ITFlag, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		SPIx->IM |= SPI_ITFlag;
	}
	else
	{
		SPIx->IM &= ~SPI_ITFlag;
	}
}

/**
	* @breif  Configurate specified parameterswork in DMA mode.
	* @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
	*  				As follow:
	*		@arg  SPIM_1, SPIM_2, SPIM_3, SPIM_4
	*   @arg  SPIS_1, SPIS_2, SPIS_3, SPIS_4
	*
	* @param  SPI_DMARxTrigLevel: Range@(0...7)
	*         when RxFIFO receive data >= SPI_DMARxTrigLevel + 1,
	*         will request DMA transmission.
	*
	* @param  SPI_DMATxTrigLevel: Range@(0...8)
	*         when RxFIFO receive data <= SPI_DMATxTrigLevel,
	*         will request DMA transmission.
	*
	* @param  SPI_DMARxTrigNewState, SPI_DMATxTrigNewState: ENABLE or DISABLE.
	*/
void SPI_DMAModeConfig( SPI_TypeDef* SPIx, \
												uint8_t SPI_DMARxTrigLevel, \
                        uint8_t SPI_DMATxTrigLevel, \
                        FunctionalState SPI_DMARxTrigNewState, \
												FunctionalState SPI_DMATxTrigNewState )
{
	if (SPI_DMARxTrigNewState != DISABLE)
	{
		SPIx->DMA_RXL = SPI_DMARxTrigLevel;
		SPIx->DMA_CTRL |= SPI_DMA_CTRL_RE;
	}
	else
	{
		SPIx->DMA_CTRL &= ~SPI_DMA_CTRL_RE;	
	}
	
	if (SPI_DMATxTrigNewState != DISABLE)
	{
		SPIx->DMA_TXL = SPI_DMATxTrigLevel;
		SPIx->DMA_CTRL |= SPI_DMA_CTRL_TE;
	}
	else
	{
		SPIx->DMA_CTRL &= ~SPI_DMA_CTRL_TE;
	}	
}

/**
	* @breif  Get status of SPI relevant flag.
	*
  * @param  SPI_FlagStatus
	*         As follow:
  * 	@arg  SPI_STS_TXERR
  * 	@arg  SPI_STS_RXF                             
  * 	@arg  SPI_STS_RXNE                         
  * 	@arg  SPI_STS_TXE                               
  * 	@arg  SPI_STS_TXNF                      
  * 	@arg  SPI_STS_BUSY
	*
	* @retval SET or RESET.
	*/
FlagStatus SPI_GetFlagStatus(SPI_TypeDef* SPIx, uint8_t SPI_FlagStatus)
{
	return (SPIx->STS & SPI_FlagStatus) == SPI_FlagStatus ? SET : RESET;
}

/**
	* @brief  Get status of SPI relevant raw interrupt according to specified parameters.
	* @param  SPI_RawITFlag
	*         As follow:
	*		@arg  SPI_RawITFlag_RXF
	*		@arg  SPI_RawITFlag_RXOV
	*		@arg  SPI_RawITFlag_RXUD
	*		@arg  SPI_RawITFlag_TXOV
	*		@arg  SPI_RawITFlag_TXE
	*
	* @retval SET or RESET.
	*/
ITStatus SPI_GetRawITStatus(SPI_TypeDef* SPIx, SPI_RawITFlag_TypeDef SPI_RawITFlag)
{
	return (SPIx->RIS & SPI_RawITFlag) == SPI_RawITFlag ? SET : RESET;
}

/**
	* @breif  Get status of SPI relevant interrupt flag.
	*
	* @param  SPI_ITFlag
	*         As follow:
	*   @arg 	SPI_ITFlag_MMC
	*   @arg  SPI_ITFlag_RXF
	*   @arg 	SPI_ITFlag_RXOV
	*   @arg  SPI_ITFlag_RXUD
	*   @qrg 	SPI_ITFlag_TXOV
	*   @arg 	SPI_ITFlag_TXE
	*
	* @retval SET or RESET.
	*/
ITStatus SPI_GetITStatus(SPI_TypeDef* SPIx, SPI_ITFlag_TypeDef SPI_ITFlag)
{
	return (SPIx->IS & SPI_ITFlag) == SPI_ITFlag ? SET : RESET;
}

/**
	* @breif  Clear status of SPI relevant interrupt flag.
	*
	* @param  SPI_ITFlag
	*         As follow:
	*   @arg 	SPI_ITFlag_MMC
	*   @arg 	SPI_ITFlag_RXOV
	*   @arg  SPI_ITFlag_RXUD
	*   @qrg 	SPI_ITFlag_TXOV
	*   @arg 	SPI_ITFlag_ALL
	*/
void SPI_ClearITFlag(SPI_TypeDef* SPIx, SPI_ClearITFlag_TypeDef SPI_ITFlag)
{
	switch (SPI_ITFlag)
	{
		case SPI_ClearITFlag_TXOV:
			SPIx->TXOV_ICR = SPIx->TXOV_ICR;
			break;
		case SPI_ClearITFlag_RXOV:
			SPIx->RXOV_ICR = SPIx->RXOV_ICR;			
			break;
		case SPI_ClearITFlag_RXUD:
			SPIx->RXUD_ICR = SPIx->RXUD_ICR;			
			break;
		case SPI_ClearITFlag_MMC:
			SPIx->MMC_ICR = SPIx->MMC_ICR;		
				break;
		default:
			SPIx->INT_CLR = SPIx->INT_CLR;			
			break;
	}
}

/**
	* @brief  Get number of SPI TXFIFO remain data.
	* @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
	*  				As follow:
	*		@arg  SPIM_1, SPIM_2, SPIM_3, SPIM_4                    
	*   @arg  SPIS_1, SPIS_2, SPIS_3, SPIS_4
	*/
uint8_t SPI_GetTxFIFOAvaDataCounter(SPI_TypeDef* SPIx)
{
	return SPIx->TXTL;
}

/**
	* @brief  Get number of SPI RXFIFO remain data.
	* @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
	*  				As follow:
	*		@arg  SPIM_1, SPIM_2, SPIM_3, SPIM_4                    
	*   @arg  SPIS_1, SPIS_2, SPIS_3, SPIS_4
	*/
uint8_t SPI_GetRxFIFOAvaDataCounter(SPI_TypeDef* SPIx)
{
	return SPIx->RXTL;
}

/**
	* @brief  SPI receive data.
	* @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
	*  				As follow:
	*		@arg  SPIM_1, SPIM_2, SPIM_3, SPIM_4                    
	*   @arg  SPIS_1, SPIS_2, SPIS_3, SPIS_4
	*/
uint16_t SPI_ReceiveData(SPI_TypeDef* SPIx)
{
	return SPIx->DATABUF;
}

/**
	* @brief  SPI send data.
	* @param  SPIx: where x can be 1, 2, 3 or 4 to select the SPI peripheral.
	*  				As follow:
	*		@arg  SPIM_1, SPIM_2, SPIM_3, SPIM_4                    
	*   @arg  SPIS_1, SPIS_2, SPIS_3, SPIS_4
	*/
void SPI_SendData(SPI_TypeDef* SPIx, uint16_t Data)
{
	SPIx->DATABUF = Data;
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
