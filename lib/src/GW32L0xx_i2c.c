/**
  ******************************************************************************
  * @file    GW32L0xx_i2c.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides all the I2C firmware functions.
  *
 @verbatim
**/

#include "GW32L0xx_i2c.h"

/**
	* @brief  Deinitializes the I2Cx peripheral registers to their default reset values.
	* @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
	* @retval None
	*/
void I2C_DeInit(I2C_TypeDef* I2Cx)
{
	/* Select which one module to reset */
	uint32_t I2C_PERI_RESET = (I2Cx != I2C_2) ? RMU_PERI_RESET0_I2C1 : RMU_PERI_RESET0_I2C2;
	do
	{
		/* Restore I2C peripheral register to the reset value */
		PERI_RST_CTRL0 |= I2C_PERI_RESET;
		
	} while ( (PERI_RST_CTRL0 & I2C_PERI_RESET) != I2C_PERI_RESET );
	
	/* Switch to work in normal mode */
	PERI_RST_CTRL0 &= ~I2C_PERI_RESET;
}

/**
	* @brief  Fills each I2C_InitStruct member with its default value.
	* @param  I2C_InitStruct: pointer to an I2C_InitTypeDef structure which will be initialized.
	* @retval None
	*/
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
{
	/* Fills each I2C_InitStruct member with its default value */
	I2C_InitStruct->I2C_Mode = I2C_Mode_Master;
	
	I2C_InitStruct->I2C_AddrType = I2C_AddrType_10Bits;
	I2C_InitStruct->I2C_MstAccessAddr = 0x55;
	I2C_InitStruct->I2C_SlvAddr = 0x55;
	
	I2C_InitStruct->I2C_SCLHighLevel = 0x28;
	I2C_InitStruct->I2C_SCLLowLevel = 0x2F;
	
	I2C_InitStruct->I2C_SDASetUpTime = 0x64;
	I2C_InitStruct->I2C_SDARxHoldTime = 0x1;
	I2C_InitStruct->I2C_SDATxHoldTime = 0x1;
	
	I2C_InitStruct->I2C_SpikeTime = 0x1;
	
	I2C_InitStruct->I2C_RxFIFOThreshValue = 0x0;
	I2C_InitStruct->I2C_TxFIFOThreshValue = 0x0;
}

/**
  * @brief  Initializes the I2Cx peripheral according to the specified 
  *         parameters in the I2C_InitStruct.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @param  I2C_InitStruct: pointer to a I2C_InitTypeDef structure that
  *         contains the configuration information for the specified I2C peripheral.
  * @retval None
  */
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{
	volatile uint16_t tmpreg = 0;
	
	/* Disable I2C module */
	I2Cx->EN &= ~I2C_EN;
	
	/* Store value of CTRL register */
	tmpreg = I2Cx->CTRL;
	
	if (I2C_InitStruct->I2C_Mode != I2C_Mode_Slave)
	{ 
		/* Master	setting */
		I2Cx->SCLH_SS = I2C_InitStruct->I2C_SCLHighLevel < 0x6 ? 0x6 : I2C_InitStruct->I2C_SCLHighLevel & I2C_SCLH_SS;
		I2Cx->SCLL_SS = I2C_InitStruct->I2C_SCLLowLevel  < 0x8 ? 0x8 : I2C_InitStruct->I2C_SCLLowLevel  & I2C_SCLL_SS;
		/* As master, set spike time */
		I2Cx->SPKF = I2C_InitStruct->I2C_SpikeTime & I2C_SPKF;		
		
		/* Disable Slave function */
		tmpreg |= I2C_CTRL_SLV_DE;
		
		/* Enable master insert restart condiction */
		tmpreg |= I2C_CTRL_RESTART_EN;
	
		if (I2C_InitStruct->I2C_AddrType != I2C_AddrType_10Bits)
		{ 
			/* Set master address type as 7bits Addrs */
			tmpreg &= ~I2C_CTRL_MSTADDR_SEL;
			
			/* Set access address of master */
			I2Cx->TARADDR = I2C_InitStruct->I2C_MstAccessAddr & I2C_TARADDR_7BITS;
		}
		else
		{
			/* Set master address type as 10bits Addrs */
			tmpreg |= I2C_CTRL_MSTADDR_SEL;
			
			/* Set access address of master */
			I2Cx->TARADDR = I2C_InitStruct->I2C_MstAccessAddr & I2C_TARADDR_10BITS;			
		}
		
		/* Set I2C speed(<= 400kbps) */
		tmpreg &= ~I2C_CTRL_SPEED;
		tmpreg |= (0x1UL << 1);		
		
		/* Enable master */
		tmpreg |= I2C_CTRL_MST_EN;
	}
	else
	{ 
		/* Slave setting */

		/* As slave and sending data, SDA setup time */
		I2Cx->SDASETUP = I2C_InitStruct->I2C_SDASetUpTime < 0x2 ? 0x2 : I2C_InitStruct->I2C_SDASetUpTime & I2C_SDASETUP;
		
		/* Enable slave function */
		tmpreg &= ~I2C_CTRL_SLV_DE;

		if (I2C_InitStruct->I2C_AddrType != I2C_AddrType_10Bits)
		{ 
			/* Set slave address type as 7bits Addrs */
			tmpreg &= ~I2C_CTRL_SLVADDR_SEL;
			
			/* Set address of slave */
			I2Cx->SARADDR = I2C_InitStruct->I2C_SlvAddr & I2C_SARADDR_7BITS;			
		}
		else
		{ 
			/* Set slave address type as 10bits Addrs */
			tmpreg |= I2C_CTRL_SLVADDR_SEL;

			/* Set address of slave */
			I2Cx->SARADDR = I2C_InitStruct->I2C_SlvAddr & I2C_SARADDR_10BITS;				
		}
		
		/* Set I2C speed(<= 400kbps) */
		tmpreg &= ~I2C_CTRL_SPEED;
		tmpreg |= (0x1UL << 1);
		
		/* Disable master */
		tmpreg &= ~I2C_CTRL_MST_EN;	
	}
	
	/* Refresh value of CTRL register */
	I2Cx->CTRL = tmpreg;
	
	/* Set SDA hold time */
	I2Cx->SDAHOLD = ( (I2C_InitStruct->I2C_SDARxHoldTime << 16) | \
	                  (I2C_InitStruct->I2C_SDATxHoldTime << 0) );
	
	/* Set threshod value of FIFO */
	I2Cx->RXTH = I2C_InitStruct->I2C_RxFIFOThreshValue & I2C_RXTH;
	I2Cx->TXTH = I2C_InitStruct->I2C_TxFIFOThreshValue & I2C_TXTH;		
}

/**
	* @brief  Enable or disable I2C module.
	*/
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		do
		{
			I2Cx->EN |= I2C_EN;
			
		} while ( (I2Cx->EN & I2C_EN) != I2C_EN );
	}
	else
	{
		I2Cx->EN &= ~I2C_EN;
	}
}

/**
	* @brief  Marsk interrupt function according to specified paramters.
	* @param  I2C_ITMask as follow:
	* 	@arg  I2C_IMR_ALL
	* 	@arg  I2C_IMR_MMHBUS                       
	* 	@arg  I2C_IMR_MRSDET                           
	* 	@arg  I2C_IMR_MGC                             
	* 	@arg  I2C_IMR_MSDET                           
	* 	@arg  I2C_IMR_MSPDET                          
	* 	@arg  I2C_IMR_MACT                           
	* 	@arg  I2C_IMR_MRXD                           
	* 	@arg  I2C_IMR_MTXA                             
	* 	@arg  I2C_IMR_MRDR                             
	* 	@arg  I2C_IMR_MTXE                            
	* 	@arg  I2C_IMR_MTXO                             
	* 	@arg  I2C_IMR_MRXF                             
	* 	@arg  I2C_IMR_MRXO                             
	* 	@arg  I2C_IMR_MRXU                             
	*/
void I2C_ITConfig(I2C_TypeDef* I2Cx, uint16_t I2C_ITMask, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		I2Cx->IMR |= I2C_ITMask;
	}
	else
	{
		I2Cx->IMR &= ~I2C_ITMask;	
	}
}

/**
	* @brief  Configurate I2C properity work in DMA mode.
	* @param  I2C_DMARxTrigLevel: range(0..7)
	* @param  I2C_DMATxTrigLevel: range(0..7)
	*/
void I2C_DMAModeConfig( I2C_TypeDef* I2Cx, \
												uint8_t I2C_DMARxTrigThreshLevel, \
                        uint8_t I2C_DMATxTrigThreshLevel, \
                        FunctionalState I2C_DMARxTrigNewState, \
												FunctionalState I2C_DMATxTrigNewState )
{
	/* Set DMA RX trigge condition */
	if (I2C_DMARxTrigNewState != DISABLE)
	{
		/* Set threshod value of DMA RX */
		I2Cx->DMARL = I2C_DMARxTrigThreshLevel;	

		/* Enable trigge of DMA RX */
		I2Cx->DMAC |= I2C_DMAC_RE;
	}
	else
	{
		/* Disable trigge of DMA RX */	
		I2Cx->DMAC &= ~I2C_DMAC_RE;	
	}
	
	/* Set DMA TX trigge condition */
	if (I2C_DMATxTrigNewState != DISABLE)
	{
		/* Set threshod value of DMA TX */
		I2Cx->DMATL = I2C_DMATxTrigThreshLevel;
		
		/* Enable trigge of DMA TX */		
		I2Cx->DMAC |= I2C_DMAC_TE;	
	}
	else
	{
		/* Disable trigge of DMA TX */		
		I2Cx->DMAC &= ~I2C_DMAC_TE;	
	}	
}

/**
	* @brief  Enable or disable I2C abort function.
	*/
void I2C_AbrtConfig(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		I2Cx->EN |= I2C_EN_ABRT;
	}
	else
	{
		I2Cx->EN &= ~I2C_EN_ABRT;		
	}
}

/**
	* @brief  Get relevant flag status of I2C.
	* @param  I2C_Status: as follow
	* 	@arg  I2C_STS_SLV_ACT    
	*		@arg  I2C_STS_MST_ACT                
	*		@arg  I2C_STS_RXF                         
	*		@arg  I2C_STS_RXNE                          
	*		@arg  I2C_STS_TXE                         
	*		@arg  I2C_STS_TXNF                           
	*		@arg  I2C_STS_ACT 
	*/
FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, uint8_t I2C_Status)
{
	return ( (I2Cx->STS & I2C_Status) == I2C_Status ? SET : RESET );
}

/**
	* @brief  Get relevant enabled flag status of I2C.
	* @param  I2C_EnabledStatus: as follow
	* 	@arg  I2C_ENSTS_SLVRX_LOST          
  * 	@arg  I2C_ENSTS_SLVDIS_BUSY                  
  * 	@arg  I2C_ENSTS_EN 
	*/
FlagStatus I2C_GetEnabledFlagStatus(I2C_TypeDef* I2Cx, uint8_t I2C_EnabledStatus)
{
	return ( (I2Cx->ENSTS & I2C_EnabledStatus) == I2C_EnabledStatus ? SET : RESET );
}

/**
	* @brief  Get relevant raw interrupt status of I2C.
	* @param  I2C_ITStatus: as follow
	* 	@arg  I2C_RISR_MHBUS                       
	* 	@arg  I2C_RISR_RSDET                           
	* 	@arg  I2C_RISR_GC                             
	* 	@arg  I2C_RISR_SDET                           
	* 	@arg  I2C_RISR_SPDET                          
	* 	@arg  I2C_RISR_ACT                           
	* 	@arg  I2C_RISR_RXD                           
	* 	@arg  I2C_RISR_TXA                             
	* 	@arg  I2C_RISR_RDR                             
	* 	@arg  I2C_RISR_TXE                            
	* 	@arg  I2C_RISR_TXO                             
	* 	@arg  I2C_RISR_RXF                             
	* 	@arg  I2C_RISR_RXO                             
	* 	@arg  I2C_RISR_RXU                             
	*/
ITStatus I2C_GetRawITStatus(I2C_TypeDef* I2Cx, uint16_t I2C_ITStatus)
{
	return ( (I2Cx->RISR & I2C_ITStatus) == I2C_ITStatus ? SET : RESET );
}

/**
	* @brief  Get relevant interrupt status of I2C.
	* @param  I2C_ITStatus: as follow
	*		@arg  I2C_ISR_MHBUS                       
	* 	@arg  I2C_ISR_RSDET                           
	* 	@arg  I2C_ISR_GC                             
	* 	@arg  I2C_ISR_SDET                           
	* 	@arg  I2C_ISR_SPDET                          
	* 	@arg  I2C_ISR_ACT                           
	* 	@arg  I2C_ISR_RXD                           
	* 	@arg  I2C_ISR_TXA                             
	* 	@arg  I2C_ISR_RDR                             
	* 	@arg  I2C_ISR_TXE                            
	* 	@arg  I2C_ISR_TXO                             
	* 	@arg  I2C_ISR_RXF                             
	* 	@arg  I2C_ISR_RXO                             
	* 	@arg  I2C_ISR_RXU                             
	*/
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx, uint16_t I2C_ITStatus)
{
	return ( (I2Cx->ISR & I2C_ITStatus) == I2C_ITStatus ? SET : RESET );
}

/**
	* @brief  Clear relevant interrupt flag of I2C.
	* @param  I2C_ITFlag, as follow
	*	 	@arg	I2C_ClearITFlag_ALL
	* 	@arg	I2C_ClearITFlag_RXU
	* 	@arg	I2C_ClearITFlag_RXO
	* 	@arg	I2C_ClearITFlag_TXO
	* 	@arg	I2C_ClearITFlag_RDR
	* 	@arg	I2C_ClearITFlag_TXA
	* 	@arg	I2C_ClearITFlag_RXD
	* 	@arg	I2C_ClearITFlag_ACT
	* 	@arg	I2C_ClearITFlag_SPDET
	* 	@arg	I2C_ClearITFlag_SDET
	* 	@arg	I2C_ClearITFlag_GC	
	* 	@arg	I2C_ClearITFlag_RSDET 
	*/
void I2C_ClearITFlag(I2C_TypeDef* I2Cx, I2C_ClearITFlag_TypeDef I2C_ITFlag)
{	
	if (I2C_ITFlag != I2C_ClearITFlag_RSDET)
	{
		if (I2Cx != I2C_2)
		{
			*(volatile uint32_t *)( (I2C_1_BASEADDR + 0x40) + 4 * I2C_ITFlag ) = \
													 *(volatile uint32_t *)( (I2C_1_BASEADDR + 0x40) + 4 * I2C_ITFlag );
		}
		else
		{
			*(volatile uint32_t *)( (I2C_2_BASEADDR + 0x40) + 4 * I2C_ITFlag ) = \
													 *(volatile uint32_t *)( (I2C_2_BASEADDR + 0x40) + 4 * I2C_ITFlag );	
		}		
	}
	else
	{
		I2Cx->RSDET_CLR = I2Cx->RSDET_CLR;
	}
}

/**
	* @brief  I2C send data.
	*/
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data)
{
  I2Cx->DC = Data;
}

/**
	* @brief  After I2C send data, master will make stop condition.
	*/
void I2C_SendDataWithStop(I2C_TypeDef* I2Cx, uint8_t Data)
{
  I2Cx->DC = (Data | I2C_DC_Stop);
}

/**
	* @brief  Before I2C read data, master will make restart condition and control byte with read bit.
	*/
void I2C_SendDataWithRestartRead(I2C_TypeDef* I2Cx)
{
  I2Cx->DC = (I2C_DC_Restart | I2C_DC_Read);
}

/**
	* @brief  Before I2C read data, master will make restart condition and control byte with read bit,
  *         and after read data, master will make stop condition.
	*/
void I2C_SendDataWithRestartReadStop(I2C_TypeDef* I2Cx)
{
  I2Cx->DC = (I2C_DC_Restart | I2C_DC_Read | I2C_DC_Stop);
}

/**
	* @brief  After I2C read data, master will make stop condition.
	*/
void I2C_SendDataWithReadStop(I2C_TypeDef* I2Cx)
{
  I2Cx->DC = (I2C_DC_Read | I2C_DC_Stop);
}

/**
	* @brief  I2C read data.
	*/
void I2C_SendDataWithRead(I2C_TypeDef* I2Cx)
{
  I2Cx->DC = I2C_DC_Read;
}

/**
	* @brief  I2C receive data.
	*/
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx)
{
  return ((uint8_t)I2Cx->DC);
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
