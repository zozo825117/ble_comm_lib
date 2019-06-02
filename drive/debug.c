/*****************************************************************************
* File Name: debug.c
*
* Version: 1.0
*
* Description:
* This file contains Debug API
*
* Note:
* Define ENABLE_DEBUG_PIN in platform.h to enable macro for toggling the debug_pin
* Define DEBUG_PRINT in platform.h to enable debug print module
* Define SOFTWARE_UART in platform.h to enable debug print over Software Uart 
* else 'SCB configured as UART' is enabled 
*
* Owner: MRAO
*
* Related Document:
* UART component datasheet
*
* Hardware Dependency:
* UART
*
* Code Tested With:
* 1. PSoC Creator 3.1 
* 2. ARM GCC 4.8.4
******************************************************************************
* Copyright (2015), Cypress Semiconductor Corporation.
******************************************************************************
* This software is owned by Cypress Semiconductor Corporation (Cypress) and is
* protected by and subject to worldwide patent protection (United States and
* foreign), United States copyright laws and international treaty provisions.
* Cypress hereby grants to licensee a personal, non-exclusive, non-transferable
* license to copy, use, modify, create derivative works of, and compile the
* Cypress Source Code and derivative works for the sole purpose of creating
* custom software in support of licensee product to be used only in conjunction
* with a Cypress integrated circuit as specified in the applicable agreement.
* Any reproduction, modification, translation, compilation, or representation of
* this software except as specified above is prohibited without the express
* written permission of Cypress.
*
* Disclaimer: CYPRESS MAKES NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, WITH
* REGARD TO THIS MATERIAL, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. 
* Cypress reserves the right to make changes without further notice to the
* materials described herein. Cypress does not assume any liability arising out
* of the application or use of any product or circuit described herein. Cypress
* does not authorize its products for use as critical components in life-support
* systems where a malfunction or failure may reasonably be expected to result in
* significant injury to the user. The inclusion of Cypress' product in a life-
* support systems application implies that the manufacturer assumes all risk of
* such use and in doing so indemnifies Cypress against all charges. Use may be
* limited by and subject to the applicable Cypress software license agreement.
*****************************************************************************/

#include "debug.h"

#ifdef DEBUG_PRINT

static uint8_t debug_level;

/*****************************************************************************
* Function Name: Putc()
******************************************************************************
* Summary:
* This function is used to print a character on the UART 
*
* Parameters:
* uint8 ch - character value
*
* Return:
* None
*
* Theory:
* Send a character to the UART
*
* Side Effects:
* None 
*
* Note:
* None
*****************************************************************************/
static void Putc(int8_t ch)
{
	UART_SendData(DEBUG_UART,ch);
  while(UART_GetLineStatus(DEBUG_UART, UART_LSFLAG_TXEmpty) == RESET);
}

/*****************************************************************************
* Function Name: Byte_To_ASCII()
******************************************************************************
* Summary:
* This function is used to map the byte to its ASCII chacter value 
*
* Parameters:
* uint32 index - byte value
*
* Return:
* uint8 * - pointers to the ASCII character value
*
* Theory:
* Converts the byte into ascii character value using look-up table approach
*
* Side Effects:
* None 
*
* Note:
* None
*****************************************************************************/
static uint8_t* Byte_To_ASCII(uint32_t Index)
{
    return (uint8_t*)("0123456789abcdef" + Index);
}

/*****************************************************************************
* Function Name: Debug_Print_Init()
******************************************************************************
* Summary:
* This function is used to initialize the debug functionality
*
* Parameters:
* None
*
* Return:
* None
*
*****************************************************************************/
void Debug_Print_Init(void)
{
    UART_InitTypeDef UART_InitStruct;
    
    PORT_InitTypeDef PORT_InitStruct;
    
    CMU_APBPeriph1ClockCmd(CMU_APBPeriph1_PORT, ENABLE);
        //PORT_DeInit();
    PORT_InitStruct.PORT_Pin = DEBUG_UART_PINR; // RX = P6.0
    PORT_InitStruct.PORT_Properity = PORT_Properity_Digital;
    PORT_InitStruct.PORT_Mode = PORT_Mode_IN;
    PORT_InitStruct.PORT_PullHigh = PORT_PH_PullHigh;
    PORT_Init(DEBUG_UART_PORT, &PORT_InitStruct);
    
    PORT_InitStruct.PORT_Pin = DEBUG_UART_PINT; // TX = P6.1
    PORT_InitStruct.PORT_Properity = PORT_Properity_Digital;
    PORT_InitStruct.PORT_Mode = PORT_Mode_OUT;
    PORT_InitStruct.PORT_OutType = PORT_OutType_PP;
    PORT_InitStruct.PORT_PullHigh = PORT_PH_NoPullHigh;
    PORT_InitStruct.PORT_DriveSink = PORT_DS_DriveSinkNormal;
    PORT_Init(DEBUG_UART_PORT, &PORT_InitStruct);
    
    PORT_WriteBit(DEBUG_UART_PORT, DEBUG_UART_PINR, Bit_SET);
    PORT_WriteBit(DEBUG_UART_PORT, DEBUG_UART_PINT, Bit_SET);

    PORT_PinAFConfig(DEBUG_UART_PORT, PORT_PinSource0, PORT_AF_1); // Port alternative function
    PORT_PinAFConfig(DEBUG_UART_PORT, PORT_PinSource1, PORT_AF_1);       
    
    CMU_APBPeriph0ClockCmd(DEBUG_UART_PERIPH_CLOCK, ENABLE);
    UART_DeInit(DEBUG_UART);
    UART_StructInit(&UART_InitStruct);
    UART_InitStruct.UART_BaudRate = 115200;
    UART_InitStruct.UART_DataLength = UART_DataLength_8Bits;
    UART_InitStruct.UART_StopBits = UART_StopBits_1Bit;
    UART_InitStruct.UART_Parity = UART_Parity_None;
    UART_InitStruct.UART_HardwareFlowControl = UART_HardwareFlowControl_None;   
    UART_Init(DEBUG_UART, &UART_InitStruct);

    UART_ITConfig(DEBUG_UART, UART_IT_ReceiveData_RXFIFOTimeOutIE, ENABLE); 
    UART_ITConfig(DEBUG_UART, UART_IT_TXREmptyIE, DISABLE);

    __disable_irq();
    NVIC_DisableIRQ(DEBUG_UART_IRQ);
    NVIC_ClearPendingIRQ(DEBUG_UART_IRQ);
    NVIC_SetPriority(DEBUG_UART_IRQ, 0x0);
    NVIC_EnableIRQ(DEBUG_UART_IRQ);
    __enable_irq();
}
/*****************************************************************************
* Function Name: Debug_Print_Start()
******************************************************************************
* Summary:
* This function is used to initialize the debug functionality
*
* Parameters:
* uint8 level - Level for printing the debug message
*
* Return:
* None
*
* Theory:
* Starts the UART component and stores the debug_level for further procecssing
*
* Side Effects:
* debug_level is updated 
*
* Note:
* None
*****************************************************************************/
void Debug_Print_Start(uint8_t level)
{
    debug_level = level;
}

/*****************************************************************************
* Function Name: Debug_Print()
******************************************************************************
* Summary:
* This function is used to print the logs on the UART 
*
* Parameters:
* uint8 level - Level of the debug message
* uint8 *pszFmt - Message to be print
*
* Return:
* None
*
* Theory:
* The message will be printed if the level specified is above the debug level 
* set during the Debug_Statt()
*
* Side Effects:
* None
*
* Note:
* The message will be printed if the level specified is above the debug level 
* set during the Debug_Start()
*****************************************************************************/
void Debug_Print(uint8_t level, char *pszFmt,...)
{
    uint8_t *pszVal;
    uint32_t iVal, xVal, i = 0, buffer[12], index = 1;
    uint8_t cVal;
    uint32_t *pArg;
		int32_t dbuf;
    pArg =(uint32_t *)&pszFmt;
    if(level >= debug_level)
    {
        while(*pszFmt)
        {
            if('%' != *pszFmt)
            {
                Putc(*pszFmt);
                pszFmt++;
                continue;
            }
            pszFmt++;

            if(*pszFmt == 's')
            {
                pszVal = (uint8_t*)pArg[index++];
                for(; *pszVal != '\0'; pszVal++)
                    Putc(*pszVal);
                pszFmt++;
                continue;
            }
            if(*pszFmt == 'd')
            {
            		dbuf = pArg[index++];
								if(dbuf<0)
									{
										Putc('-');
										iVal = -dbuf;
									}
								else
									iVal = dbuf;
                //iVal = pArg[index++];
                i = 0;
                do{
                    buffer[i++] = iVal % 10;
                    iVal /= 10;
                }while(iVal);
                while(i > 0)
                {
                    i--;
                    Putc(*Byte_To_ASCII(buffer[i]));
                }
                pszFmt++;
                continue;
            }
            if(*pszFmt == 'c')
            {
                cVal = pArg[index++];
                Putc(cVal);
                pszFmt++;
                continue;
            }
            if(*pszFmt == 'x')
            {
                xVal = pArg[index++];
                i = 0;
                do{
                    buffer[i++] = xVal % 16;
                    xVal /= 16;
                }while(xVal);
                if(i%2!=0)
                    buffer[i++]=0;
                if(i<2)
                    buffer[i++]=0;

                while(i > 0)
                {
                    i--;
                    Putc(*Byte_To_ASCII(buffer[i]));
                }
                pszFmt++;
                continue;
            }
            if(pszFmt == '\0')
            {
                break;
            }
        }
    }
}

#endif /* DEBUG */
