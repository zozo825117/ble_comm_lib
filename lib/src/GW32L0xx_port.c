/**
******************************************************************************
  * @file    GW32L0xx_port.c
  * @author  GW_IOM
  * @version V1.0.4
  * @date    2018-10-18
  * @brief   This file provides firmware functions to manage the following
  *
 @verbatim
**/

#include "GW32L0xx_port.h"

/* Added to modify the original output pin operation mutual interference problem.*/
/* (When the output pin is forced to pull low at the open-drain output, 
 *  and the adjacent pin has an operation output, it will change its output state)*/
static unsigned long gvPortOut[7]  = 
{
  0xffff,
  0xffff,
  0xffff,
  0xffff,
  0xffff,
  0xffff,
  0xffff,
};

/**
* @brief  Deinitializes the PORTx peripheral registers to their default reset values.
* @param  None	
* @retval None
*/ 
void PORT_DeInit(void)
{
  do
  {
    /* Restore port peripheral register to the reset value */
    PERI_RST_CTRL1 |= RMU_PERI_RESET1_PORT;
	
  } while ( (PERI_RST_CTRL1 & RMU_PERI_RESET1_PORT) != RMU_PERI_RESET1_PORT );
  
  /* Switch to work in normal mode */
  PERI_RST_CTRL1 &= ~RMU_PERI_RESET1_PORT;	
}

/**
* @brief  Fills each PORT_InitStruct member with its default value.
* @param  PORT_InitStruct: pointer to a PORT_InitTypeDef structure which will
*         be initialized.
* @retval None
*/
void PORT_StructInit(PORT_InitTypeDef* PORT_InitStruct)
{
  /* Reset PORT init structure parameters values */
  PORT_InitStruct->PORT_Pin = PORT_Pin_All;
  PORT_InitStruct->PORT_Properity = PORT_Properity_Digital;
  PORT_InitStruct->PORT_Mode = PORT_Mode_IN;
  PORT_InitStruct->PORT_OutType = PORT_OutType_PP;
  PORT_InitStruct->PORT_PullHigh = PORT_PH_NoPullHigh;
  PORT_InitStruct->PORT_DriveSink = PORT_DS_DriveSinkNormal;	
}

/**
* @brief  Initializes the PORTx peripheral according to the specified
*         parameters in the PORT_InitStruct.
* @param  PORTx: where x can be (0..6) to select the PORT peripheral.
* @param  PORT_InitStruct: pointer to a PORT_InitTypeDef structure that
*         contains the configuration information for the specified PORT peripheral.
* @retval None
*/
void PORT_Init(PORT_TypeDef* PORTx, PORT_InitTypeDef* PORT_InitStruct)
{
  uint16_t pinpos, pos, currentpin;
  
  /* Check the parameters */
  assert_param(IS_PORT_ALL_PERIPH(PORTx));
  assert_param(IS_PORT_PIN(PORT_InitStruct->PORT_Pin));

  for (pinpos = 0x0; pinpos < 0x10; pinpos++)
  {
    pos = ((uint32_t)0x1) << pinpos;
	
    /* Get the port pins position */
    currentpin = (PORT_InitStruct->PORT_Pin) & pos;
	
    if (currentpin == pos)
    {	
      /* Check the parameters */
      assert_param(IS_PORT_PROPERITY(PORT_InitStruct->PORT_Properity));
	  
      /* Set port attribute(digital or analog) in specified pin */
      PORTx->Pn_SEL0 &= ~(currentpin);
      PORTx->Pn_SEL0 |= (PORT_InitStruct->PORT_Properity << pinpos);
	  
      /* Check the parameters */
      assert_param(IS_PORT_MODE(PORT_InitStruct->PORT_Mode));
	  
      /* Set port direction(input or output) in specified pin */			
      PORTx->Pn_DIR &= ~(currentpin);
      PORTx->Pn_DIR |= (PORT_InitStruct->PORT_Mode << pinpos);
	  
      /* Check the parameters */
      assert_param(IS_PORT_OUTTYPE(PORT_InitStruct->PORT_OutType));

      /* Enable the output mode of port (open-drain or pull-push) function in specified pin */			
      PORTx->Pn_OPENDRAIN &= ~(currentpin);
      PORTx->Pn_OPENDRAIN |= (PORT_InitStruct->PORT_OutType << pinpos);
	  
      /* Check the parameters */
      assert_param(IS_PORT_PH(PORT_InitStruct->PORT_PullHigh));
	  
      /* Enable or disable internal pull-high resister in specified pin */			
      PORTx->Pn_PH &= ~(currentpin);
      PORTx->Pn_PH |= (PORT_InitStruct->PORT_PullHigh << pinpos);
	  
      /* Check the parameters */	
      assert_param(IS_PORT_DS(PORT_InitStruct->PORT_DriveSink));
	  
      /* Enable port (drivesink or normal) driver in specified pin */				
      PORTx->Pn_DS &= ~(currentpin);
      PORTx->Pn_DS |= (PORT_InitStruct->PORT_DriveSink << pinpos);			
    }
  }
}

/**
* @brief  Initializes the PORTx peripheral according to the specified
*         parameters in the PORT_InitStruct.
* @param  PORTx: where x can be (0..6) to select the PORT peripheral.
* @param  PORT_Pin: specifies the port bit to read.
*         This parameter can be PORT_Pin_x where x can be (0..15).
* @retval Value reading from port bit
*/
BitAction PORT_ReadInputDataBit(PORT_TypeDef* PORTx, uint16_t PORT_Pin)
{	
  /* Check the parameters */
  assert_param(IS_PORT_ALL_PERIPH(PORTx));
  assert_param(IS_GET_PORT_PIN(PORT_Pin));
  
  return (PORTx->Pn & PORT_Pin) != PORT_Pin ? Bit_RESET : Bit_SET;
}

/**
* @brief  Reads the specified PORT input data port.
* @param  PORTx: where x can be (0..6) to select the PORT peripheral.
* @retval PORT input data port value.
*/
uint16_t PORT_ReadInputData(PORT_TypeDef* PORTx)
{
  /* Check the parameters */
  assert_param(IS_PORT_ALL_PERIPH(PORTx));
  
  return (uint16_t)PORTx->Pn;
}

/**
* @brief  Reads the specified output data port bit.
* @param  PORTx: where x can be (0..6) to select the PORT peripheral.
* @param  PORT_Pin:  specifies the port bit to read.
*         This parameter can be PORT_Pin_x where x can be (0..15).
* @retval The output port pin value.
*/
BitAction PORT_ReadOutputDataBit(PORT_TypeDef* PORTx, uint16_t PORT_Pin)
{	
  /* Port location */
  unsigned long vSite;
  
  /* Check the parameters */
  assert_param(IS_PORT_ALL_PERIPH(PORTx));
  assert_param(IS_GET_PORT_PIN(PORT_Pin));
  
  /* Calculate port location */
  vSite = (unsigned long)((unsigned long)PORTx - PORT_0_BASEADDR)/(PORT_1_BASEADDR-PORT_0_BASEADDR);
  
  /* Return result */
  return (gvPortOut[vSite] & PORT_Pin) != PORT_Pin ? Bit_RESET : Bit_SET;
}

/**
* @brief  Reads the specified PORT output data port.
* @param  PORTx: where x can be (0..6) to select the PORT peripheral.
* @retval PORT output data port value.
*/
uint16_t PORT_ReadOutputData(PORT_TypeDef* PORTx)
{
  /* Port location */
  unsigned long vSite;
  
  /* Check the parameters */
  assert_param(IS_PORT_ALL_PERIPH(PORTx));
  
  /* Calculate port location */
  vSite = (unsigned long)((unsigned long)PORTx - PORT_0_BASEADDR)/(PORT_1_BASEADDR-PORT_0_BASEADDR);
  return (uint16_t)gvPortOut[vSite];
}

/**
* @brief  Sets the selected data port bits.
* @param  PORTx: where x can be (0..6) to select the PORT peripheral.
* @param  PORT_Pin: specifies the port bits to be written.
*         This parameter can be any combination of PORT_Pin_x where x can be (0..15).
* @retval None
*/
void PORT_SetBits(PORT_TypeDef* PORTx, uint16_t PORT_Pin)
{
  /* Port location */
  unsigned long vSite;
  
  /* Check the parameters */
  assert_param(IS_PORT_ALL_PERIPH(PORTx));
  assert_param(IS_PORT_PIN(PORT_Pin));
  
  /* Calculate port location */
  vSite = (unsigned long)((unsigned long)PORTx - PORT_0_BASEADDR)/(PORT_1_BASEADDR-PORT_0_BASEADDR);
  
  /* Operation cache */
  gvPortOut[vSite] |= PORT_Pin;
  
  /* Return result */
  PORTx->Pn = gvPortOut[vSite];
}

/**
* @brief  Clears the selected data port bits.
* @param  PORTx: where x can be (0..6) to select the PORT peripheral.
* @param  PORT_Pin: specifies the port bits to be written.
*   This parameter can be any combination of PORT_Pin_x where x can be (0..15).
* @retval None
*/
void PORT_ResetBits(PORT_TypeDef* PORTx, uint16_t PORT_Pin)
{
  /* Port location */
  unsigned long vSite;
  
  /* Check the parameters */
  assert_param(IS_PORT_ALL_PERIPH(PORTx));
  assert_param(IS_PORT_PIN(PORT_Pin));
  
  /* Calculate port location */
  vSite = (unsigned long)((unsigned long)PORTx - PORT_0_BASEADDR)/(PORT_1_BASEADDR-PORT_0_BASEADDR);
  
  /* Operation cache */
  gvPortOut[vSite] &= ~PORT_Pin;
  
  /* Return result */
  PORTx->Pn = gvPortOut[vSite];
}

/**
* @brief  Sets or clears the selected data port bit.
* @param  PORTx: where x can be (0..6) to select the PORT peripheral.
* @param  PORT_Pin: specifies the port bit to be written.
*         This parameter can be one of PORT_Pin_x where x can be (0..15).
* @param  BitVal: specifies the value to be written to the selected bit.
*         This parameter can be one of the BitAction enum values:
*         	@arg Bit_RESET: to clear the port pin
*         	@arg Bit_SET: to set the port pin
* @retval None
*/
void PORT_WriteBit(PORT_TypeDef* PORTx, uint16_t PORT_Pin, BitAction BitVal)
{
  /* Port location */
  unsigned long vSite;
  
  /* Check the parameters */
  assert_param(IS_PORT_ALL_PERIPH(PORTx));
  assert_param(IS_GET_PORT_PIN(PORT_Pin));
  assert_param(IS_PORT_BIT_ACTION(BitVal));
  
  /* Calculate port location */
  vSite = (unsigned long)((unsigned long)PORTx - PORT_0_BASEADDR)/(PORT_1_BASEADDR-PORT_0_BASEADDR);
  
  /* Operation cache */
  if(BitVal != Bit_RESET)
  {
    gvPortOut[vSite] |= PORT_Pin;
  }
  else
  {
    gvPortOut[vSite] &= ~PORT_Pin;
  }
  
  /* Return result */
  PORTx->Pn = gvPortOut[vSite];
}

/**
* @brief  Writes data to the specified PORT data port.
* @param  PORTx: where x can be (0..6) to select the PORT peripheral.
* @param  PortVal: specifies the value to be written to the port output data register.
* @retval None
*/
void PORT_Write(PORT_TypeDef* PORTx, uint16_t PortVal)
{
  /* Port location */
  unsigned long vSite;
  /* Check the parameters */
  assert_param(IS_PORT_ALL_PERIPH(PORTx));
  /* Calculate port location */
  vSite = (unsigned long)((unsigned long)PORTx - PORT_0_BASEADDR)/(PORT_1_BASEADDR-PORT_0_BASEADDR);
  
  /* Operation cache */
  gvPortOut[vSite] = PortVal;
  
  /* Return result */
  PORTx->Pn = gvPortOut[vSite];
}

/**
* @brief  Toggle the selected data port bits.
* @param  PORTx: where x can be (0..6) to select the PORT peripheral.
* @param  PORT_Pin: specifies the port bits to be toggled.
*         This parameter can be one of PORT_Pin_x where x can be (0..15).
* @retval None
*/
void PORT_ToggleBit(PORT_TypeDef* PORTx, uint16_t PORT_Pin)
{
  /* Port location */
  unsigned long vSite;
  
  /* Check the parameters */
  assert_param(IS_PORT_ALL_PERIPH(PORTx));
  assert_param(IS_GET_PORT_PIN(PORT_Pin));
  
  /* Calculate port location */
  vSite = (unsigned long)((unsigned long)PORTx - PORT_0_BASEADDR)/(PORT_1_BASEADDR-PORT_0_BASEADDR);
  
  /* Operation cache */
  gvPortOut[vSite] ^= PORT_Pin;
  
  /* Return result */
  PORTx->Pn = gvPortOut[vSite];
}

/**
* @brief  Initializes the PORT peripheral according to the specified parameters.
* @param  PORTx: where x can be (0..6) to select the PORT peripheral.
* @param  PORT_PinSource: specifies the port bits to be the setting of EXTI
* @param	PORT_EXTI_InitStruct: initializes the port pin EXTI attribute 
according to the specified parameters PORTx and PORT_PinSource. 
* @retval  None
*/
void PORT_EXTI_Init(PORT_TypeDef* PORTx, uint8_t PORT_PinSource, PORT_EXTI_InitTypeDef* PORT_EXTI_InitStruct)
{	
  /* Check the parameters */
  assert_param(IS_PORT_EXTI_INPUTSOURCESEL(PORT_EXTI_InitStruct->PORT_EXTI_InputSource));
  
  /* Select level as toggled mode */
  if (PORT_EXTI_InitStruct->PORT_EXTI_InputSource == PORT_EXTI_InputSource_Level)
  {
    /* Check the parameters */
    assert_param(IS_PORT_ALL_PERIPH(PORTx));

    PORTx->Pn_PULSE_SEL &= ~(0x3UL << 2 * PORT_PinSource);
	
    if (PORT_EXTI_InitStruct->PORT_EXTI_Cmd != DISABLE)
    {
      /* Check the parameters */
      assert_param(IS_PORT_EXTI_TRIGGER_LEVEL(PORT_EXTI_InitStruct->PORT_EXTI_Trigger));
      assert_param(IS_PORT_PIN_SOURCE(PORT_PinSource));

      PORTx->Pn_PULSE_SEL |= PORT_EXTI_InitStruct->PORT_EXTI_Trigger << 2 * PORT_PinSource;
    }
  }
  else
  {
    /* Select edge as toggled mode */	
    if (PORT_EXTI_InitStruct->PORT_EXTI_InputSource == PORT_EXTI_InputSource_Edge)
    { 
      /* Check the parameters */
      assert_param(IS_PORT_ALL_PERIPH(PORTx));

      PORTx->Pn_EDGE_SEL &= ~(0x3UL << 2 * PORT_PinSource);
	  
      if (PORT_EXTI_InitStruct->PORT_EXTI_Cmd != DISABLE)
      {	
        /* Check the parameters */
        assert_param(IS_PORT_EXTI_TRIGGER_EDGE(PORT_EXTI_InitStruct->PORT_EXTI_Trigger));
        assert_param(IS_PORT_PIN_SOURCE(PORT_PinSource));

        PORTx->Pn_EDGE_SEL |= PORT_EXTI_InitStruct->PORT_EXTI_Trigger << 2 * PORT_PinSource;
      }
    }
  }
}

/** 
* @brief	Reset the structure of PORT_EXTI
* @param	PORT_EXTI_InitStruct: specifies the structure to set as reset value.
* @retval None
*/
void PORT_EXTI_StructInit(PORT_EXTI_InitTypeDef* PORT_EXTI_InitStruct)
{
  /* Reset PORT init structure parameters values */
  PORT_EXTI_InitStruct->PORT_EXTI_InputSource = PORT_EXTI_InputSource_NO;
  PORT_EXTI_InitStruct->PORT_EXTI_Trigger = PORT_EXTI_Trigger_NO;
  PORT_EXTI_InitStruct->PORT_EXTI_Cmd = DISABLE;
}

/**
* @brief	Get external interrupt flag of port bit.
* @param  PORTx: where x can be (0..6) to select the PORT peripheral.
* @param  PORT_Pin: specifies the port bit to be got.
* @retval RESET or SET
*/
ITStatus PORT_EXTI_GetITStatus(PORT_TypeDef* PORTx, uint16_t PORT_Pin)
{
  /* Check the parameters */
  assert_param(IS_PORT_ALL_PERIPH(PORTx));
  assert_param(IS_GET_PORT_PIN(PORT_Pin));
	
  return (PORTx->Pn_IFG & PORT_Pin) != PORT_Pin ? RESET : SET;
}

/**
* @brief	Clear interrupt flag of port bit.
* @param  PORTx: where x can be (0..6) to select the PORT peripheral.
* @param  PORT_Pin: specifies the port bit or PORT_Pin_All to be cleared.
* @retval None
*/
void PORT_EXTI_ClearITFlag(PORT_TypeDef* PORTx, uint16_t PORT_Pin)
{
  /* Check the parameters */
  assert_param(IS_PORT_ALL_PERIPH(PORTx));
  assert_param(IS_GET_PORT_PIN(PORT_Pin));
  
  PORTx->Pn_IFG	&= ~PORT_Pin;
}

/**
* @brief  Enable or disable EXTI request to NVIC.
* @param  PORTx: where x can be (0..6) to select the PORT peripheral.
* @param  PORT_Pin: specifies the port bit to be requested.
* @param  NewState: ENABLE or DISABLE
* @retval None
*/
void PORT_EXTI_ITConfig(PORT_TypeDef* PORTx, uint16_t PORT_Pin, FunctionalState NewState)
{
  /* Check the parameters */
  assert_param(IS_PORT_ALL_PERIPH(PORTx));
  assert_param(IS_GET_PORT_PIN(PORT_Pin));
  
  if (NewState != DISABLE)
  {
    do
    {
      PORTx->Pn_IE |= PORT_Pin;
    } while ( (PORTx->Pn_IE & PORT_Pin) != PORT_Pin );	
  }
  else
  {
    do
    {
      PORTx->Pn_IE &= ~PORT_Pin;
    } while ( (PORTx->Pn_IE & PORT_Pin) == PORT_Pin );
  }
}

/**
* @brief	Set port pin alternative function.
* @param  PORTx: where x can be (0..6) to select the PORT peripheral.
* @param  PORT_PinSource: specifies the port bit to be configurated.
* @param  PORT_AF: define as follow
*		@arg 	PORT_AF_0	 < GPIO >
*   @arg 	PORT_AF_1  < UART1, UART2, UART3, UART4, UART5, UART6 >
*   @arg 	PORT_AF_2  < IrDA1, IrDA2, UART3, UART5, UART6, RTC >
*   @arg 	PORT_AF_3  < SPI1_M, SPI2_M, SPI3_M, SPI4_M >
*   @arg 	PORT_AF_4  < SPI1_S, SPI2_S, SPI3_S, SPI4_S >                                           
*   @arg 	PORT_AF_5  < PCLK, IRC16M, IRC38K, ADC_CLK_OUT, I2C1, I2C2, 7816, VC, LVD, BASETIMER, HCLK, XTAL32K >                                
*   @arg 	PORT_AF_6  < HCLK, XTAL32K, XTAL32M, IRC38K, TIMER1, TIMER2, TIMER3, TIMER4, VC, LVD, BUZZER >
*   @arg 	PORT_AF_7  < PCA1, PCA2, PCA3, PCA4, VC, LVD, TIMER1, TIMER2, TIMER3, TIMER4 >        
* @retval None
*/
void PORT_PinAFConfig(PORT_TypeDef* PORTx, uint8_t PORT_PinSource, uint8_t PORT_AF)
{
  /* Check the parameters */
  assert_param(IS_PORT_ALL_PERIPH(PORTx));
  assert_param(IS_PORT_PIN_SOURCE(PORT_PinSource));
  assert_param(IS_PORT_AF(PORT_AF));
  
  if (PORT_PinSource < PORT_PinSource8)
  {
    PORTx->Pn_SEL1 &= ~(0x7UL << PORT_PinSource * 3);
    PORTx->Pn_SEL1 |= (PORT_AF << PORT_PinSource * 3);
  }
  else
  {
    PORTx->Pn_SEL2 &= ~(0x7UL << (PORT_PinSource - PORT_PinSource8) * 3);
    PORTx->Pn_SEL2 |= (PORT_AF << (PORT_PinSource - PORT_PinSource8) * 3);
  }
}

/************************ (C) COPYRIGHT GWTRI *****END OF FILE****/
