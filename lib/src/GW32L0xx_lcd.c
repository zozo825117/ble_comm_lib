/**
  ******************************************************************************
  * @file    GW32L0xx_lcd.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_lcd.h"

/**
	* @brief  Deinitialize LCD module to the reset value.
	*/
void LCD_DeInit(void)
{
	do
	{
		/* Restore LCD peripheral register to the reset value */
		PERI_RST_CTRL1 |= RMU_PERI_RESET1_LCD;
		
	} while ( (PERI_RST_CTRL1 & RMU_PERI_RESET1_LCD) != RMU_PERI_RESET1_LCD );
	
	/* Switch to work in normal mode */
	PERI_RST_CTRL1 &= ~RMU_PERI_RESET1_LCD;
}

/**
  * @brief  Fills each LCD_InitStruct member with its default value.
	*/
void LCD_StructInit(LCD_InitTypeDef* LCD_InitStruct)
{
	/* Set default value of LCD module register */
	
	LCD_InitStruct->LCD_Mode = LCD_Mode_StaticsDisplay;
	LCD_InitStruct->LCD_Bias = LCD_Bias_1_3;
	
	LCD_InitStruct->LCD_IRH = LCD_IRH_Disable;
	LCD_InitStruct->LCD_IRL = LCD_IRL_Disable;
	LCD_InitStruct->LCD_ChargePump = LCD_ChargePump_Disable;
	LCD_InitStruct->LCD_ChargePumpClk = LCD_ChargePumpClk_2KHz;
	
	LCD_InitStruct->LCD_FrameRefreshRate = LCD_FrameRefreshRate_64;
	
	LCD_InitStruct->LCD_Blinky = LCD_Blinky_Disable;
	
	LCD_InitStruct->LCD_ITInterval = LCD_ITInterval_1Frame;
}

/**
  * @brief  Initializes the LCD peripheral according to the specified
  *         parameters in the LCD_InitStruct.
	*/
void LCD_Init(LCD_InitTypeDef* LCD_InitStruct)
{
	/* Restore value of LCDCR register */
	volatile uint32_t tmpreg = LCD->LCDCR;
	
	/* Close off power of LCD before configurating module */
	LCD->LCDCR &= ~LCD_CTRL_LCDEN;
	
	/* Configurate LCD work mode */
	tmpreg &= ~LCD_CTRL_MODE;
	tmpreg |= (LCD_InitStruct->LCD_Mode << 6);
	
	/* Set bias voltage */
	tmpreg &= ~LCD_CTRL_BIAS;
	tmpreg |= (LCD_InitStruct->LCD_Bias << 5);
	
	/* Ebable or disable internal large divider resistance */
	tmpreg &= ~LCD_CTRL_IRH;
	tmpreg |= (LCD_InitStruct->LCD_IRH << 11);
	
	/* Ebable or disable internal small divider resistance */	
	tmpreg &= ~LCD_CTRL_IRL;
	tmpreg |= (LCD_InitStruct->LCD_IRL << 10);
	
	/* Enable or disable charge pump */
	tmpreg &= ~LCD_CTRL_CPEN;
	tmpreg |= (LCD_InitStruct->LCD_ChargePump << 9);
	
	/* Select clock for charge pump */
	tmpreg &= ~LCD_CTRL_CPCLKSEL;
	tmpreg |= (LCD_InitStruct->LCD_ChargePumpClk << 3);
	
	/* Set frequence of LCD frame refresh */
	tmpreg &= ~LCD_CTRL_FRM;
	tmpreg |= (LCD_InitStruct->LCD_FrameRefreshRate << 1);
	
	/* Enable or disable LCD display blank */
	tmpreg &= ~LCD_CTRL_BLK;
	tmpreg |= (LCD_InitStruct->LCD_Blinky << 12);
	
	/* Set condition of LCD interrupt */
	tmpreg &= ~LCD_CTRL_FC;
	tmpreg |= (LCD_InitStruct->LCD_ITInterval << 14);
	
	/* Refresh value of LCDCR register */
	LCD->LCDCR = tmpreg;
}

/**
	* @brief  Enable or disable LCD module.
	*/
void LCD_Cmd(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		do 
		{
			LCD->LCDCR |= LCD_CTRL_LCDEN;
			
		} while ((LCD->LCDCR & LCD_CTRL_LCDEN) != LCD_CTRL_LCDEN);
	}
	else
	{
		LCD->LCDCR &= ~LCD_CTRL_LCDEN;		
	}
}

/**
	* @brief  Configurate enabled or disabled interrupt state.
	*/
void LCD_ITConfig(FunctionalState NewState)
{
	if (NewState != DISABLE)
	{
		LCD->LCDCR |= LCD_CTRL_INTEN;
	}
	else
	{
		LCD->LCDCR &= ~LCD_CTRL_INTEN;
	}
}

/**
	* @brief  Get flag Status of LCD interrupt.
	*/
ITStatus LCD_GetITStatus(void)
{
	return (LCD->LCDCR & LCD_CTRL_LCDINT) != LCD_CTRL_LCDINT ? SET : RESET;
}

/**
	* @brief  Clear flag of LCD interrupt.
	*/
void LCD_ClearITFlag(void)
{
	LCD->LCDCR &= ~LCD_CTRL_LCDINT;
}

/**
	* @brief  Clear RAML register of LCD.
	* @param  LCD_RAML, as follow
	* 	@arg	LCD_RAML_0
	* 	@arg	LCD_RAML_1
	* 	@arg	LCD_RAML_2
	* 	@arg	LCD_RAML_3
	* 	@arg	LCD_RAML_4
	* 	@arg	LCD_RAML_5
	* 	@arg	LCD_RAML_6
	* 	@arg	LCD_RAML_7
	*/
void LCD_RAMLInit(LCD_RAML_TypeDef LCD_RAML)
{
	/* Clear RAML register */
	*( (volatile uint32_t *)(LCD_BASEADDR + 4 * LCD_RAML) ) = 0x0;
}

/**
	* @brief  Clear RAMH register of LCD.
	* @param  LCD_RAMH, as follow
	* 	@arg	LCD_RAMH_0
	* 	@arg	LCD_RAMH_1
	* 	@arg	LCD_RAMH_2
	* 	@arg	LCD_RAMH_3
	* 	@arg	LCD_RAMH_4
	* 	@arg	LCD_RAMH_5
	* 	@arg	LCD_RAMH_6
	* 	@arg	LCD_RAMH_7
	*/
void LCD_RAMHInit(LCD_RAMH_TypeDef LCD_RAMH)
{	
	/* Clear RAMH register */
	*( (volatile uint32_t *)(LCD_BASEADDR + 0x20 + 4 * LCD_RAMH) ) = 0x0;
}

/**
	* @brief  Fill RAML or RAMH register of LCD with specified parameters.
	* @param  LCD_COM, as follow
	* 	@arg	LCD_COM_0
	* 	@arg	LCD_COM_1
	* 	@arg	LCD_COM_2
	* 	@arg	LCD_COM_3
	* 	@arg	LCD_COM_4
	* 	@arg	LCD_COM_5
	* 	@arg	LCD_COM_6
	* 	@arg	LCD_COM_7
	* @brief  LCD_SEG, range(0...55).
	*/
void LCD_SetRAMData(LCD_COM_TypeDef LCD_COM, uint8_t LCD_SEG, uint32_t LCD_RAM_Data)
{
	/* LCD Select RAML as data area */
	if (LCD_SEG <= 31)
	{		
		*( (volatile uint32_t *)(LCD_BASEADDR + 4 * LCD_COM) ) |= LCD_RAM_Data << LCD_SEG;	
	}
	else
	{
		/* LCD Select RAMH as data area */
		if ( (LCD_SEG >= 32) && (LCD_SEG < 56) )
		{
			LCD_SEG -= 32;
			
			if ( (LCD_COM == LCD_COM_6) || (LCD_COM == LCD_COM_7) )
			{
				/* Select RAMH6 or RAMH7 */
				*( (volatile uint32_t *)(LCD_BASEADDR + 0x20 + 4 * LCD_COM) ) |= (LCD_RAM_Data << LCD_SEG) & LCD_RAM_6_7H;
			}
			else if ( (LCD_COM == LCD_COM_4) || (LCD_COM == LCD_COM_5) )
			{
				/* Select RAMH4 or RAMH5 */
				*( (volatile uint32_t *)(LCD_BASEADDR + 0x20 + 4 * LCD_COM) ) |= (LCD_RAM_Data << LCD_SEG) & LCD_RAM_4_5H;
			}
			else
			{
				/* Select RAMH0, RAMH1, RAMH2 or RAMH3 */
				*( (volatile uint32_t *)(LCD_BASEADDR + 0x20 + 4 * LCD_COM) ) |= (LCD_RAM_Data << LCD_SEG) & LCD_RAM_0_1_2_3H;		
			}		
		}
	}
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
