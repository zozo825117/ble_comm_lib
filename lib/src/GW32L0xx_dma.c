/**
  ******************************************************************************
  * @file    GW32L0xx_dma.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides all the DMA firmware functions.
  *
 @verbatim
**/

#include "GW32L0xx_dma.h"

/**
  * @brief  Deinitializes the DMA registers to their default reset values.
  * @retval None
  */
void DMA_DeInit(void)
{
	do
	{
		/* Restore DMA peripheral register to the reset value */
		PERI_RST_CTRL0 |= RMU_PERI_RESET0_DMA;
		
	} while ( (PERI_RST_CTRL0 & RMU_PERI_RESET0_DMA) != RMU_PERI_RESET0_DMA );
	
	/* Switch to work in normal mode */
	PERI_RST_CTRL0 &= ~RMU_PERI_RESET0_DMA;
}

/**
	* @brief  Initializes the DMA according to the specified
	*         parameters in the DMA_InitStruct.
	* @param  DMA_ChannelSel: where can be 1 or 2 to select the DMA
						as follow: 
	*		@arg  DMA_ChannelSel_CH0
	*		@arg  DMA_ChannelSel_CH1
	* @param  DMA_InitStruct: pointer to a DMA_InitTypeDef structure that
	*         contains the configuration information for the specified DMA Channel.
	* @retval None
	*/
void DMA_Init(DMA_ChannelSel_TypeDef DMA_ChannelSel, DMA_InitTypeDef* DMA_InitStruct)
{
    volatile uint32_t tmpreg = 0;
	
	DMA_EN = DMA_DMAEN;
		
	while (DMA_CHxEN & (DMA_CHxEN_CH0EN << DMA_ChannelSel));
	
	DMA_ClearTc =    ( (0x1UL << 0) << DMA_ChannelSel );	
	DMA_ClearBlkTc = ( (0x1UL << 0) << DMA_ChannelSel );
	DMA_ClearSrcTc = ( (0x1UL << 0) << DMA_ChannelSel );
	DMA_ClearDstTc = ( (0x1UL << 0) << DMA_ChannelSel );
	DMA_ClearErr =   ( (0x1UL << 0) << DMA_ChannelSel );
	
	*( (volatile uint32_t *)(DMAC_BASEADDR + 0x58 * DMA_ChannelSel) ) = DMA_InitStruct->DMA_SrcAddr;
	*( (volatile uint32_t *)((DMAC_BASEADDR + 0x8) + 0x58 * DMA_ChannelSel) ) = DMA_InitStruct->DMA_DstAddr;
		
	tmpreg = *( (volatile uint32_t *)((DMAC_BASEADDR + 0x18) + 0x58 * DMA_ChannelSel) );		
	tmpreg &= ~DMA_CH0_CTRL0_TT;
	tmpreg |= (DMA_InitStruct->DMA_TransDir << 20);		
	switch (DMA_InitStruct->DMA_Mode)
	{
		case DMA_Mode_DstScatter:
			tmpreg |= DMA_CH0_CTRL0_DSTSCA_EN;
			break;
		case DMA_Mode_SrcGather:
			tmpreg |= DMA_CH0_CTRL0_SRCGAT_EN;
			break;
		default:
			tmpreg &= ~(DMA_CH0_CTRL0_DSTSCA_EN | DMA_CH0_CTRL0_SRCGAT_EN);
			break;			
	}		
	tmpreg &= ~(DMA_CH0_CTRL0_SRC_BLEN);
	tmpreg |= (DMA_InitStruct->DMA_SrcBurstLen << 14);
	tmpreg &= ~(DMA_CH0_CTRL0_DST_BLEN);
	tmpreg |= (DMA_InitStruct->DMA_DstBurstLen << 11);
	tmpreg &= ~(DMA_CH0_CTRL0_SADDR_INC);
	tmpreg |= (DMA_InitStruct->DMA_SrcAddrDir << 9);	
	tmpreg &= ~(DMA_CH0_CTRL0_DADDR_INC);
	tmpreg |= (DMA_InitStruct->DMA_DstAddrDir << 7);		
	tmpreg &= ~(DMA_CH0_CTRL0_STRAN_WD);
	tmpreg |= (DMA_InitStruct->DMA_SrcTransDataSize << 4);		
	tmpreg &= ~(DMA_CH0_CTRL0_DTRAN_WD);
	tmpreg |= (DMA_InitStruct->DMA_DstTransDataSize << 1);
	tmpreg &= ~(DMA_CH0_CTRL0_INTEN);
	tmpreg |= DMA_InitStruct->DMA_GlobalIntEn;
	*( (volatile uint32_t *)((DMAC_BASEADDR + 0x18)+ 0x58 * DMA_ChannelSel) ) = tmpreg;
		
	*( (volatile uint32_t *)((DMAC_BASEADDR + 0x1C) + 0x58 * DMA_ChannelSel) ) = (DMA_InitStruct->DMA_TransBlkSize & 0xFFFUL);
		
	tmpreg = *( (volatile uint32_t *)((DMAC_BASEADDR + 0x40) + 0x58 * DMA_ChannelSel) );
	tmpreg &= ~(DMA_CH0_CFG0_SHS_POL);
	tmpreg |= (DMA_InitStruct->DMA_SrcHandShakeLevelPol << 19);
	tmpreg &= ~(DMA_CH0_CFG0_DHS_POL);
	tmpreg |= (DMA_InitStruct->DMA_DstHandShakeLevelPol << 18);		
	tmpreg &= ~(DMA_CH0_CFG0_SHS_SEL);
	tmpreg |= (DMA_InitStruct->DMA_SrcHandShakeSel << 11);
	tmpreg &= ~(DMA_CH0_CFG0_DHS_SEL);
	tmpreg |= (DMA_InitStruct->DMA_DstHandShakeSel << 10);		
	tmpreg &= ~(DMA_CH0_CFG0_PRIOR);
	tmpreg |= (DMA_InitStruct->DMA_Priority << 5);
	*( (volatile uint32_t *)((DMAC_BASEADDR + 0x40) + 0x58 * DMA_ChannelSel) ) = tmpreg;
		
	tmpreg = *( (volatile uint32_t *)((DMAC_BASEADDR + 0x44) + 0x58 * DMA_ChannelSel) );
	tmpreg &= ~(DMA_CH0_CFG1_DPER_HS);
	tmpreg |= (DMA_InitStruct->DMA_DstPerHandShakeInput << 11);
	tmpreg &= ~(DMA_CH0_CFG1_SPER_HS);
	tmpreg |= (DMA_InitStruct->DMA_SrcPerHandShakeInput << 7);
	*( (volatile uint32_t *)((DMAC_BASEADDR + 0x44) + 0x58 * DMA_ChannelSel) ) = tmpreg;

	switch (DMA_InitStruct->DMA_TransDir)
	{
		case DMA_TransDir_M2P:
			*( (volatile uint32_t *)(HS_MUX_BASEADDR + 4 * DMA_InitStruct->DMA_DstPerHandShakeInput) ) = DMA_InitStruct->DMA_DstPerReq;
			break;
		case DMA_TransDir_P2M:
			*( (volatile uint32_t *)(HS_MUX_BASEADDR + 4 * DMA_InitStruct->DMA_SrcPerHandShakeInput) ) = DMA_InitStruct->DMA_SrcPerReq;
			break;
		case DMA_TransDir_P2P:
			*( (volatile uint32_t *)(HS_MUX_BASEADDR + 4 * DMA_InitStruct->DMA_DstPerHandShakeInput) ) = DMA_InitStruct->DMA_DstPerReq;
			*( (volatile uint32_t *)(HS_MUX_BASEADDR + 4 * DMA_InitStruct->DMA_SrcPerHandShakeInput) ) = DMA_InitStruct->DMA_SrcPerReq;
			break;
		default:
			break;
	}

	tmpreg = *( (volatile uint32_t *)((DMAC_BASEADDR + 0x48) + 0x58 * DMA_ChannelSel) );
	tmpreg &= ~(DMA_CH0_SRCGAT_SGAT_CNT);
	tmpreg |= (DMA_InitStruct->DMA_SrcAddrGatherDataCnt << 20);
	tmpreg &= ~(DMA_CH0_SRCGAT_SGAT_ITV);
	tmpreg |= DMA_InitStruct->DMA_SrcAddrGatherIntervalCnt;
	*( (volatile uint32_t *)((DMAC_BASEADDR + 0x48) + 0x58 * DMA_ChannelSel) ) = tmpreg;
		
	tmpreg = *( (volatile uint32_t *)((DMAC_BASEADDR + 0x50) + 0x58 * DMA_ChannelSel) );
	tmpreg &= ~(DMA_CH0_DSTSCA_DSCA_CNT);
	tmpreg |= (DMA_InitStruct->DMA_DstAddrScatterDataCnt << 20);
	tmpreg &= ~(DMA_CH0_DSTSCA_DSCA_ITV);
	tmpreg |= DMA_InitStruct->DMA_DstAddrScatterIntervalCnt;
	*( (volatile uint32_t *)((DMAC_BASEADDR + 0x50) + 0x58 * DMA_ChannelSel) ) = tmpreg;
}

/**
	* @brief  Fills each DMA_InitStruct member with its default value.
	* @param  DMA_InitStruct : pointer to a DMA_InitTypeDef structure which will
	*         be initialized.
	* @retval None
	*/
void DMA_StructInit(DMA_InitTypeDef* DMA_InitStruct)
{
	DMA_InitStruct->DMA_SrcAddr = 0x00;
	DMA_InitStruct->DMA_DstAddr = 0x00;
	
	DMA_InitStruct->DMA_TransDir = DMA_TransDir_P2P;
	
	DMA_InitStruct->DMA_Mode = DMA_Mode_Normal;
	
	DMA_InitStruct->DMA_SrcBurstLen = DMA_BurstLen_4;
	DMA_InitStruct->DMA_DstBurstLen = DMA_BurstLen_4;
	
	DMA_InitStruct->DMA_SrcAddrDir = DMA_AddrDir_Inc;
	DMA_InitStruct->DMA_DstAddrDir = DMA_AddrDir_Inc;
	
	DMA_InitStruct->DMA_SrcTransDataSize = DMA_TransDataSize_8Bits;
	DMA_InitStruct->DMA_DstTransDataSize = DMA_TransDataSize_8Bits;
	
	DMA_InitStruct->DMA_TransBlkSize = 0x2;
	
	DMA_InitStruct->DMA_SrcHandShakeLevelPol = DMA_HandShakeLevelPol_High;
	DMA_InitStruct->DMA_DstHandShakeLevelPol = DMA_HandShakeLevelPol_High;
	
	DMA_InitStruct->DMA_SrcHandShakeSel = DMA_HandShakeSel_SoftWare;
	DMA_InitStruct->DMA_DstHandShakeSel = DMA_HandShakeSel_SoftWare;
	
	DMA_InitStruct->DMA_Priority = DMA_Priority_Low;
	
	DMA_InitStruct->DMA_DstPerReq = 0x0;
	DMA_InitStruct->DMA_SrcPerReq = 0x0;
	
	DMA_InitStruct->DMA_DstPerHandShakeInput = DMA_PerHandShakeInput_HS0;
	DMA_InitStruct->DMA_SrcPerHandShakeInput = DMA_PerHandShakeInput_HS0;
	
	DMA_InitStruct->DMA_SrcAddrGatherDataCnt = 0x0;
	DMA_InitStruct->DMA_SrcAddrGatherIntervalCnt = 0x0;
	
	DMA_InitStruct->DMA_DstAddrScatterDataCnt = 0x0;
	DMA_InitStruct->DMA_DstAddrScatterIntervalCnt = 0x0;
	
	DMA_InitStruct->DMA_GlobalIntEn = ENABLE;
}

/**
	* @breif  Enable or disable DMA module.
	* @param  DMA_ChannelSel: where can be 1 or 2 to select the DMA, as follow: 
	*		@arg  DMA_ChannelSel_CH0
	*		@arg  DMA_ChannelSel_CH1
	* @param  NewState as follow
      @arg  ENABLE or DISABLE.
	*/
void DMA_Cmd(DMA_ChannelSel_TypeDef DMA_ChannelSel, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		DMA_CHxEN = ( (DMA_CHxEN_CH0EN_WE | DMA_CHxEN_CH0EN) << DMA_ChannelSel ); 
	}
	else
	{
		DMA_CHxEN = ( (DMA_CHxEN_CH0EN_WE | 0x0UL) << DMA_ChannelSel );
	}
}

/** 
	* @brief  Configurate enabled interrupt according to specified DMA interrupt flag.
	* @param  DMA_ChannelSel: where can be 1 or 2 to select the DMA, as follow: 
	*		@arg  DMA_ChannelSel_CH0
	*		@arg  DMA_ChannelSel_CH1 
	*
	* @param  DMA_ITFlag:
	* 	@arg  DMA_ITFlag_Tc
	* 	@arg  DMA_ITFlag_BlkTc
	*		@arg  DMA_ITFlag_SrcTc
	*		@arg  DMA_ITFlag_DstTc
	*   @arg  DMA_ITFlag_Err
	*/
void DMA_ITConfig(DMA_ChannelSel_TypeDef DMA_ChannelSel, DMA_ITFlag_TypeDef DMA_ITFlag, FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		*(volatile uint32_t *)( (DMAC_BASEADDR + 0x310) + 8 * DMA_ITFlag ) = \
			                    ( (DMA_MASKTC_CH0MTC_WE | DMA_MASKTC_CH0MASKTC) << DMA_ChannelSel );
	}
	else
	{
		*(volatile uint32_t *)( (DMAC_BASEADDR + 0x310) + 8 * DMA_ITFlag ) = \
			                    ( (DMA_MASKTC_CH0MTC_WE << DMA_ChannelSel | 0x0UL) << DMA_ChannelSel );	
	}
}

/**
	* @brief  Get raw interrupt flag of DMA.
	* @param  DMA_ChannelSel: where can be 1 or 2 to select the DMA, as follow: 
	*		@arg  DMA_ChannelSel_CH0
	*		@arg  DMA_ChannelSel_CH1 
	*
	* @param  DMA_ITFlag:
	* 	@arg  DMA_ITFlag_Tc
	* 	@arg  DMA_ITFlag_BlkTc
	*		@arg  DMA_ITFlag_SrcTc
	*		@arg  DMA_ITFlag_DstTc
	*   @arg  DMA_ITFlag_Err
	*/
ITStatus DMA_GetRawITStatus(DMA_ChannelSel_TypeDef DMA_ChannelSel, DMA_ITFlag_TypeDef DMA_ITFlag)
{
	return ( *(volatile uint32_t *)((DMAC_BASEADDR + 0x2C0) + 8 * DMA_ITFlag) & (DMA_RAWTC_INTS_CH0 << DMA_ChannelSel) ) == \
		(DMA_RAWTC_INTS_CH0 << DMA_ChannelSel) ? SET : RESET;
}  

/**
	* @brief  Get interrupt flag of DMA.
	* @param  DMA_ChannelSel: where can be 1 or 2 to select the DMA, as follow: 
	*		@arg  DMA_ChannelSel_CH0
	*		@arg  DMA_ChannelSel_CH1 
	*
	* @param  DMA_ITFlag:
	* 	@arg  DMA_ITFlag_Tc
	* 	@arg  DMA_ITFlag_BlkTc
	*		@arg  DMA_ITFlag_SrcTc
	*		@arg  DMA_ITFlag_DstTc
	*   @arg  DMA_ITFlag_Err
	*/
ITStatus DMA_GetITStatus(DMA_ChannelSel_TypeDef DMA_ChannelSel, DMA_ITFlag_TypeDef DMA_ITFlag)
{
	return ( *(volatile uint32_t *)((DMAC_BASEADDR + 0x2E8) + 8 * DMA_ITFlag) & (DMA_TC_INTS_CH0 << DMA_ChannelSel) ) == \
		                                                                          (DMA_TC_INTS_CH0 << DMA_ChannelSel) ? SET : RESET;
}

/**
	* @brief  Get all channels 'OR' interrupt flag of DMA.
	* @param  DMA_ITFlag:
	* 	@arg  DMA_ITFlag_Tc
	* 	@arg  DMA_ITFlag_BlkTc
	*		@arg  DMA_ITFlag_SrcTc
	*		@arg  DMA_ITFlag_DstTc
	*   @arg  DMA_ITFlag_Err
	*/
ITStatus DMA_GetCombineITStatus(DMA_ITFlag_TypeDef DMA_ITFlag)
{
	return ( DMA_CombIntr & (0x1UL << DMA_ITFlag) ) == (0x1UL << DMA_ITFlag) ? SET : RESET;
}

/**
	* @brief  Clear interrupt flag of DMA.
	* @param  DMA_ChannelSel: where can be 1 or 2 to select the DMA, as follow: 
	*		@arg  DMA_ChannelSel_CH0
	*		@arg  DMA_ChannelSel_CH1 
	*
	* @param  DMA_ITFlag:
	* 	@arg  DMA_ITFlag_Tc
	* 	@arg  DMA_ITFlag_BlkTc
	*		@arg  DMA_ITFlag_SrcTc
	*		@arg  DMA_ITFlag_DstTc
	*   @arg  DMA_ITFlag_Err
	*/
void DMA_ClearITFlag(DMA_ChannelSel_TypeDef DMA_ChannelSel, DMA_ITFlag_TypeDef DMA_ITFlag)
{
	*(volatile uint32_t *)((DMAC_BASEADDR + 0x338) + 8 * DMA_ITFlag) = ( (0x1UL << 0) << DMA_ChannelSel );
}

/**
	* @brief  Get completed flag of DMA.
	* @param  DMA_ChannelSel: where can be 1 or 2 to select the DMA, as follow: 
	*		@arg  DMA_ChannelSel_CH0
	*		@arg  DMA_ChannelSel_CH1
	*/
FlagStatus DMA_GetCompletedFlagStatus(DMA_ChannelSel_TypeDef DMA_ChannelSel)
{
	return (DMA_CHxEN & (DMA_CHxEN_CH0EN << DMA_ChannelSel)) == (DMA_CHxEN_CH0EN << DMA_ChannelSel) ? RESET : SET;
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
