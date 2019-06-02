/**
  ******************************************************************************
 * @file    GW32L.h
 * @author  GW_IOM
 * @version V1.0.4
 * @date    2018-10-18
 * @brief   CMSIS Core Peripheral Access Layer Header File for
 *          GW32L Device Series
 * *****************************************************************************
  * @attention
  *
  * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
  *
  ******************************************************************************
  */
   /*All rights reserved.
   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:
   - Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in the
     documentation and/or other materials provided with the distribution.
   - Neither the name of ARM nor the names of its contributors may be used
     to endorse or promote products derived from this software without
     specific prior written permission.
   *
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
   POSSIBILITY OF SUCH DAMAGE.
   ---------------------------------------------------------------------------*/


#ifndef ARMCM0plus_H
	#define ARMCM0plus_H

#ifdef __cplusplus
extern "C" {
#endif

/* Uncomment the line below according to the target STM32 device used in your
   application 
 */

#if !defined (GW32L0xx_xx)
  #define GW32L0xx_xx    /*!< GW32L0xx_xx: GW32L Low power devices */
#endif

#if !defined (GW32L0xx_xx)
	#error "Please select first the target GW32L0xx_xx device used in your application (in GW32L.h file)"
#endif

#if !defined( USE_STDPERIPH_DRIVER )
/**
	* @brief Comment the line below if you will not use the peripherals drivers.
		In this case, these drivers will not be included and the application code will 
		be based on direct access to peripherals registers 
	*/
	#define USE_STDPERIPH_DRIVER
#endif

/**
	* @brief In the following line adjust the value of External High Speed oscillator (HSE)
		used in your application 

		Tip: To avoid modifying this file each time you need to use different HSE, you
				 can define the HSE value in your toolchain compiler preprocessor.
	*/           
#if !defined( HSE_VALUE )
	#ifdef GW32L0xx_xx   
		#define HSE_VALUE    ((uint32_t)32000000) /*!< Value of the External oscillator in Hz */
  #else 
		#define HSE_VALUE    ((uint32_t)8000000)  /*!< Value of the External oscillator in Hz */
	#endif
#endif /* HSE_VALUE */

#define HSI_VALUE    ((uint32_t)16000000) /*!< Value of the InternalRC in Hz*/

#define LSE_VALUE    ((uint32_t)32768)    /*!< Value of the Low Speed External oscillator in Hz*/

#define LSI_VALUE    ((uint32_t)38500)    /*!< Value of the Low Speed InternalRC in Hz*/

#if !defined( FLASH_SIZE )
	#ifdef GW32L0xx_xx   
		#define FLASH_PAGE_SIZE    ((uint32_t)0x400)      /*!< Max value of pages in flash */
		#define FLASH_SIZE         ((uint32_t)0x40000)    /*!< Max size in flash */		
  #else 
		#define FLASH_PAGE_SIZE    ((uint32_t)0x20)       /*!< Max value of pages in flash */
		#define FLASH_SIZE         ((uint32_t)0x10000)    /*!< Max size in flash */
	#endif
#endif /* FLASH_SIZE */

#if !defined( RAM_SIZE )
	#ifdef GW32L0xx_xx   
		#define RAM_SIZE    ((uint32_t)0x8000) /*!< Max value of ram in chip */
  #else 
		#define RAM_SIZE    ((uint32_t)0x4000) /*!< Max value of ram in chip */
	#endif
#endif /* RAM_SIZE */

#if !defined( __SYSTEMRESET_BACKUPRAM_RESET )
/**
	* @brief Comment the line below if you will not use to reset the peripherals BACKUP RAM.
    In this case, these drivers will not be included and the application code will 
    be based on direct access to peripherals registers 
	*/
//	#define __SYSTEMRESET_BACKUPRAM_RESET
#endif

/* -------------------------  Interrupt Number Definition  ------------------------ */
typedef enum IRQn
{
/* -------------------  Cortex-M0+ Processor Exceptions Numbers  ------------------ */
  NonMaskableInt_IRQn   = -14,      /*!<  2 Non Maskable Interrupt          */
  HardFault_IRQn        = -13,      /*!<  3 HardFault Interrupt             */
  SVCall_IRQn           =  -5,      /*!< 11 SV Call Interrupt               */
  PendSV_IRQn           =  -2,      /*!< 14 Pend SV Interrupt               */
  SysTick_IRQn          =  -1,      /*!< 15 System Tick Interrupt           */
/* ----------------------  ARMCM0 Specific Interrupt Numbers  --------------------- */
   DMAC_IRQn            = 0,
   P0_IRQn              = 1,    
   TIMER1_IRQn          = 2,
   UART1_IRQn      	    = 3,
   SPI1_IRQn            = 4,
   I2C1_IRQn            = 5,
   RAM_IRQn             = 6,
   ADC_IRQn             = 7,
   VC_IRQn              = 8,
   LVD_IRQn             = 9,
   RTC_IRQn             = 10,
   BASETIMER_IRQn       = 11,
   P1P2_IRQn            = 12,
   P3P4_IRQn            = 13,
   P5P6_IRQn            = 14,
   TIMER2_IRQn          = 15,
   TIMER3_IRQn          = 16,
   TIMER4_IRQn          = 17,
   UART2_IRQn           = 18,
   UART3_IRQn           = 19,
   UART4_IRQn           = 20,
   UART5_IRQn           = 21,
   UART6_IRQn           = 22,
   SPI2_IRQn            = 23,
   SPI3_IRQn            = 24,
   SPI4_IRQn            = 25,
   I2C2_IRQn            = 26,
   PCA12_IRQn           = 27,
   PCA34_IRQn           = 28,
   WDT_IRQn             = 29,
   LCD_IRQn             = 30,
   SCI7816_IRQn         = 31

} IRQn_Type;

/* ================================================================================ */
/* ================      Processor and Core Peripheral Section     ================ */
/* ================================================================================ */

/* --------  Configuration of the Cortex-M0+ Processor and Core Peripherals  ------ */
#define __CM0PLUS_REV             0x0000    /*!< Core revision r0p0                              */
#define __MPU_PRESENT             0         /*!< MPU present or not                              */
#define __VTOR_PRESENT            1         /*!< VTOR present or not                             */
#define __NVIC_PRIO_BITS          2         /*!< Number of Bits used for Priority Levels         */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used    */

#include "core_cm0plus.h"                   /* Processor and core peripherals                    */
#include "system_GW32L.h"                   /* System Header                                     */
#include <stdint.h>

/* ================================================================================ */
/* ================       Device Specific Peripheral Section       ================ */
/* ================================================================================ */

/* -------------------  Start of section using anonymous unions  ------------------ */
#if   defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/* !< GW32L Standard Peripheral Library old types  */

typedef unsigned char       u8;
typedef unsigned short int  u16;
typedef unsigned int        u32;

typedef int32_t  s32;
typedef int16_t  s16;
typedef int8_t   s8;

typedef const int32_t   sc32;            /*!< Read Only */
typedef const int16_t   sc16;            /*!< Read Only */
typedef const int8_t    sc8;             /*!< Read Only */

typedef __IO int32_t    vs32;
typedef __IO int16_t    vs16;
typedef __IO int8_t     vs8;

typedef __I int32_t     vsc32;           /*!< Read Only */
typedef __I int16_t     vsc16;           /*!< Read Only */
typedef __I int8_t      vsc8;            /*!< Read Only */

typedef const uint32_t  uc32;            /*!< Read Only */
typedef const uint16_t  uc16;            /*!< Read Only */
typedef const uint8_t   uc8;             /*!< Read Only */

typedef __IO uint32_t   vu32;
typedef __IO uint16_t   vu16;
typedef __IO uint8_t    vu8;

typedef __I uint32_t    vuc32;           /*!< Read Only */
typedef __I uint16_t    vuc16;           /*!< Read Only */
typedef __I uint8_t     vuc8;            /*!< Read Only */

#define HSE_Value                   HSE_VALUE
#define HSI_Value                   HSI_VALUE
#define LSE_Value                   LSE_VALUE
#define LSI_Value                   LSI_VALUE

typedef enum {RESET = 0, SET = !RESET} FlagStatus, ITStatus;

typedef enum {DISABLE = 0, ENABLE = !DISABLE} FunctionalState;
#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE))

typedef enum {ERROR = 1, SUCCESS = !ERROR} ErrorStatus;

/* ================================================================================ */
/* ================              Peripheral memory map             ================ */
/* ================================================================================ */
// Peripheral_memory_map
#define   FLASH_BASE                (0x00000000) /*!< FLASH base address in the alias region */
#define   SRAM_BASE                 (0x20000000) /*!< SRAM base address in the alias region */
#define   PERIPH_BASE               (0x40000000) /*!< Peripheral base address in the alias region */

#define   UART_1_BASEADDR           (0x40000000)
#define   UART_2_BASEADDR           (0x40000400)
#define   UART_3_BASEADDR           (0x40000800)	
#define   I2C_1_BASEADDR            (0x40000C00)	
#define   SPIM_1_BASEADDR           (0x40001000)
#define   SPIM_2_BASEADDR           (0x40001400)		
#define   SPIS_1_BASEADDR           (0x40001800)	
#define   SPIS_2_BASEADDR           (0x40001C00)
#define   HS_MUX_BASEADDR           (0x40002000)
#define   CAL_BASEADDR              (0x40002400)
#define   SCI7816_BASEADDR          (0x40002800)
#define   TIMER_1_BASEADDR          (0x40002C00)					
#define   TIMER_2_BASEADDR          (0x40002C14)			
#define   TIMER_3_BASEADDR          (0x40002C28)			
#define   TIMER_4_BASEADDR          (0x40002C3C)	

#define   RNG_BASEADDR              (0x40003000)	
#define   LCD_BASEADDR              (0x40003400)
#define   UART_4_BASEADDR           (0x40010000)
#define   UART_5_BASEADDR           (0x40010400)
#define   UART_6_BASEADDR           (0x40010800)
#define   I2C_2_BASEADDR            (0x40010C00)
#define   SPIM_3_BASEADDR           (0x40011000)
#define   SPIM_4_BASEADDR           (0x40011400)
#define   SPIS_3_BASEADDR           (0x40011800) 
#define   SPIS_4_BASEADDR           (0x40011C00)
#define   RTC_BASEADDR              (0x40012000)
#define   WDT_BASEADDR              (0x40012400)
#define   BASETIMER_BASEADDR        (0x40012800)

#define   PORT_0_BASEADDR           (0x40012C00)
#define   PORT_1_BASEADDR           (0x40012C40)
#define   PORT_2_BASEADDR           (0x40012C80)
#define   PORT_3_BASEADDR           (0x40012CC0)
#define   PORT_4_BASEADDR           (0x40012D00)
#define   PORT_5_BASEADDR           (0x40012D40)
#define   PORT_6_BASEADDR           (0x40012D80)
#define   PCA_1_BASEADDR            (0x40013000)
#define   PCA_2_BASEADDR            (0x40013050)				  
#define   PCA_3_BASEADDR            (0x400130A0)					
#define   PCA_4_BASEADDR            (0x400130F0)
#define   ANALOG_CTRL_BASEADDR      (0x40013400)
#define   EFLASH_CTRL_BASEADDR      (0x40020000)
#define   PMU_CTRL_BASEADDR         (0x40020400)		
#define   DMAC_BASEADDR             (0x40020C00)
#define   CRC_BASEADDR              (0x40021000)	
#define   DES_BASEADDR              (0x40021800)	

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//  DMAC_BASEADDR             		
#define   CH0_SRCADDR               *((volatile unsigned int *)(DMAC_BASEADDR+0x000))	
#define   CH0_DSTADDR               *((volatile unsigned int *)(DMAC_BASEADDR+0x008))	
#define   CH0_CTRL0                 *((volatile unsigned int *)(DMAC_BASEADDR+0x018))	
#define   CH0_CTRL1                 *((volatile unsigned int *)(DMAC_BASEADDR+0x01c))						
#define   CH0_CFG0                  *((volatile unsigned int *)(DMAC_BASEADDR+0x040))
#define   CH0_CFG1                  *((volatile unsigned int *)(DMAC_BASEADDR+0x044))	
#define   CH0_SRCGAT                *((volatile unsigned int *)(DMAC_BASEADDR+0x048))
#define   CH0_DSTSCA                *((volatile unsigned int *)(DMAC_BASEADDR+0x050))		

#define   CH1_SRCADDR               *((volatile unsigned int *)(DMAC_BASEADDR+0x058))	
#define   CH1_DSTADDR               *((volatile unsigned int *)(DMAC_BASEADDR+0x060))	
#define   CH1_CTRL0                 *((volatile unsigned int *)(DMAC_BASEADDR+0x070))	
#define   CH1_CTRL1                 *((volatile unsigned int *)(DMAC_BASEADDR+0x074))						
#define   CH1_CFG0                  *((volatile unsigned int *)(DMAC_BASEADDR+0x098))
#define   CH1_CFG1                  *((volatile unsigned int *)(DMAC_BASEADDR+0x09c))	
#define   CH1_SRCGAT                *((volatile unsigned int *)(DMAC_BASEADDR+0x0a0))
#define   CH1_DSTSCA                *((volatile unsigned int *)(DMAC_BASEADDR+0x0a8))	

//dma common register				
#define   DMA_RawTc             		*((volatile unsigned int *)(DMAC_BASEADDR+0x2c0))	
#define   DMA_RawBlkTc        			*((volatile unsigned int *)(DMAC_BASEADDR+0x2c8))	
#define   DMA_RawSrcTc          		*((volatile unsigned int *)(DMAC_BASEADDR+0x2d0))	
#define   DMA_RawDstTc          		*((volatile unsigned int *)(DMAC_BASEADDR+0x2d8))				
#define   DMA_RawErr            		*((volatile unsigned int *)(DMAC_BASEADDR+0x2e0))	

#define   DMA_Tc                		*((volatile unsigned int *)(DMAC_BASEADDR+0x2e8))		
#define   DMA_BlkTc             		*((volatile unsigned int *)(DMAC_BASEADDR+0x2f0))	
#define   DMA_SrcTc             		*((volatile unsigned int *)(DMAC_BASEADDR+0x2f8))	
#define   DMA_DstTc             		*((volatile unsigned int *)(DMAC_BASEADDR+0x300))				
#define   DMA_Err               		*((volatile unsigned int *)(DMAC_BASEADDR+0x308))

#define   DMA_MaskTc            		*((volatile unsigned int *)(DMAC_BASEADDR+0x310))		
#define   DMA_MaskBlkTc         		*((volatile unsigned int *)(DMAC_BASEADDR+0x318))	
#define   DMA_MaskSrcTc         		*((volatile unsigned int *)(DMAC_BASEADDR+0x320))	
#define   DMA_MaskDstTc         		*((volatile unsigned int *)(DMAC_BASEADDR+0x328))				
#define   DMA_MaskErr           		*((volatile unsigned int *)(DMAC_BASEADDR+0x330))

#define   DMA_ClearTc           		*((volatile unsigned int *)(DMAC_BASEADDR+0x338))		
#define   DMA_ClearBlkTc        		*((volatile unsigned int *)(DMAC_BASEADDR+0x340))	
#define   DMA_ClearSrcTc        		*((volatile unsigned int *)(DMAC_BASEADDR+0x348))	
#define   DMA_ClearDstTc        		*((volatile unsigned int *)(DMAC_BASEADDR+0x350))				
#define   DMA_ClearErr          		*((volatile unsigned int *)(DMAC_BASEADDR+0x358))

#define   DMA_CombIntr          		*((volatile unsigned int *)(DMAC_BASEADDR+0x360))
#define   DMA_SrcTranReq        		*((volatile unsigned int *)(DMAC_BASEADDR+0x368))
#define   DMA_DstTranReq        		*((volatile unsigned int *)(DMAC_BASEADDR+0x370))
#define   DMA_SrcSglTranReq     		*((volatile unsigned int *)(DMAC_BASEADDR+0x378))
#define   DMA_DstSglTranReq     		*((volatile unsigned int *)(DMAC_BASEADDR+0x380))	

#define   DMA_EN                		*((volatile unsigned int *)(DMAC_BASEADDR+0x398))	
#define   DMA_CHxEN             		*((volatile unsigned int *)(DMAC_BASEADDR+0x3a0))			

//#define   HS_MUX_BASEADDR           (0x40002000)
#define   HS0_CFG               		*((volatile unsigned int *)(HS_MUX_BASEADDR+0x00))
#define   HS1_CFG               		*((volatile unsigned int *)(HS_MUX_BASEADDR+0x04))
#define   HS2_CFG               		*((volatile unsigned int *)(HS_MUX_BASEADDR+0x08))
#define   HS3_CFG               		*((volatile unsigned int *)(HS_MUX_BASEADDR+0x0c))					

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++		
//  ANALOG_CTRL_BASEADDR
#define   SYSCLK0		            	*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x00))
#define   SYSCLK1		            	*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x04))
#define   PMU_CTRL    		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x08))
#define   IRC16M_CTRL 		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x0C))
#define   XHF_CTRL			        	*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x10))
#define   IRC38K_CTRL 		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x14))
#define   XLF_CTRL 		          		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x18))
#define   RESETFLAG   		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x20))
#define   BGR_CTRL    		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x28))
#define   LVD_CTRL0   		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x2C))
#define   LVD_CTRL1   		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x30))
#define   VC_CTRL0    		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x34))
#define   VC_CTRL1    		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x38))
#define   PERI_CLK_CTRL0        		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x40))
#define   PERI_CLK_CTRL1	      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x44))
#define   PERI_RST_CTRL0	      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x48))
#define   PERI_RST_CTRL1	      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x4C))
#define   CLKCAL_CTRL   		      	*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x50))
#define   CALCNT    	          		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x54))
#define   REFCNT  	            		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x58))
#define   ADC_CTRL0   		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x60))
#define   ADC_CTRL1   		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x64))
#define   ADC_CTRL2   		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x68))
#define   ADC_RESULT_ACC        		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x6C))
#define   DEBUG_ACTIVE          		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x70))
#define   BUZZER                		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x74))

#define   ADC_RESULT0  		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x80))
#define   ADC_RESULT1  		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x84))
#define   ADC_RESULT2  		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x88))
#define   ADC_RESULT3  		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x8C))
#define   ADC_RESULT4  		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x90))	
#define   ADC_RESULT5  		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x94))
#define   ADC_RESULT6  	  	    		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x98))
#define   ADC_RESULT7  	  	    		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x9C))
#define   BACKUP_RAM0  	  	    		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0xC0))	
#define   BACKUP_RAM1  	  	    		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0xC4))		
#define   BACKUP_RAM2  	  	    		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0xC8))
#define   BACKUP_RAM3  	  	    		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0xCC))
#define   BACKUP_RAM4  	  	    		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0xD0))		
#define   BACKUP_RAM5  	  	    		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0xD4))
#define   BACKUP_RAM6  	    	  		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0xD8))
#define   BACKUP_RAM7  	  	    		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0xDC))
#define   BACKUP_RAM8  	  	    		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0xE0))
#define   BACKUP_RAM9  	  	    		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0xE4))
#define   BACKUP_RAMA  	  	    		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0xE8))
#define   BACKUP_RAMB  	  	    		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0xEC))
#define   BACKUP_RAMC  		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0xF0))
#define   BACKUP_RAMD  		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0xF4))	
#define   BACKUP_RAME  		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0xF8))
#define   BACKUP_RAMF  		      		*((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0xFC))

#define   RAM_FAULT_INTR  		  		*((volatile unsigned int *)(EFLASH_CTRL_BASEADDR+0x64))
#define   RAM_FAULT_ADDR  		  		*((volatile unsigned int *)(EFLASH_CTRL_BASEADDR+0x68))

#define   CAL0                  		*((volatile unsigned int *)(CAL_BASEADDR+0x80))
#define   CAL1                  		*((volatile unsigned int *)(CAL_BASEADDR+0x84))
#define   CAL2                  		*((volatile unsigned int *)(CAL_BASEADDR+0x88))
#define   CAL3                  		*((volatile unsigned int *)(CAL_BASEADDR+0x8C))
#define   CAL4                  		*((volatile unsigned int *)(CAL_BASEADDR+0x90))
#define   CAL5                  		*((volatile unsigned int *)(CAL_BASEADDR+0x94))
#define   CAL6                  		*((volatile unsigned int *)(CAL_BASEADDR+0x98))
#define   CAL7                  		*((volatile unsigned int *)(CAL_BASEADDR+0x9C))

#define   SYSTICK_TIMER             *((volatile unsigned int *)(ANALOG_CTRL_BASEADDR+0x7C))

/* ================================================================================ */
/* ================            UART                                ================ */
/* ================================================================================ */	
typedef struct
{
    __IO u32  RXR;                 
	__IO u32  INTENR;         
	__IO u32  INTIDR;                                  
	__IO u32  LNCR;
	__IO u32  MDMCR;
	__IO u32  LNSR;
	__IO u32  MDMSR; 
       u32  RESERVED0[21];         
	__IO u32  FIFOAR;           
	__IO u32  TFIFORR;  
	__IO u32  RFIFOWR;  
       u32  RESERVED1[10]; 
	__IO u32  HLTEN;    
	__IO u32  DMASWACK;

} UART_TypeDef;

#define   TXR       								RXR
#define   BDL       								RXR
#define   BDH       								INTENR
#define   FIFOCR    								INTIDR

#define   UART_1                    ((UART_TypeDef *)UART_1_BASEADDR)
#define   UART_2                    ((UART_TypeDef *)UART_2_BASEADDR)
#define   UART_3                    ((UART_TypeDef *)UART_3_BASEADDR)
#define   UART_4                    ((UART_TypeDef *)UART_4_BASEADDR)
#define   UART_5                    ((UART_TypeDef *)UART_5_BASEADDR)
#define   UART_6                    ((UART_TypeDef *)UART_6_BASEADDR)

/* ================================================================================ */
/* ================            I2C                                 ================ */
/* ================================================================================ */
typedef struct
{
	__IO u32 CTRL;            
	__IO u32 TARADDR;            
	__IO u32 SARADDR; 
       u32 RESERVED0[1];		
	__IO u32 DC;       
	__IO u32 SCLH_SS;        
	__IO u32 SCLL_SS;        
	__IO u32 SCLH_FS;        
	__IO u32 SCLL_FS;        
       u32 RESERVED1[2];	        
	__IO u32 ISR;      
	__IO u32 IMR;      
	__IO u32 RISR;  
	__IO u32 RXTH;          
	__IO u32 TXTH;          
	__IO u32 ICLR;       
	__IO u32 RXU_CLR;   
	__IO u32 RXO_CLR;    
	__IO u32 TXO_CLR;    
	__IO u32 RDR_CLR;     
	__IO u32 TXA_CLR;    
	__IO u32 RXD_CLR;    
	__IO u32 ACT_CLR;   
	__IO u32 SPDET_CLR;   
	__IO u32 SDET_CLR;  
	__IO u32 GC_CLR;   
	__IO u32 EN;         
	__IO u32 STS;         
	__IO u32 TXFL;          
	__IO u32 RXFL;
	__IO u32 SDAHOLD;	
	__IO u32 TXABRTS;
       u32 RESERVED2[1];		
	__IO u32 DMAC;         
	__IO u32 DMATL;       
	__IO u32 DMARL;       
	__IO u32 SDASETUP; 	    
	__IO u32 GCALL_ACK; 
	__IO u32 ENSTS;    
	__IO u32 SPKF; 
       u32 RESERVED3[1];		
	__IO u32 RSDET_CLR;

} I2C_TypeDef;

#define   I2C_1                     ((I2C_TypeDef *)I2C_1_BASEADDR)
#define   I2C_2                     ((I2C_TypeDef *)I2C_2_BASEADDR)

/* ================================================================================ */
/* ================            SPI                                 ================ */
/* ================================================================================ */
typedef struct
{
	__IO u32 CTRL0;    
	__IO u32 CTRL1;    
	__IO u32 EN;    
	__IO u32 MW_CTRL;      
	__IO u32 SSEL;       
	__IO u32 BAUD;     
	__IO u32 TXTHL;    
	__IO u32 RXTHL;    
	__IO u32 TXTL;     
	__IO u32 RXTL;     
	__IO u32 STS;        
	__IO u32 IM;       
	__IO u32 IS;       
	__IO u32 RIS;      
	__IO u32 TXOV_ICR;    
	__IO u32 RXOV_ICR;    
	__IO u32 RXUD_ICR;    
	__IO u32 MMC_ICR;    
	__IO u32 INT_CLR;       
	__IO u32 DMA_CTRL;     
	__IO u32 DMA_TXL;   
	__IO u32 DMA_RXL; 
	     u32 RESERVED0[2];	
	__IO u32 DATABUF;     

} SPI_TypeDef;

#define   SPIM_1                    ((SPI_TypeDef *)SPIM_1_BASEADDR)
#define   SPIM_2                    ((SPI_TypeDef *)SPIM_2_BASEADDR)
#define   SPIM_3                    ((SPI_TypeDef *)SPIM_3_BASEADDR)
#define   SPIM_4                    ((SPI_TypeDef *)SPIM_4_BASEADDR)

#define   SPIS_1                    ((SPI_TypeDef *)SPIS_1_BASEADDR)
#define   SPIS_2                    ((SPI_TypeDef *)SPIS_2_BASEADDR)
#define   SPIS_3                    ((SPI_TypeDef *)SPIS_3_BASEADDR)
#define   SPIS_4                    ((SPI_TypeDef *)SPIS_4_BASEADDR)

/* ================================================================================ */
/* ================            SCI7816                             ================ */
/* ================================================================================ */
typedef struct
{   
	__IO u32 CON;         
	__IO u32 MODE;           
	__IO u32 STATUS;          
	__IO u32 FIFO_STATUS;     
	__IO u32 FIFO_DEPTH;     
	__IO u32 DATA;            
	__IO u32 EDC_DATA;       
	__IO u32 SBDR;            
	__IO u32 ETU_CNT;        
	__IO u32 CLK_RST;

} SCI7816_TypeDef;

#define   SCI7816                   ((SCI7816_TypeDef *)SCI7816_BASEADDR)

///* ================================================================================ */
///* ================            TIMER + BASETIMER                   ================ */
///* ================================================================================ */
typedef struct
{
		__IO u32  LOADCOUNT0;
		__IO u32  CURCOUNT;
		__IO u32  CTRL;
		__IO u32  INTCLR; 
		__IO u32  INTSTS;

} TIMER_TypeDef;

#define   TIMER_1                   ((TIMER_TypeDef *)   TIMER_1_BASEADDR)
#define   TIMER_2                   ((TIMER_TypeDef *)   TIMER_2_BASEADDR)
#define   TIMER_3                   ((TIMER_TypeDef *)   TIMER_3_BASEADDR)
#define   TIMER_4                   ((TIMER_TypeDef *)   TIMER_4_BASEADDR)
#define   BASETIMER                 ((TIMER_TypeDef *) BASETIMER_BASEADDR)

#define   TIMER_1_LOADCOUNT1        *((volatile unsigned int  *)(  TIMER_1_BASEADDR+0xb0))
#define   TIMER_2_LOADCOUNT1        *((volatile unsigned int  *)(  TIMER_1_BASEADDR+0xb4))
#define   TIMER_3_LOADCOUNT1        *((volatile unsigned int  *)(  TIMER_1_BASEADDR+0xb8))
#define   TIMER_4_LOADCOUNT1        *((volatile unsigned int  *)(  TIMER_1_BASEADDR+0xbc))
#define   BASETIMER_LOADCOUNT1      *((volatile unsigned int  *)(BASETIMER_BASEADDR+0xb0))

#define   TIMERS_INTSTS             *((volatile unsigned int  *)(  TIMER_1_BASEADDR+0xa0))
#define   TIMERS_INTCLR             *((volatile unsigned int  *)(  TIMER_1_BASEADDR+0xa4))
#define   TIMERS_RawINTSTS          *((volatile unsigned int  *)(  TIMER_1_BASEADDR+0xa8))	
#define   TIMERS_GATE               *((volatile unsigned int  *)(  TIMER_1_BASEADDR+0xd0))  //(bit1,bit0: ct,gate)*4

#define   BTIMERS_INTSTS            *((volatile unsigned int  *)(BASETIMER_BASEADDR+0xa0))
#define   BTIMERS_INTCLR            *((volatile unsigned int  *)(BASETIMER_BASEADDR+0xa4))	
#define   BTIMERS_RawINTSTS         *((volatile unsigned int  *)(BASETIMER_BASEADDR+0xa8))		
#define   BTIMERS_GATE              *((volatile unsigned int  *)(BASETIMER_BASEADDR+0xd0))  //bit1,bit0: ct,gate	

/* ================================================================================ */
/* ================            RNG                                 ================ */
/* ================================================================================ */
//#define RNG_BASEADDR          (0x40003000)
typedef struct
{
    __IO u32  CTRL;
    __IO u32  MODE;
    __IO u32  SEQ;
    __IO u32  DATA0;
    __IO u32  DATA1;

} RNG_TypeDef;

#define RNG                         ((RNG_TypeDef *)RNG_BASEADDR)

/* ================================================================================ */
/* ================            CRC                                 ================ */
/* ================================================================================ */
typedef struct
{
    __IO u32  CTRL;
    __IO u32  RESULT;
    __IO u32  RAND;
    __IO u32  FLAG; 
	       u32  RESERVED0[28];
    __IO u32  DATA;
} CRC_TypeDef;

#define CRC                         ((CRC_TypeDef *)CRC_BASEADDR)

/* ================================================================================ */
/* ================            DES                                 ================ */
/* ================================================================================ */
typedef struct
{
    __IO u32  CTRL;
	       u32  RESERVED0[2];
    __IO u32  RAND;
	       u32  RESERVED1[2];
    __IO u32  IV_L;
    __IO u32  IV_H;
    __IO u32  DATA_L;
    __IO u32  DATA_H;
    __IO u32  KEY1_L;
    __IO u32  KEY1_H;
    __IO u32  KEY2_L;
    __IO u32  KEY2_H;
    __IO u32  KEY3_L;
    __IO u32  KEY3_H;

} DES_TypeDef;

#define DES                         ((DES_TypeDef *)DES_BASEADDR)

/* ================================================================================ */
/* ================            LCD                                 ================ */
/* ================================================================================ */
typedef struct
{
	  __IO u32 LCDRAM0L;        
	  __IO u32 LCDRAM1L;
	  __IO u32 LCDRAM2L;	
	  __IO u32 LCDRAM3L;
	  __IO u32 LCDRAM4L;        
	  __IO u32 LCDRAM5L;
	  __IO u32 LCDRAM6L;	
	  __IO u32 LCDRAM7L;
	  __IO u32 LCDRAM0H;        
	  __IO u32 LCDRAM1H;
	  __IO u32 LCDRAM2H;	
	  __IO u32 LCDRAM3H;
	  __IO u32 LCDRAM4H;        
	  __IO u32 LCDRAM5H;
	  __IO u32 LCDRAM6H;	
	  __IO u32 LCDRAM7H;
	  __IO u32 LCDCR;

} LCD_TypeDef;

#define   LCD                         ((LCD_TypeDef *)LCD_BASEADDR)

/* ================================================================================ */
/* ================            RTC                                 ================ */
/* ================================================================================ */
typedef struct
{
	  __IO u32 SIXTEENOFS;        
	  __IO u32 SECOND;           
	  __IO u32 MINUTE;           
	  __IO u32 HOUR;             
	  __IO u32 DAY;              
	  __IO u32 MONTH;            
	  __IO u32 YEARL;            
	  __IO u32 YEARH;            
	  __IO u32 SIXTEENOFS_DIS;   
	  __IO u32 SECOND_DIS;       
	  __IO u32 MINUTE_DIS;       
	  __IO u32 HOUR_DIS;         		
	  __IO u32 DAY_DIS;          
	  __IO u32 MONTH_DIS;         
	  __IO u32 YEARL_DIS;         
	  __IO u32 YEARH_DIS;         		
	  __IO u32 ADJUST_INC;       
	  __IO u32 ADJUST_DEC;       
	  __IO u32 FORMAT;           
	  __IO u32 INTERVAL;
	  __IO u32 EIGHT0;
	  __IO u32 EIGHT1;		
	  __IO u32 CONFIG0;          
	  __IO u32 CONFIG1;          
	  __IO u32 PHASE;            
	  __IO u32 HOLD; 
	  __IO u32 RTCRST;		
	  __IO u32 RTCINT;

} RTC_TypeDef;

#define   RTC                       ((RTC_TypeDef *)RTC_BASEADDR)

/* ================================================================================ */
/* ================            WDT                                 ================ */
/* ================================================================================ */
typedef struct
{       
	  __IO u32 CTRL;           
	  __IO u32 TIMEOV;        
	  __IO u32 CV; 		    
	  __IO u32 RESTART; 		      
	  __IO u32 INTSTAT;         
	  __IO u32 INTCLR;

} WDT_TypeDef;

#define   WDT                       ((WDT_TypeDef *)WDT_BASEADDR)

/* ================================================================================ */
/* ================            GPIO                                ================ */
/* ================================================================================ */

typedef struct
{
	  __IO u32  Pn;
	  __IO u32  Pn_DIR;
	  __IO u32  Pn_PULSE_SEL;
	  __IO u32  Pn_EDGE_SEL; 
	  __IO u32  Pn_IE; 
	  __IO u32  Pn_IFG;
	  __IO u32  Pn_PH; 
	  __IO u32  Pn_DS;
	  __IO u32  Pn_OPENDRAIN;
	  __IO u32  Pn_SEL0;
	  __IO u32  Pn_SEL1;
	  __IO u32  Pn_SEL2; 

} PORT_TypeDef;

#define   PORT_0                    ((PORT_TypeDef *)PORT_0_BASEADDR)
#define   PORT_1                    ((PORT_TypeDef *)PORT_1_BASEADDR)
#define   PORT_2                    ((PORT_TypeDef *)PORT_2_BASEADDR)
#define   PORT_3                    ((PORT_TypeDef *)PORT_3_BASEADDR)
#define   PORT_4                    ((PORT_TypeDef *)PORT_4_BASEADDR)
#define   PORT_5                    ((PORT_TypeDef *)PORT_5_BASEADDR)
#define   PORT_6                    ((PORT_TypeDef *)PORT_6_BASEADDR)

/* ================================================================================ */
/* ================            PCA                                 ================ */
/* ================================================================================ */
typedef struct
{
	__IO u32 CCON;         
	__IO u32 CMOD;         
	__IO u32 CH;           
	__IO u32 CL;           
	__IO u32 CCAPM0;       
	__IO u32 CCAPM1;      
	__IO u32 CCAPM2;       
	__IO u32 CCAPM3;       
	__IO u32 CCAPM4;       
	__IO u32 CCAP0H;       
	__IO u32 CCAP0L;       
	__IO u32 CCAP1H;       
	__IO u32 CCAP1L;       
	__IO u32 CCAP2H;       
	__IO u32 CCAP2L;       
	__IO u32 CCAP3H;       
	__IO u32 CCAP3L;       
	__IO u32 CCAP4H;       
	__IO u32 CCAP4L;       
	__IO u32 CCAPO;             

} PCA_TypeDef;

#define   PCA_1                      ((PCA_TypeDef *)PCA_1_BASEADDR)
#define   PCA_2                      ((PCA_TypeDef *)PCA_2_BASEADDR)
#define   PCA_3                      ((PCA_TypeDef *)PCA_3_BASEADDR)
#define   PCA_4                      ((PCA_TypeDef *)PCA_4_BASEADDR)

/* ================================================================================ */
/* ================            FLASH                                ================ */
/* ================================================================================ */

typedef struct
{
    __IO u32  TNVS;
    __IO u32  TPGS;
    __IO u32  TPROG;
    __IO u32  TNVH;
    __IO u32  TRCV;
    __IO u32  TERASE;
    __IO u32  TME;
    __IO u32  TNVH1;			
    __IO u32  FLASH_CTRL;
    __IO u32  FLASH_FLAG;
         u32  RESERVED0[2];

    __IO u32  PL_SEQ;
         u32  RESERVED1[1];
    __IO u32  Flash_PL0;
    __IO u32  Flash_PL1;
    __IO u32  Flash_PL2;
    __IO u32  Flash_PL3;
    __IO u32  Flash_PL4;
    __IO u32  Flash_PL5;
    __IO u32  Flash_PL6;
    __IO u32  Flash_PL7;

} FLASH_TypeDef;

#define   FLASH                     ((FLASH_TypeDef *)EFLASH_CTRL_BASEADDR)

/* ================================================================================ */


/******************************************************************************/
/*                                                                            */
/*                       General Purpose IOs (PORT)                           */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for PORT_Px register  *****************/
#define PORT_Px_PB0          										((uint16_t)0x0001)      /*!<Px bit 0 */
#define PORT_Px_PB1          										((uint16_t)0x0002) 			/*!<Px bit 1 */
#define PORT_Px_PB2          										((uint16_t)0x0004) 			/*!<Px bit 2 */
#define PORT_Px_PB3          										((uint16_t)0x0008) 			/*!<Px bit 3 */
#define PORT_Px_PB4          										((uint16_t)0x0010) 			/*!<Px bit 4 */
#define PORT_Px_PB5          										((uint16_t)0x0020) 			/*!<Px bit 5 */
#define PORT_Px_PB6          										((uint16_t)0x0040) 			/*!<Px bit 6 */
#define PORT_Px_PB7          										((uint16_t)0x0080) 			/*!<Px bit 7 */
#define PORT_Px_PB8          										((uint16_t)0x0100) 			/*!<Px bit 8 */
#define PORT_Px_PB9          										((uint16_t)0x0200) 			/*!<Px bit 9 */
#define PORT_Px_PB10          									((uint16_t)0x0400) 			/*!<Px bit 10*/
#define PORT_Px_PB11          									((uint16_t)0x0800) 			/*!<Px bit 11 */
#define PORT_Px_PB12          									((uint16_t)0x1000) 			/*!<Px bit 12 */
#define PORT_Px_PB13          									((uint16_t)0x2000) 			/*!<Px bit 13 */
#define PORT_Px_PB14          									((uint16_t)0x4000) 			/*!<Px bit 14 */
#define PORT_Px_PB15          									((uint16_t)0x8000) 			/*!<Px bit 15 */

/*******************  Bit definition for PORT_Px_DIR register  *****************/
#define PORT_Px_DIR_0          									((uint16_t)0x0001)        	/*!<Px_DIR bit 0 */
#define PORT_Px_DIR_1          									((uint16_t)0x0002) 			/*!<Px_DIR bit 1 */
#define PORT_Px_DIR_2          									((uint16_t)0x0004) 			/*!<Px_DIR bit 2 */
#define PORT_Px_DIR_3          									((uint16_t)0x0008) 			/*!<Px_DIR bit 3 */
#define PORT_Px_DIR_4          									((uint16_t)0x0010) 			/*!<Px_DIR bit 4 */
#define PORT_Px_DIR_5          									((uint16_t)0x0020) 			/*!<Px_DIR bit 5 */
#define PORT_Px_DIR_6          									((uint16_t)0x0040) 			/*!<Px_DIR bit 6 */
#define PORT_Px_DIR_7          									((uint16_t)0x0080) 			/*!<Px_DIR bit 7 */
#define PORT_Px_DIR_8          									((uint16_t)0x0100) 			/*!<Px_DIR bit 8 */
#define PORT_Px_DIR_9          									((uint16_t)0x0200) 			/*!<Px_DIR bit 9 */
#define PORT_Px_DIR_10          								((uint16_t)0x0400) 			/*!<Px_DIR bit 10*/
#define PORT_Px_DIR_11          								((uint16_t)0x0800) 			/*!<Px_DIR bit 11 */
#define PORT_Px_DIR_12          								((uint16_t)0x1000) 			/*!<Px_DIR bit 12 */
#define PORT_Px_DIR_13          								((uint16_t)0x2000) 			/*!<Px_DIR bit 13 */
#define PORT_Px_DIR_14          								((uint16_t)0x4000) 			/*!<Px_DIR bit 14 */
#define PORT_Px_DIR_15													((uint16_t)0x8000) 			/*!<Px_DIR bit 15 */

/*******************  Bit definition for PORT_Px_LEVEL_SEL register  *****************/
#define PORT_Px_LEVEL_SEL_LEV0          				((uint32_t)0x00000003)        	
#define PORT_Px_LEVEL_SEL_LEV0_0          			((uint32_t)0x00000001)        	/*!<Px_LEVEL_SEL bit 0 */
#define PORT_Px_LEVEL_SEL_LEV0_1          			((uint32_t)0x00000002)        	/*!<Px_LEVEL_SEL bit 1 */
#define PORT_Px_LEVEL_SEL_LEV1          				((uint32_t)0x0000000C) 			
#define PORT_Px_LEVEL_SEL_LEV1_0          			((uint32_t)0x00000004)        	/*!<Px_LEVEL_SEL bit 2 */
#define PORT_Px_LEVEL_SEL_LEV1_1          			((uint32_t)0x00000008)        	/*!<Px_LEVEL_SEL bit 3 */
#define PORT_Px_LEVEL_SEL_LEV2          				((uint32_t)0x00000030) 			
#define PORT_Px_LEVEL_SEL_LEV2_0          			((uint32_t)0x00000010)        	/*!<Px_LEVEL_SEL bit 4 */
#define PORT_Px_LEVEL_SEL_LEV2_1          			((uint32_t)0x00000020)        	/*!<Px_LEVEL_SEL bit 5 */
#define PORT_Px_LEVEL_SEL_LEV3          				((uint32_t)0x000000C0) 			
#define PORT_Px_LEVEL_SEL_LEV3_0          			((uint32_t)0x00000040)        	/*!<Px_LEVEL_SEL bit 6 */
#define PORT_Px_LEVEL_SEL_LEV3_1          			((uint32_t)0x00000080)        	/*!<Px_LEVEL_SEL bit 7 */
#define PORT_Px_LEVEL_SEL_LEV4          				((uint32_t)0x00000300) 			
#define PORT_Px_LEVEL_SEL_LEV4_0          			((uint32_t)0x00000100)        	/*!<Px_LEVEL_SEL bit 8 */
#define PORT_Px_LEVEL_SEL_LEV4_1          			((uint32_t)0x00000200)        	/*!<Px_LEVEL_SEL bit 9 */
#define PORT_Px_LEVEL_SEL_LEV5          				((uint32_t)0x00000C00) 			
#define PORT_Px_LEVEL_SEL_LEV5_0          			((uint32_t)0x00000400)        	/*!<Px_LEVEL_SEL bit 10 */
#define PORT_Px_LEVEL_SEL_LEV5_1          			((uint32_t)0x00000800)        	/*!<Px_LEVEL_SEL bit 11 */
#define PORT_Px_LEVEL_SEL_LEV6          				((uint32_t)0x00003000) 			
#define PORT_Px_LEVEL_SEL_LEV6_0          			((uint32_t)0x00001000)        	/*!<Px_LEVEL_SEL bit 12 */
#define PORT_Px_LEVEL_SEL_LEV6_1          			((uint32_t)0x00002000)        	/*!<Px_LEVEL_SEL bit 13 */
#define PORT_Px_LEVEL_SEL_LEV7         					((uint32_t)0x0000C000) 		
#define PORT_Px_LEVEL_SEL_LEV7_0          			((uint32_t)0x00004000)        	/*!<Px_LEVEL_SEL bit 14 */
#define PORT_Px_LEVEL_SEL_LEV7_1          			((uint32_t)0x00008000)        	/*!<Px_LEVEL_SEL bit 15 */
#define PORT_Px_LEVEL_SEL_LEV8          				((uint32_t)0x00030000) 			
#define PORT_Px_LEVEL_SEL_LEV8_0          			((uint32_t)0x00010000)        	/*!<Px_LEVEL_SEL bit 16 */
#define PORT_Px_LEVEL_SEL_LEV8_1          			((uint32_t)0x00020000)        	/*!<Px_LEVEL_SEL bit 17 */
#define PORT_Px_LEVEL_SEL_LEV9         					((uint32_t)0x000C0000) 			
#define PORT_Px_LEVEL_SEL_LEV9_0          			((uint32_t)0x00040000)        	/*!<Px_LEVEL_SEL bit 18 */
#define PORT_Px_LEVEL_SEL_LEV9_1          			((uint32_t)0x00080000)        	/*!<Px_LEVEL_SEL bit 19 */
#define PORT_Px_LEVEL_SEL_LEV10          				((uint32_t)0x00300000)			
#define PORT_Px_LEVEL_SEL_LEV10_0          			((uint32_t)0x00100000)        	/*!<Px_LEVEL_SEL bit 20 */
#define PORT_Px_LEVEL_SEL_LEV10_1          			((uint32_t)0x00200000)        	/*!<Px_LEVEL_SEL bit 21 */
#define PORT_Px_LEVEL_SEL_LEV11          				((uint32_t)0x00C00000) 			
#define PORT_Px_LEVEL_SEL_LEV11_0          			((uint32_t)0x00400000)        	/*!<Px_LEVEL_SEL bit 22 */
#define PORT_Px_LEVEL_SEL_LEV11_1          			((uint32_t)0x00800000)        	/*!<Px_LEVEL_SEL bit 23 */
#define PORT_Px_LEVEL_SEL_LEV12          				((uint32_t)0x03000000) 			
#define PORT_Px_LEVEL_SEL_LEV12_0          			((uint32_t)0x01000000)        	/*!<Px_LEVEL_SEL bit 24 */
#define PORT_Px_LEVEL_SEL_LEV12_1          			((uint32_t)0x02000000)        	/*!<Px_LEVEL_SEL bit 25 */
#define PORT_Px_LEVEL_SEL_LEV13          				((uint32_t)0x0C000000) 			
#define PORT_Px_LEVEL_SEL_LEV13_0          			((uint32_t)0x04000000)        	/*!<Px_LEVEL_SEL bit 26 */
#define PORT_Px_LEVEL_SEL_LEV13_1          			((uint32_t)0x08000000)        	/*!<Px_LEVEL_SEL bit 27 */
#define PORT_Px_LEVEL_SEL_LEV14          				((uint32_t)0x30000000) 			
#define PORT_Px_LEVEL_SEL_LEV14_0          			((uint32_t)0x10000000)        	/*!<Px_LEVEL_SEL bit 28 */
#define PORT_Px_LEVEL_SEL_LEV14_1          			((uint32_t)0x20000000)        	/*!<Px_LEVEL_SEL bit 29 */
#define PORT_Px_LEVEL_SEL_LEV15         				((uint32_t)0xC0000000) 		
#define PORT_Px_LEVEL_SEL_LEV15_0          			((uint32_t)0x40000000)        	/*!<Px_LEVEL_SEL bit 31 */
#define PORT_Px_LEVEL_SEL_LEV15_1          			((uint32_t)0x80000000)        	/*!<Px_LEVEL_SEL bit 32 */

/*******************  Bit definition for PORT_Px_EDGE_SEL register  *****************/
#define PORT_Px_EDGE_SEL_EDGE0          				((uint32_t)0x00000003)        	
#define PORT_Px_EDGE_SEL_EDGE0_0          			((uint32_t)0x00000001)        	/*!<Px_EDGE_SEL bit 0 */
#define PORT_Px_EDGE_SEL_EDGE0_1          			((uint32_t)0x00000002)        	/*!<Px_EDGE_SEL bit 1 */
#define PORT_Px_EDGE_SEL_EDGE1          				((uint32_t)0x0000000C) 			
#define PORT_Px_EDGE_SEL_EDGE1_0          			((uint32_t)0x00000004)        	/*!<Px_EDGE_SEL bit 2 */
#define PORT_Px_EDGE_SEL_EDGE1_1          			((uint32_t)0x00000008)        	/*!<Px_EDGE_SEL bit 3 */
#define PORT_Px_EDGE_SEL_EDGE2          				((uint32_t)0x00000030) 			
#define PORT_Px_EDGE_SEL_EDGE2_0          			((uint32_t)0x00000010)        	/*!<Px_EDGE_SEL bit 4 */
#define PORT_Px_EDGE_SEL_EDGE2_1          			((uint32_t)0x00000020)        	/*!<Px_EDGE_SEL bit 5 */
#define PORT_Px_EDGE_SEL_EDGE3          				((uint32_t)0x000000C0) 			
#define PORT_Px_EDGE_SEL_EDGE3_0          			((uint32_t)0x00000040)        	/*!<Px_EDGE_SEL bit 6 */
#define PORT_Px_EDGE_SEL_EDGE3_1          			((uint32_t)0x00000080)        	/*!<Px_EDGE_SEL bit 7 */
#define PORT_Px_EDGE_SEL_EDGE4          				((uint32_t)0x00000300) 			
#define PORT_Px_EDGE_SEL_EDGE4_0          			((uint32_t)0x00000100)        	/*!<Px_EDGE_SEL bit 8 */
#define PORT_Px_EDGE_SEL_EDGE4_1          			((uint32_t)0x00000200)        	/*!<Px_EDGE_SEL bit 9 */
#define PORT_Px_EDGE_SEL_EDGE5          				((uint32_t)0x00000C00) 			
#define PORT_Px_EDGE_SEL_EDGE5_0      					((uint32_t)0x00000400)        	/*!<Px_EDGE_SEL bit 10 */
#define PORT_Px_EDGE_SEL_EDGE5_1          			((uint32_t)0x00000800)        	/*!<Px_EDGE_SEL bit 11 */
#define PORT_Px_EDGE_SEL_EDGE6          				((uint32_t)0x00003000) 			
#define PORT_Px_EDGE_SEL_EDGE6_0       					((uint32_t)0x00001000)        	/*!<Px_EDGE_SEL bit 12 */
#define PORT_Px_EDGE_SEL_EDGE6_1          		  ((uint32_t)0x00002000)        	/*!<Px_EDGE_SEL bit 13 */
#define PORT_Px_EDGE_SEL_EDGE7         					((uint32_t)0x0000C000) 			
#define PORT_Px_EDGE_SEL_EDGE7_0          			((uint32_t)0x00004000)        	/*!<Px_EDGE_SEL bit 14 */
#define PORT_Px_EDGE_SEL_EDGE7_1          			((uint32_t)0x00008000)        	/*!<Px_EDGE_SEL bit 15 */
#define PORT_Px_EDGE_SEL_EDGE8          				((uint32_t)0x00030000) 			
#define PORT_Px_EDGE_SEL_EDGE8_0          			((uint32_t)0x00010000)        	/*!<Px_EDGE_SEL bit 16 */
#define PORT_Px_EDGE_SEL_EDGE8_1          			((uint32_t)0x00020000)        	/*!<Px_EDGE_SEL bit 17 */
#define PORT_Px_EDGE_SEL_EDGE9         					((uint32_t)0x000C0000) 			
#define PORT_Px_EDGE_SEL_EDGE9_0          			((uint32_t)0x00040000)        	/*!<Px_EDGE_SEL bit 18 */
#define PORT_Px_EDGE_SEL_EDGE9_1          			((uint32_t)0x00080000)        	/*!<Px_EDGE_SEL bit 19 */
#define PORT_Px_EDGE_SEL_EDGE10          				((uint32_t)0x00300000)		
#define PORT_Px_EDGE_SEL_EDGE10_0          			((uint32_t)0x00100000)        	/*!<Px_EDGE_SEL bit 20 */
#define PORT_Px_EDGE_SEL_EDGE10_1          			((uint32_t)0x00200000)        	/*!<Px_EDGE_SEL bit 21 */
#define PORT_Px_EDGE_SEL_EDGE11          				((uint32_t)0x00C00000) 			
#define PORT_Px_EDGE_SEL_EDGE11_0          			((uint32_t)0x00400000)        	/*!<Px_EDGE_SEL bit 22 */
#define PORT_Px_EDGE_SEL_EDGE11_1          			((uint32_t)0x00800000)        	/*!<Px_EDGE_SEL bit 23 */
#define PORT_Px_EDGE_SEL_EDGE12          				((uint32_t)0x03000000) 			
#define PORT_Px_EDGE_SEL_EDGE12_0          			((uint32_t)0x01000000)        	/*!<Px_EDGE_SEL bit 24 */
#define PORT_Px_EDGE_SEL_EDGE12_1          			((uint32_t)0x02000000)        	/*!<Px_EDGE_SEL bit 25 */
#define PORT_Px_EDGE_SEL_EDGE13          				((uint32_t)0x0C000000) 		
#define PORT_Px_EDGE_SEL_EDGE13_0          			((uint32_t)0x04000000)        	/*!<Px_EDGE_SEL bit 26 */
#define PORT_Px_EDGE_SEL_EDGE13_1          			((uint32_t)0x08000000)        	/*!<Px_EDGE_SEL bit 27 */
#define PORT_Px_EDGE_SEL_EDGE14          				((uint32_t)0x30000000) 			
#define PORT_Px_EDGE_SEL_EDGE14_0          			((uint32_t)0x10000000)        	/*!<Px_EDGE_SEL bit 28 */
#define PORT_Px_EDGE_SEL_EDGE14_1          			((uint32_t)0x20000000)        	/*!<Px_EDGE_SEL bit 29 */
#define PORT_Px_EDGE_SEL_EDGE15         				((uint32_t)0xC0000000) 			
#define PORT_Px_EDGE_SEL_EDGE15_0          			((uint32_t)0x40000000)        	/*!<Px_EDGE_SEL bit 30 */
#define PORT_Px_EDGE_SEL_EDGE_1          				((uint32_t)0x80000000)        	/*!<Px_EDGE_SEL bit 31 */

/*******************  Bit definition for PORT_Px_IE register  *****************/
#define PORT_Px_IE_0          									((uint16_t)0x0001)        	/*!<Px_IE bit 0 */
#define PORT_Px_IE_1          									((uint16_t)0x0002) 			/*!<Px_IE bit 1 */
#define PORT_Px_IE_2          									((uint16_t)0x0004) 			/*!<Px_IE bit 2 */
#define PORT_Px_IE_3          									((uint16_t)0x0008) 			/*!<Px_IE bit 3 */
#define PORT_Px_IE_4          									((uint16_t)0x0010) 			/*!<Px_IE bit 4 */
#define PORT_Px_IE_5          									((uint16_t)0x0020) 			/*!<Px_IE bit 5 */
#define PORT_Px_IE_6          									((uint16_t)0x0040) 			/*!<Px_IE bit 6 */
#define PORT_Px_IE_7          									((uint16_t)0x0080) 			/*!<Px_IE bit 7 */
#define PORT_Px_IE_8          									((uint16_t)0x0100) 			/*!<Px_IE bit 8 */
#define PORT_Px_IE_9          									((uint16_t)0x0200) 			/*!<Px_IE bit 9 */
#define PORT_Px_IE_10          									((uint16_t)0x0400) 			/*!<Px_IE bit 10*/
#define PORT_Px_IE_11          									((uint16_t)0x0800) 			/*!<Px_IE bit 11 */
#define PORT_Px_IE_12          									((uint16_t)0x1000) 			/*!<Px_IE bit 12 */
#define PORT_Px_IE_13          									((uint16_t)0x2000) 			/*!<Px_IE bit 13 */
#define PORT_Px_IE_14          									((uint16_t)0x4000) 			/*!<Px_IE bit 14 */
#define PORT_Px_IE_15          									((uint16_t)0x8000) 			/*!<Px_IE bit 15 */

/*******************  Bit definition for PORT_Px_IFG register  *****************/
#define PORT_Px_IFG_0          									((uint16_t)0x0001)        	/*!<Px_IFG bit 0 */
#define PORT_Px_IFG_1          									((uint16_t)0x0002) 			/*!<Px_IFG bit 1 */
#define PORT_Px_IFG_2          									((uint16_t)0x0004) 			/*!<Px_IFG bit 2 */
#define PORT_Px_IFG_3          									((uint16_t)0x0008) 			/*!<Px_IFG bit 3 */
#define PORT_Px_IFG_4          									((uint16_t)0x0010) 			/*!<Px_IFG bit 4 */
#define PORT_Px_IFG_5          									((uint16_t)0x0020) 			/*!<Px_IFG bit 5 */
#define PORT_Px_IFG_6          									((uint16_t)0x0040) 			/*!<Px_IFG bit 6 */
#define PORT_Px_IFG_7          									((uint16_t)0x0080) 			/*!<Px_IFG bit 7 */
#define PORT_Px_IFG_8          									((uint16_t)0x0100) 			/*!<Px_IFG bit 8 */
#define PORT_Px_IFG_9          									((uint16_t)0x0200) 			/*!<Px_IFG bit 9 */
#define PORT_Px_IFG_10          								((uint16_t)0x0400) 			/*!<Px_IFG bit 10*/
#define PORT_Px_IFG_11          								((uint16_t)0x0800) 			/*!<Px_IFG bit 11 */
#define PORT_Px_IFG_12          								((uint16_t)0x1000) 			/*!<Px_IFG bit 12 */
#define PORT_Px_IFG_13          								((uint16_t)0x2000) 			/*!<Px_IFG bit 13 */
#define PORT_Px_IFG_14          								((uint16_t)0x4000) 			/*!<Px_IFG bit 14 */
#define PORT_Px_IFG_15          								((uint16_t)0x8000) 			/*!<Px_IFG bit 15 */

/*******************  Bit definition for PORT_Px_PH register  *****************/
#define PORT_Px_PH_0          									((uint16_t)0x0001)        	/*!<Px_PH bit 0 */
#define PORT_Px_PH_1          									((uint16_t)0x0002) 			/*!<Px_PH bit 1 */
#define PORT_Px_PH_2          									((uint16_t)0x0004) 			/*!<Px_PH bit 2 */
#define PORT_Px_PH_3          									((uint16_t)0x0008) 			/*!<Px_PH bit 3 */
#define PORT_Px_PH_4          									((uint16_t)0x0010) 			/*!<Px_PH bit 4 */
#define PORT_Px_PH_5          									((uint16_t)0x0020) 			/*!<Px_PH bit 5 */
#define PORT_Px_PH_6          									((uint16_t)0x0040) 			/*!<Px_PH bit 6 */
#define PORT_Px_PH_7          									((uint16_t)0x0080) 			/*!<Px_PH bit 7 */
#define PORT_Px_PH_8          									((uint16_t)0x0100) 			/*!<Px_PH bit 8 */
#define PORT_Px_PH_9          									((uint16_t)0x0200) 			/*!<Px_PH bit 9 */
#define PORT_Px_PH_10          									((uint16_t)0x0400) 			/*!<Px_PH bit 10*/
#define PORT_Px_PH_11          									((uint16_t)0x0800) 			/*!<Px_PH bit 11 */
#define PORT_Px_PH_12          									((uint16_t)0x1000) 			/*!<Px_PH bit 12 */
#define PORT_Px_PH_13          									((uint16_t)0x2000) 			/*!<Px_PH bit 13 */
#define PORT_Px_PH_14          									((uint16_t)0x4000) 			/*!<Px_PH bit 14 */
#define PORT_Px_PH_15          									((uint16_t)0x8000) 			/*!<Px_PH bit 15 */

/*******************  Bit definition for PORT_Px_DS register  *****************/
#define PORT_Px_DS_0          									((uint16_t)0x0001)        	/*!<Px_DS bit 0 */
#define PORT_Px_DS_1          									((uint16_t)0x0002) 			/*!<Px_DS bit 1 */
#define PORT_Px_DS_2          									((uint16_t)0x0004) 			/*!<Px_DS bit 2 */
#define PORT_Px_DS_3          									((uint16_t)0x0008) 			/*!<Px_DS bit 3 */
#define PORT_Px_DS_4          									((uint16_t)0x0010) 			/*!<Px_DS bit 4 */
#define PORT_Px_DS_5          									((uint16_t)0x0020) 			/*!<Px_DS bit 5 */
#define PORT_Px_DS_6          									((uint16_t)0x0040) 			/*!<Px_DS bit 6 */
#define PORT_Px_DS_7          									((uint16_t)0x0080) 			/*!<Px_DS bit 7 */
#define PORT_Px_DS_8          									((uint16_t)0x0100) 			/*!<Px_DS bit 8 */
#define PORT_Px_DS_9          									((uint16_t)0x0200) 			/*!<Px_DS bit 9 */
#define PORT_Px_DS_10          									((uint16_t)0x0400) 			/*!<Px_DS bit 10*/
#define PORT_Px_DS_11          									((uint16_t)0x0800) 			/*!<Px_DS bit 11 */
#define PORT_Px_DS_12          									((uint16_t)0x1000) 			/*!<Px_DS bit 12 */
#define PORT_Px_DS_13          									((uint16_t)0x2000) 			/*!<Px_DS bit 13 */
#define PORT_Px_DS_14          									((uint16_t)0x4000) 			/*!<Px_DS bit 14 */
#define PORT_Px_DS_15          									((uint16_t)0x8000) 			/*!<Px_DS bit 15 */

/*******************  Bit definition for PORT_Px_OPENDRAIN register  *****************/
#define PORT_Px_OPENDRAIN_0          						((uint16_t)0x0001)        	/*!<Px_OPENDRAIN bit 0 */
#define PORT_Px_OPENDRAIN_1          						((uint16_t)0x0002) 			/*!<Px_OPENDRAIN bit 1 */
#define PORT_Px_OPENDRAIN_2          						((uint16_t)0x0004) 			/*!<Px_OPENDRAIN bit 2 */
#define PORT_Px_OPENDRAIN_3          						((uint16_t)0x0008) 			/*!<Px_OPENDRAIN bit 3 */
#define PORT_Px_OPENDRAIN_4          						((uint16_t)0x0010) 			/*!<Px_OPENDRAIN bit 4 */
#define PORT_Px_OPENDRAIN_5          						((uint16_t)0x0020) 			/*!<Px_OPENDRAIN bit 5 */
#define PORT_Px_OPENDRAIN_6          						((uint16_t)0x0040) 			/*!<Px_OPENDRAIN bit 6 */
#define PORT_Px_OPENDRAIN_7          						((uint16_t)0x0080) 			/*!<Px_OPENDRAIN bit 7 */
#define PORT_Px_OPENDRAIN_8          						((uint16_t)0x0100) 			/*!<Px_OPENDRAIN bit 8 */
#define PORT_Px_OPENDRAIN_9          						((uint16_t)0x0200) 			/*!<Px_OPENDRAIN bit 9 */
#define PORT_Px_OPENDRAIN_10          					((uint16_t)0x0400) 			/*!<Px_OPENDRAIN bit 10*/
#define PORT_Px_OPENDRAIN_11          					((uint16_t)0x0800) 			/*!<Px_OPENDRAIN bit 11 */
#define PORT_Px_OPENDRAIN_12          					((uint16_t)0x1000) 			/*!<Px_OPENDRAIN bit 12 */
#define PORT_Px_OPENDRAIN_13          					((uint16_t)0x2000) 			/*!<Px_OPENDRAIN bit 13 */
#define PORT_Px_OPENDRAIN_14          					((uint16_t)0x4000) 			/*!<Px_OPENDRAIN bit 14 */
#define PORT_Px_OPENDRAIN_15          					((uint16_t)0x8000) 			/*!<Px_OPENDRAIN bit 15 */

/*******************  Bit definition for PORT_Px_SEL0 register  *****************/
#define PORT_Px_SLE0_0          								((uint16_t)0x0001)        	/*!<Px_SEL0 bit 0 */
#define PORT_Px_SEL0_1          								((uint16_t)0x0002) 			/*!<Px_SEL0 bit 1 */
#define PORT_Px_SEL0_2          								((uint16_t)0x0004) 			/*!<Px_SEL0 bit 2 */
#define PORT_Px_SEL0_3          								((uint16_t)0x0008) 			/*!<Px_SEL0 bit 3 */
#define PORT_Px_SEL0_4          								((uint16_t)0x0010) 			/*!<Px_SEL0 bit 4 */
#define PORT_Px_SEL0_5          								((uint16_t)0x0020) 			/*!<Px_SEL0 bit 5 */
#define PORT_Px_SEL0_6          								((uint16_t)0x0040) 			/*!<Px_SEL0 bit 6 */
#define PORT_Px_SEL0_7          								((uint16_t)0x0080) 			/*!<Px_SEL0 bit 7 */
#define PORT_Px_SEL0_8          								((uint16_t)0x0100) 			/*!<Px_SEL0 bit 8 */
#define PORT_Px_SEL0_9          								((uint16_t)0x0200) 			/*!<Px_SEL0 bit 9 */
#define PORT_Px_SEL0_10          								((uint16_t)0x0400) 			/*!<Px_SEL0 bit 10*/
#define PORT_Px_SEL0_11          								((uint16_t)0x0800) 			/*!<Px_SEL0 bit 11 */
#define PORT_Px_SEL0_12          	          		((uint16_t)0x1000) 			/*!<Px_SEL0 bit 12 */
#define PORT_Px_SEL0_13          	              ((uint16_t)0x2000) 			/*!<Px_SEL0 bit 13 */
#define PORT_Px_SEL0_14          	              ((uint16_t)0x4000) 			/*!<Px_SEL0 bit 14 */
#define PORT_Px_SEL0_15          	              ((uint16_t)0x8000) 			/*!<Px_SEL0 bit 15 */

/*******************  Bit definition for PORT_Px_SEL1 register  *****************/
#define PORT_Px_SEL1                            ((uint32_t)0xFFFFFF)

/*******************  Bit definition for PORT_Px_SEL2 register  *****************/
#define PORT_Px_SEL2                            ((uint16_t)0x1FF)

/******************************************************************************/
/*                                                                            */
/*                       CMU                                                  */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for CMU_SYSCLK0 register  *****************/
#define CMU_SYSCLK0_IRC16M_EN                   ((uint16_t)0x1 << 0)
#define CMU_SYSCLK0_XHF_EN                      ((uint16_t)0x1 << 1)
#define CMU_SYSCLK0_IRC38K_EN                   ((uint16_t)0x1 << 2)
#define CMU_SYSCLK0_XLF_EN                      ((uint16_t)0x1 << 3)
#define CMU_SYSCLK0_SYSCLK_SEL                  ((uint16_t)0x3 << 4)
#define CMU_SYSCLK0_AHB_CLK_DIV                 ((uint16_t)0x7 << 6)
#define CMU_SYSCLK0_APB_CLK_DIV                 ((uint16_t)0x3 << 9)

#define CMU_SYSCLK0_APB_CLK_DIV_DIV1          	((uint16_t)0x0 << 9)
#define CMU_SYSCLK0_APB_CLK_DIV_DIV2          	((uint16_t)0x1 << 9)
#define CMU_SYSCLK0_APB_CLK_DIV_DIV4          	((uint16_t)0x2 << 9)
#define CMU_SYSCLK0_APB_CLK_DIV_DIV8          	((uint16_t)0x3 << 9)

#define CMU_SYSCLK0_AHB_CLK_DIV_DIV1            ((uint16_t)0x0 << 6)
#define CMU_SYSCLK0_AHB_CLK_DIV_DIV2            ((uint16_t)0x1 << 6)
#define CMU_SYSCLK0_AHB_CLK_DIV_DIV4            ((uint16_t)0x2 << 6)
#define CMU_SYSCLK0_AHB_CLK_DIV_DIV8            ((uint16_t)0x3 << 6)
#define CMU_SYSCLK0_AHB_CLK_DIV_DIV16           ((uint16_t)0x4 << 6)
#define CMU_SYSCLK0_AHB_CLK_DIV_DIV32           ((uint16_t)0x5 << 6)
#define CMU_SYSCLK0_AHB_CLK_DIV_DIV64           ((uint16_t)0x6 << 6)
#define CMU_SYSCLK0_AHB_CLK_DIV_DIV128          ((uint16_t)0x7 << 6)

#define CMU_SYSCLK0_SYSCLK_SEL_IRC16M           ((uint16_t)0x0 << 4)
#define CMU_SYSCLK0_SYSCLK_SEL_XHFOSC			      ((uint16_t)0x1 << 4)
#define CMU_SYSCLK0_SYSCLK_SEL_IRC38K			      ((uint16_t)0x2 << 4)
#define CMU_SYSCLK0_SYSCLK_SEL_XLFOSC			      ((uint16_t)0x3 << 4)

#define CMU_SYSCLK0_XLF_EN_LSEOFF               ((uint16_t)0x0 << 3)
#define CMU_SYSCLK0_XLF_EN_LSEON				        ((uint16_t)0x1 << 3)

#define CMU_SYSCLK0_IRC38K_EN_LSIOFF			      ((uint16_t)0x0 << 2)
#define CMU_SYSCLK0_IRC38K_EN_LSION				      ((uint16_t)0x1 << 2)

#define CMU_SYSCLK0_XHF_EN_HSEOFF				        ((uint16_t)0x0 << 1)
#define CMU_SYSCLK0_XHF_EN_HSEON				        ((uint16_t)0x1 << 1)

#define CMU_SYSCLK0_IRC16M_EN_HSIOFF			      ((uint16_t)0x0 << 0)
#define CMU_SYSCLK0_IRC16M_EN_HSION				      ((uint16_t)0x1 << 0)

/*******************  Bit definition for CMU_SYSCLK1 register  *****************/
#define CMU_SYSCLK1_IRC40K_EN                   ((uint16_t)0x1 << 8)
#define CMU_SYSCLK1_LPUART_CS                   ((uint16_t)0x1 << 7)
#define CMU_SYSCLK1_LCD_CS                   	  ((uint16_t)0x1 << 6)
#define CMU_SYSCLK1_WDT_CS                   	  ((uint16_t)0x3 << 4)
#define CMU_SYSCLK1_BASETM_CS                   ((uint16_t)0x1 << 3)
#define CMU_SYSCLK1_RTC_CS                   	  ((uint16_t)0x1 << 2)
#define CMU_SYSCLK1_RAM_PAR_EN                  ((uint16_t)0x1 << 1)
#define CMU_SYSCLK1_LOOKUP_EN                   ((uint16_t)0x1)

#define CMU_SYSCLK1_IRC40K_ENOFF                ((uint16_t)0x0 << 8)
#define CMU_SYSCLK1_IRC40K_ENON 				        ((uint16_t)0x1 << 8)

#define CMU_SYSCLK1_LPUART_CS_IRC38K 		        ((uint16_t)0x0 << 7)
#define CMU_SYSCLK1_LPUART_CS_LSE 				      ((uint16_t)0x1 << 7)

#define CMU_SYSCLK1_LCD_CS_IRC38K 		    	    ((uint16_t)0x0 << 6)
#define CMU_SYSCLK1_LCD_CS_LSE 					        ((uint16_t)0x1 << 6)

#define CMU_SYSCLK1_WDT_CS_IRC40K 				      ((uint16_t)0x0 << 4)
#define CMU_SYSCLK1_WDT_CS_LSE 					        ((uint16_t)0x2 << 4)
#define CMU_SYSCLK1_WDT_CS_IRC38K 		    	    ((uint16_t)0x3 << 4)

#define CMU_SYSCLK1_BASETM_CS_IRC38K 		        ((uint16_t)0x0 << 3)
#define CMU_SYSCLK1_BASETM_CS_LSE 				      ((uint16_t)0x1 << 3)

#define CMU_SYSCLK1_RTC_CS_IRC38K 		    	    ((uint16_t)0x0 << 2)
#define CMU_SYSCLK1_RTC_CS_LSE 					        ((uint16_t)0x1 << 2)

/*******************  Bit definition for CMU_PERI_CLK0 register  *****************/
#define CMU_PERI_CLK0_RNG_EN                    ((uint32_t)0x1 << 29)
#define CMU_PERI_CLK0_DES_EN   					        ((uint32_t)0x1 << 27)
#define CMU_PERI_CLK0_ADC_EN					          ((uint32_t)0x1 << 26)
#define CMU_PERI_CLK0_BUZZER_EN					        ((uint32_t)0x1 << 25)
#define CMU_PERI_CLK0_CRC_EN					          ((uint32_t)0x1 << 23)
#define CMU_PERI_CLK0_DMA_EN					          ((uint32_t)0x1 << 22)
#define CMU_PERI_CLK0_FLASH_EN					        ((uint32_t)0x1 << 21)
#define CMU_PERI_CLK0_PCA4_EN					          ((uint32_t)0x1 << 20)
#define CMU_PERI_CLK0_PCA3_EN					          ((uint32_t)0x1 << 19)
#define CMU_PERI_CLK0_PCA2_EN					          ((uint32_t)0x1 << 18)
#define CMU_PERI_CLK0_PCA1_EN					          ((uint32_t)0x1 << 17)
#define CMU_PERI_CLK0_TIMER4_EN					        ((uint32_t)0x1 << 16)
#define CMU_PERI_CLK0_TIMER3_EN					        ((uint32_t)0x1 << 15)
#define CMU_PERI_CLK0_TIMER2_EN					        ((uint32_t)0x1 << 14)
#define CMU_PERI_CLK0_TIMER1_EN					        ((uint32_t)0x1 << 13)
#define CMU_PERI_CLK0_SCI7816_EN				        ((uint32_t)0x1 << 12)
#define CMU_PERI_CLK0_I2C2_EN					          ((uint32_t)0x1 << 11)
#define CMU_PERI_CLK0_I2C1_EN					          ((uint32_t)0x1 << 10)
#define CMU_PERI_CLK0_SPI4_EN					          ((uint32_t)0x1 << 9)
#define CMU_PERI_CLK0_SPI3_EN					          ((uint32_t)0x1 << 8)
#define CMU_PERI_CLK0_SPI2_EN					          ((uint32_t)0x1 << 7)
#define CMU_PERI_CLK0_SPI1_EN					          ((uint32_t)0x1 << 6)
#define CMU_PERI_CLK0_UART6_EN					        ((uint32_t)0x1 << 5)
#define CMU_PERI_CLK0_UART5_EN					        ((uint32_t)0x1 << 4)
#define CMU_PERI_CLK0_UART4_EN					        ((uint32_t)0x1 << 3)
#define CMU_PERI_CLK0_UART3_EN					        ((uint32_t)0x1 << 2)
#define CMU_PERI_CLK0_UART2_EN					        ((uint32_t)0x1 << 1)
#define CMU_PERI_CLK0_UART1_EN					        ((uint32_t)0x1 << 0)

/*******************  Bit definition for CMU_PERI_CLK1 register  *****************/
#define CMU_PERI_CLK1_LCD_EN					          ((uint8_t)0x1 << 5)
#define CMU_PERI_CLK1_WDT_EN					          ((uint8_t)0x1 << 4)
#define CMU_PERI_CLK1_BASETM_EN					        ((uint8_t)0x1 << 3)
#define CMU_PERI_CLK1_RTC_EN					          ((uint8_t)0x1 << 2)
#define CMU_PERI_CLK1_PORT_EN					          ((uint8_t)0x1 << 1)
#define CMU_PERI_CLK1_BKRAM_EN					        ((uint8_t)0x1 << 0)

/*******************  Bit definition for CMU_IRC16M_CTRL register  *****************/
#define CMU_IRC16M_CTRL_IRC16M_STABLE           ((uint16_t)0x1 << 8)
#define CMU_IRC16M_CTRL_IRC16M_TRIM             ((uint16_t)0xFF << 0)

/*******************  Bit definition for CMU_XHF_CTRL register  *****************/
#define CMU_XHF_CTRL_XHF_STABLE   			        ((uint8_t)0x1 << 5)
#define CMU_XHF_CTRL_XHF_STARTUP                ((uint8_t)0x3 << 3)
#define CMU_XHF_CTRL_XHF_DRIVER                 ((uint8_t)0x7 << 0)

/*******************  Bit definition for CMU_IRC38K_CTRL register  *****************/
#define CMU_IRC38K_CTRL_IRC38K_STABLE           ((uint16_t)0x1 << 8)
#define CMU_IRC38K_CTRL_IRC38K_STARTUP          ((uint16_t)0x3 << 6)
#define CMU_IRC38K_CTRL_IRC38K_TRIM             ((uint16_t)0x3F << 0)

/*******************  Bit definition for CMU_XLF_CTRL register  *****************/
#define CMU_XLF_CTRL_XLF_STABLE                 ((uint8_t)0x1 << 6)
#define CMU_XLF_CTRL_XLF_STARTUP                ((uint8_t)0x3 << 4)
#define CMU_XLF_CTRL_XLF_DRIVER                 ((uint8_t)0xF << 0)

/******************************************************************************/
/*                                                                            */
/*                                SYSTICK                                     */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for SYSTICK_TIMER register  *****************/
#define SYSTICK_TIMER_CLK_SEL                   ((uint32_t)0x3 << 26)
#define SYSTICK_TIMER_NOREF                     ((uint32_t)0x1 << 25)
#define SYSTICK_TIMER_SKEW                      ((uint32_t)0x1 << 24)
#define SYSTICK_TIMER_STCALIB                   ((uint32_t)0xFFFFFF << 0)

/******************************************************************************/
/*                                                                            */
/*                                UART                                        */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for UART_RXR register  *****************/
#define UART_RXR                                ((uint8_t)0xFF << 0)

/*******************  Bit definition for UART_TXR register  *****************/
#define UART_TXR                                ((uint8_t)0xFF << 0)

/*******************  Bit definition for UART_BDH register  *****************/
#define UART_BDH                                ((uint8_t)0xFF << 0)

/*******************  Bit definition for UART_BDL register  *****************/
#define UART_BDL                                ((uint8_t)0xFF << 0)

/*******************  Bit definition for UART_INTENR register  *****************/
#define UART_INTENR_PTXRE                       ((uint8_t)0x1 << 7)
#define UART_INTENR_DSIE                        ((uint8_t)0x1 << 3)
#define UART_INTENR_LSIE                        ((uint8_t)0x1 << 2)
#define UART_INTENR_TXREE                       ((uint8_t)0x1 << 1)
#define UART_INTENR_RDAIE                       ((uint8_t)0x1 << 0)

/*******************  Bit definition for UART_INTIDR register  *****************/
#define UART_INTIDR_FIFOME                      ((uint8_t)0x3 << 6)
#define UART_INTIDR_INIDR                       ((uint8_t)0xF << 0)

/*******************  Bit definition for UART_FIFOCR register  *****************/
#define UART_FIFOCR_RVTR                        ((uint8_t)0x3 << 6)
#define UART_FIFOCR_TXTR                        ((uint8_t)0x3 << 4)
#define UART_FIFOCR_TXFIFORST                   ((uint8_t)0x1 << 2)
#define UART_FIFOCR_RXFIFORST                   ((uint8_t)0x1 << 1)
#define UART_FIFOCR_FIFOEN                      ((uint8_t)0x1 << 0)

/*******************  Bit definition for UART_LNCR register  *****************/
#define UART_LNCR_BDRAE                         ((uint8_t)0x1 << 7)
#define UART_LNCR_BKC                           ((uint8_t)0x1 << 6)
#define UART_LNCR_FPAR                          ((uint8_t)0x1 << 5)
#define UART_LNCR_PARS                          ((uint8_t)0x1 << 4)
#define UART_LNCR_PAREN                         ((uint8_t)0x1 << 3)
#define UART_LNCR_STOP                          ((uint8_t)0x1 << 2)
#define UART_LNCR_DLENS                         ((uint8_t)0x3 << 0)

/*******************  Bit definition for UART_MDMCR register  *****************/
#define UART_MDMCR_SIREN                        ((uint8_t)0x1 << 6)
#define UART_MDMCR_AFEN                         ((uint8_t)0x1 << 5)
#define UART_MDMCR_LPBK                         ((uint8_t)0x1 << 4)
#define UART_MDMCR_OUT2                         ((uint8_t)0x1 << 3)
#define UART_MDMCR_OUT1                         ((uint8_t)0x1 << 2)
#define UART_MDMCR_RTS                          ((uint8_t)0x1 << 1)
#define UART_MDMCR_DTR                          ((uint8_t)0x1 << 0)

/*******************  Bit definition for UART_LNSR register  *****************/
#define UART_LNSR_RXFIFOE                       ((uint8_t)0x1 << 7)
#define UART_LNSR_TXEMPT                        ((uint8_t)0x1 << 6)
#define UART_LNSR_TXRE                          ((uint8_t)0x1 << 5)
#define UART_LNSR_BKI                           ((uint8_t)0x1 << 4)
#define UART_LNSR_FME                           ((uint8_t)0x1 << 3)
#define UART_LNSR_PARE                          ((uint8_t)0x1 << 2)
#define UART_LNSR_OFE                           ((uint8_t)0x1 << 1)
#define UART_LNSR_DATARDY                       ((uint8_t)0x1 << 0)

/*******************  Bit definition for UART_MDMSR register  *****************/
#define UART_MDMSR_DCD                          ((uint8_t)0x1 << 7)
#define UART_MDMSR_RI                           ((uint8_t)0x1 << 6)
#define UART_MDMSR_DSR                          ((uint8_t)0x1 << 5)
#define UART_MDMSR_CTS                          ((uint8_t)0x1 << 4)
#define UART_MDMSR_DCDA                         ((uint8_t)0x1 << 3)
#define UART_MDMSR_RIA                          ((uint8_t)0x1 << 2)
#define UART_MDMSR_DSRA                         ((uint8_t)0x1 << 1)
#define UART_MDMSR_CTSA                         ((uint8_t)0x1 << 0)

/*******************  Bit definition for UART_FIFOAR register  *****************/
#define UART_FIFOAR                             ((uint8_t)0xFF << 0)

/*******************  Bit definition for UART_TFIFORR register  *****************/
#define UART_TFIFORR                            ((uint8_t)0xFF << 0)

/*******************  Bit definition for UART_RFIFOWR register  *****************/
#define UART_RFIFOWR_RFIFOFME                   ((uint16_t)0x1 << 9)
#define UART_RFIFOWR_RFIFOPARE                  ((uint16_t)0x1 << 8)
#define UART_RFIFOWR_RFIFOWRD                   ((uint16_t)0xFF << 0)

/*******************  Bit definition for UART_HLTEN register  *****************/
#define UART_HLTEN                              ((uint8_t)0x1 << 0)

/*******************  Bit definition for UART_DMASWACK register  *****************/
#define UART_DMASWACK                           ((uint8_t)0x1 << 0)

/******************************************************************************/
/*                                                                            */
/*                                I2C                                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for I2C_CTRL register  *****************/
#define I2C_CTRL_TXE_CTRL                       ((uint16_t)0x1 << 8)
#define I2C_CTRL_STOPDET_CTRL                   ((uint16_t)0x1 << 7)
#define I2C_CTRL_SLV_DE                         ((uint16_t)0x1 << 6)
#define I2C_CTRL_RESTART_EN                     ((uint16_t)0x1 << 5)
#define I2C_CTRL_MSTADDR_SEL                    ((uint16_t)0x1 << 4)
#define I2C_CTRL_SLVADDR_SEL                    ((uint16_t)0x1 << 3)
#define I2C_CTRL_SPEED                          ((uint16_t)0x3 << 1)
#define I2C_CTRL_MST_EN                         ((uint16_t)0x1 << 0)

/*******************  Bit definition for I2C_TARADDR register  *****************/
#define I2C_TARADDR_SPECIAL                     ((uint16_t)0x1 << 11)
#define I2C_TARADDR_GCALL_START                 ((uint16_t)0x1 << 10)
#define I2C_TARADDR_10BITS                      ((uint16_t)0x3FF << 0)
#define I2C_TARADDR_7BITS                       ((uint16_t)0x7F << 0)

/*******************  Bit definition for I2C_SARADDR register  *****************/
#define I2C_SARADDR_10BITS                      ((uint16_t)0x3FF << 0)
#define I2C_SARADDR_7BITS                       ((uint16_t)0x7F << 0)

/*******************  Bit definition for I2C_DC register  *****************/
#define I2C_DC_RESTART                          ((uint16_t)0x1 << 10)
#define I2C_DC_STOP                             ((uint16_t)0x1 << 9)
#define I2C_DC_CMD                              ((uint16_t)0x1 << 8)
#define I2C_DC_DAT                              ((uint16_t)0xFF << 0)
#define I2C_DC_Read          										I2C_DC_CMD
#define I2C_DC_Stop          										I2C_DC_STOP
#define	I2C_DC_Restart       										I2C_DC_RESTART

/*******************  Bit definition for I2C_SCLH_SS register  *****************/
#define I2C_SCLH_SS                             ((uint16_t)0xFFFF << 0)

/*******************  Bit definition for I2C_SCLL_SS register  *****************/
#define I2C_SCLL_SS                             ((uint16_t)0xFFFF << 0)

/*******************  Bit definition for I2C_ISR register  *****************/
#define I2C_ISR_MHBUS                           ((uint16_t)0x1 << 13)
#define I2C_ISR_RSDET                           ((uint16_t)0x1 << 12)
#define I2C_ISR_GC                              ((uint16_t)0x1 << 11)
#define I2C_ISR_SDET                            ((uint16_t)0x1 << 10)
#define I2C_ISR_SPDET                           ((uint16_t)0x1 << 9)
#define I2C_ISR_ACT                             ((uint16_t)0x1 << 8)
#define I2C_ISR_RXD                             ((uint16_t)0x1 << 7)
#define I2C_ISR_TXA                             ((uint16_t)0x1 << 6)
#define I2C_ISR_RDR                             ((uint16_t)0x1 << 5)
#define I2C_ISR_TXE                             ((uint16_t)0x1 << 4)
#define I2C_ISR_TXO                             ((uint16_t)0x1 << 3)
#define I2C_ISR_RXF                             ((uint16_t)0x1 << 2)
#define I2C_ISR_RXO                             ((uint16_t)0x1 << 1)
#define I2C_ISR_RXU                             ((uint16_t)0x1 << 0)

/*******************  Bit definition for I2C_IMR register  *****************/
#define I2C_IMR_MMHBUS                           ((uint16_t)0x1 << 13)
#define I2C_IMR_MRSDET                           ((uint16_t)0x1 << 12)
#define I2C_IMR_MGC                              ((uint16_t)0x1 << 11)
#define I2C_IMR_MSDET                            ((uint16_t)0x1 << 10)
#define I2C_IMR_MSPDET                           ((uint16_t)0x1 << 9)
#define I2C_IMR_MACT                             ((uint16_t)0x1 << 8)
#define I2C_IMR_MRXD                             ((uint16_t)0x1 << 7)
#define I2C_IMR_MTXA                             ((uint16_t)0x1 << 6)
#define I2C_IMR_MRDR                             ((uint16_t)0x1 << 5)
#define I2C_IMR_MTXE                             ((uint16_t)0x1 << 4)
#define I2C_IMR_MTXO                             ((uint16_t)0x1 << 3)
#define I2C_IMR_MRXF                             ((uint16_t)0x1 << 2)
#define I2C_IMR_MRXO                             ((uint16_t)0x1 << 1)
#define I2C_IMR_MRXU                             ((uint16_t)0x1 << 0)
#define I2C_IMR_ALL         										 ((uint16_t)0x3FFF)

/*******************  Bit definition for I2C_RISR register  *****************/
#define I2C_RISR_MHBUS                           ((uint16_t)0x1 << 13)
#define I2C_RISR_RSDET                           ((uint16_t)0x1 << 12)
#define I2C_RISR_GC                              ((uint16_t)0x1 << 11)
#define I2C_RISR_SDET                            ((uint16_t)0x1 << 10)
#define I2C_RISR_SPDET                           ((uint16_t)0x1 << 9)
#define I2C_RISR_ACT                             ((uint16_t)0x1 << 8)
#define I2C_RISR_RXD                             ((uint16_t)0x1 << 7)
#define I2C_RISR_TXA                             ((uint16_t)0x1 << 6)
#define I2C_RISR_RDR                             ((uint16_t)0x1 << 5)
#define I2C_RISR_TXE                             ((uint16_t)0x1 << 4)
#define I2C_RISR_TXO                             ((uint16_t)0x1 << 3)
#define I2C_RISR_RXF                             ((uint16_t)0x1 << 2)
#define I2C_RISR_RXO                             ((uint16_t)0x1 << 1)
#define I2C_RISR_RXU                             ((uint16_t)0x1 << 0)

/*******************  Bit definition for I2C_RXTH register  *****************/
#define I2C_RXTH                                 ((uint8_t)0xFF < 0) 

/*******************  Bit definition for I2C_TXTH register  *****************/
#define I2C_TXTH                                 ((uint8_t)0xFF < 0)

/*******************  Bit definition for I2C_ICLR register  *****************/
#define I2C_ICRL                                 ((uint8_t)0x1 < 0)

/*******************  Bit definition for I2C_RXU_CLR register  *****************/
#define I2C_RXU_CLR                              ((uint8_t)0x1 < 0)

/*******************  Bit definition for I2C_RXO_CLR register  *****************/
#define I2C_RXO_CLR                              ((uint8_t)0x1 < 0)

/*******************  Bit definition for I2C_TXO_CLR register  *****************/
#define I2C_TXO_CLR                              ((uint8_t)0x1 < 0)

/*******************  Bit definition for I2C_RDR_CLR register  *****************/
#define I2C_RDR_CLR                              ((uint8_t)0x1 < 0)

/*******************  Bit definition for I2C_TXA_CLR register  *****************/
#define I2C_TXA_CLR                              ((uint8_t)0x1 < 0)

/*******************  Bit definition for I2C_RXD_CLR register  *****************/
#define I2C_RXD_CLR                              ((uint8_t)0x1 < 0)

/*******************  Bit definition for I2C_ACT_CLR register  *****************/
#define I2C_ACT_CLR                              ((uint8_t)0x1 < 0)

/*******************  Bit definition for I2C_SPDET_CLR register  *****************/
#define I2C_SPDET_CLR                            ((uint8_t)0x1 < 0)

/*******************  Bit definition for I2C_SDET_CLR register  *****************/
#define I2C_SDET_CLR                             ((uint8_t)0x1 < 0)

/*******************  Bit definition for I2C_GC_CLR register  *****************/
#define I2C_GC_CLR                               ((uint8_t)0x1 < 0)

/*******************  Bit definition for I2C_RSDET_CLR register  *****************/
#define I2C_RSDET_CLR                            ((uint8_t)0x1 << 0)

/*******************  Bit definition for I2C_EN register  *****************/
#define I2C_EN_ABRT                              ((uint8_t)0x1 << 1)
#define I2C_EN                                   ((uint8_t)0x1 << 0)

/*******************  Bit definition for I2C_STS register  *****************/
#define I2C_STS_SLV_ACT                          ((uint8_t)0x1 << 6)
#define I2C_STS_MST_ACT                          ((uint8_t)0x1 << 5)
#define I2C_STS_RXF                              ((uint8_t)0x1 << 4)
#define I2C_STS_RXNE                             ((uint8_t)0x1 << 3)
#define I2C_STS_TXE                              ((uint8_t)0x1 << 2)
#define I2C_STS_TXNF                             ((uint8_t)0x1 << 1)
#define I2C_STS_ACT                              ((uint8_t)0x1 << 0)

/*******************  Bit definition for I2C_TXFL register  *****************/
#define I2C_TXFL                                 ((uint8_t)0xF << 0)

/*******************  Bit definition for I2C_RXFL register  *****************/
#define I2C_RXFL                                 ((uint8_t)0xF << 0)

/*******************  Bit definition for I2C_SDAHOLD register  *****************/
#define I2C_SDAHOLD_RX                           ((uint32_t)0xFFFF << 16)
#define I2C_SDAHOLD_TX                           ((uint32_t)0xFFFF << 0)

/*******************  Bit definition for I2C_TXABRTS register  *****************/
#define I2C_TXABRTS_BKTXFL                       ((uint32_t)0xFF << 24) 
#define I2C_TXABRTS_ABRTDET                      ((uint32_t)0x3 << 16)
#define I2C_TXABRTS_RD                           ((uint32_t)0x1 << 15) 
#define I2C_TXABRTS_ABRTL                        ((uint32_t)0x1 << 14) 
#define I2C_TXABRTS_TXNE                         ((uint32_t)0x1 << 13) 
#define I2C_TXABRTS_MABRTL                       ((uint32_t)0x1 << 12) 
#define I2C_TXABRTS_DIS                          ((uint32_t)0x1 << 11) 
#define I2C_TXABRTS_RDE                          ((uint32_t)0x1 << 10) 
#define I2C_TXABRTS_SB                           ((uint32_t)0x1 << 9) 
#define I2C_TXABRTS_SBAK                         ((uint32_t)0x1 << 7) 
#define I2C_TXABRTS_GCRD                         ((uint32_t)0x1 << 5) 
#define I2C_TXABRTS_GCNK                         ((uint32_t)0x1 << 4) 
#define I2C_TXABRTS_TXNK                         ((uint32_t)0x1 << 3) 
#define I2C_TXABRTS_NK3                          ((uint32_t)0x1 << 2) 
#define I2C_TXABRTS_NK2                          ((uint32_t)0x1 << 1) 
#define I2C_TXABRTS_NK1                          ((uint32_t)0x1 << 0)

/*******************  Bit definition for I2C_DMAC register  *****************/
#define I2C_DMAC_TE                              ((uint8_t)0x1 << 1)
#define I2C_DMAC_RE                              ((uint8_t)0x1 << 0)

/*******************  Bit definition for I2C_DMATL register  *****************/
#define I2C_DMATL                                ((uint8_t)0x7 << 0)

/*******************  Bit definition for I2C_DMARL register  *****************/
#define I2C_DMARL                                ((uint8_t)0x7 << 0)

/*******************  Bit definition for I2C_SDASETUP register  *****************/
#define I2C_SDASETUP                             ((uint8_t)0xFF << 0)

/*******************  Bit definition for I2C_GCALL_ACK register  *****************/
#define I2C_GCALL_ACK                            ((uint8_t)0x1 << 0)

/*******************  Bit definition for I2C_ENSTS register  *****************/
#define I2C_ENSTS_SLVRX_LOST                     ((uint8_t)0x1 << 2)
#define I2C_ENSTS_SLVDIS_BUSY                    ((uint8_t)0x1 << 1)
#define I2C_ENSTS_EN                             ((uint8_t)0x1 << 0)

/*******************  Bit definition for I2C_SPKF register  *****************/
#define I2C_SPKF                                 ((uint8_t)0xFF << 0)

/******************************************************************************/
/*                                                                            */
/*                                DMA                                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for DMA_CH0_SRCADDR register  *****************/
#define DMA_CH0_SRCADDR                          ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for DMA_CH0_DSTADDR register  *****************/
#define DMA_CH0_DSTADDR                          ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for DMA_CH0_CTRL0 register  *****************/
#define DMA_CH0_CTRL0_TT                           ((uint32_t)0x7 << 20)
#define DMA_CH0_CTRL0_DSTSCA_EN                    ((uint32_t)0x1 << 18)
#define DMA_CH0_CTRL0_SRCGAT_EN                    ((uint32_t)0x1 << 17)
#define DMA_CH0_CTRL0_SRC_BLEN                     ((uint32_t)0x7 << 14)
#define DMA_CH0_CTRL0_DST_BLEN                     ((uint32_t)0x7 << 11)
#define DMA_CH0_CTRL0_SADDR_INC                    ((uint32_t)0x3 << 9)
#define DMA_CH0_CTRL0_DADDR_INC                    ((uint32_t)0x3 << 7)
#define DMA_CH0_CTRL0_STRAN_WD                     ((uint32_t)0x7 << 4)
#define DMA_CH0_CTRL0_DTRAN_WD                     ((uint32_t)0x7 << 1)
#define DMA_CH0_CTRL0_INTEN                        ((uint32_t)0x1 << 0)

/*******************  Bit definition for DMA_CH0_CTRL1 register  *****************/
#define DMA_CH0_CTRL1_BLK_SZ                       ((uint16_t)0xFFF << 0)

/*******************  Bit definition for DMA_CH0_CFG0 register  *****************/
#define DMA_CH0_CFG0_MAX_BLEN                      ((uint32_t)0x3FF << 20)
#define DMA_CH0_CFG0_SHS_POL                       ((uint32_t)0x1 << 19)
#define DMA_CH0_CFG0_DHS_POL                       ((uint32_t)0x1 << 18)
#define DMA_CH0_CFG0_SHS_SEL                       ((uint32_t)0x1 << 11)
#define DMA_CH0_CFG0_DHS_SEL                       ((uint32_t)0x1 << 10)
#define DMA_CH0_CFG0_FE                            ((uint32_t)0x1 << 9)
#define DMA_CH0_CFG0_SUSPEND                       ((uint32_t)0x1 << 8)
#define DMA_CH0_CFG0_PRIOR                         ((uint32_t)0x7 << 5)

/*******************  Bit definition for DMA_CH0_CFG1 register  *****************/
#define DMA_CH0_CFG1_DPER_HS                       ((uint16_t)0xF << 11)
#define DMA_CH0_CFG1_SPER_HS                       ((uint16_t)0xF << 7)
#define DMA_CH0_CFG1_PC                            ((uint16_t)0x7 << 2)
#define DMA_CH0_CFG1_FM                            ((uint16_t)0x1 << 1)

/*******************  Bit definition for DMA_CH0_SRCGAT register  *****************/
#define DMA_CH0_SRCGAT_SGAT_CNT                    ((uint32_t)0xFFF << 20)
#define DMA_CH0_SRCGAT_SGAT_ITV                    ((uint32_t)0xFFFFF << 0)

/*******************  Bit definition for DMA_CH0_DSTSCA register  *****************/
#define DMA_CH0_DSTSCA_DSCA_CNT                    ((uint32_t)0xFFF << 20)
#define DMA_CH0_DSTSCA_DSCA_ITV                    ((uint32_t)0xFFFFF << 0)

/*******************  Bit definition for DMA_CH1_SRCADDR register  *****************/
#define DMA_CH1_SRCADDR                            ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for DMA_CH1_DSTADDR register  ** ***************/
#define DMA_CH1_DSTADDR                            ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for DMA_CH1_CTRL0 register  *****************/
#define DMA_CH1_CTRL0_TT                           ((uint32_t)0x7 << 20)
#define DMA_CH1_CTRL0_DSTSCA_EN                    ((uint32_t)0x1 << 18)
#define DMA_CH1_CTRL0_SRCGAT_EN                    ((uint32_t)0x1 << 17)
#define DMA_CH1_CTRL0_SRC_BLEN                     ((uint32_t)0x7 << 14)
#define DMA_CH1_CTRL0_DST_BLEN                     ((uint32_t)0x7 << 11)
#define DMA_CH1_CTRL0_SADDR_INC                    ((uint32_t)0x3 << 9)
#define DMA_CH1_CTRL0_DADDR_INC                    ((uint32_t)0x3 << 7)
#define DMA_CH1_CTRL0_STRAN_WD                     ((uint32_t)0x7 << 4)
#define DMA_CH1_CTRL0_DTRAN_WD                     ((uint32_t)0x7 << 1)
#define DMA_CH1_CTRL0_INTEN                        ((uint32_t)0x1 << 0)

/*******************  Bit definition for DMA_CH1_CTRL1 register  *****************/
#define DMA_CH1_CTRL1_BLK_SZ                       ((uint16_t)0xFFF << 0)

/*******************  Bit definition for DMA_CH1_CFG0 register  *****************/
#define DMA_CH1_CFG0_MAX_BLEN                      ((uint32_t)0x3FF << 20)
#define DMA_CH1_CFG0_SHS_POL                       ((uint32_t)0x1 << 19)
#define DMA_CH1_CFG0_DHS_POL                       ((uint32_t)0x1 << 18)
#define DMA_CH1_CFG0_SHS_SEL                       ((uint32_t)0x1 << 11)
#define DMA_CH1_CFG0_DHS_SEL                       ((uint32_t)0x1 << 10)
#define DMA_CH1_CFG0_FE                            ((uint32_t)0x1 << 9)
#define DMA_CH1_CFG0_SUSPEND                       ((uint32_t)0x1 << 8)
#define DMA_CH1_CFG0_PRIOR                         ((uint32_t)0x7 << 5)

/*******************  Bit definition for DMA_CH1_CFG1 register  *****************/
#define DMA_CH1_CFG1_DPER_HS                       ((uint16_t)0xF << 11)
#define DMA_CH1_CFG1_SPER_HS                       ((uint16_t)0xF << 7)
#define DMA_CH1_CFG1_PC                            ((uint16_t)0x7 << 2)
#define DMA_CH1_CFG1_FM                            ((uint16_t)0x1 << 1)

/*******************  Bit definition for DMA_CH1_SRCGAT register  *****************/
#define DMA_CH1_SRCGAT_SGAT_CNT                    ((uint32_t)0xFFF << 20)
#define DMA_CH1_SRCGAT_SGAT_ITV                    ((uint32_t)0xFFFFF << 0)

/*******************  Bit definition for DMA_CH1_DSTSCA register  *****************/
#define DMA_CH1_DSTSCA_DSCA_CNT                    ((uint32_t)0xFFF << 20)
#define DMA_CH1_DSTSCA_DSCA_ITV                    ((uint32_t)0xFFFFF << 0)

/*******************  Bit definition for DMA_RAWTC register  *****************/
#define DMA_RAWTC_INTS_CH1                         ((uint8_t)0x1 << 1)
#define DMA_RAWTC_INTS_CH0                         ((uint8_t)0x1 << 0)

/*******************  Bit definition for DMA_RAWBLKTC register  *****************/
#define DMA_RAWBLKTC_INTS_CH1                      ((uint8_t)0x1 << 1)
#define DMA_RAWBLKTC_INTS_CH0                      ((uint8_t)0x1 << 0)

/*******************  Bit definition for DMA_RAWSRCTC register  *****************/
#define DMA_RAWSRCTC_INTS_CH1                      ((uint8_t)0x1 << 1)
#define DMA_RAWSRCTC_INTS_CH0                      ((uint8_t)0x1 << 0)

/*******************  Bit definition for DMA_RAWDSTTC register  *****************/
#define DMA_RAWDSTTC_INTS_CH1                      ((uint8_t)0x1 << 1)
#define DMA_RAWDSTTC_INTS_CH0                      ((uint8_t)0x1 << 0)

/*******************  Bit definition for DMA_RAWERR register  *****************/
#define DMA_RAWERR_INTS_CH1                        ((uint8_t)0x1 << 1)
#define DMA_RAWERR_INTS_CH0                        ((uint8_t)0x1 << 0)

/*******************  Bit definition for DMA_TC register  *****************/
#define DMA_TC_INTS_CH1                            ((uint8_t)0x1 << 1)
#define DMA_TC_INTS_CH0                            ((uint8_t)0x1 << 0)

/*******************  Bit definition for DMA_BLKTC register  *****************/
#define DMA_BLKTC_INTS_CH1                         ((uint8_t)0x1 << 1)
#define DMA_BLKTC_INTS_CH0                         ((uint8_t)0x1 << 0)

/*******************  Bit definition for DMA_SRCTC register  *****************/
#define DMA_SRCTC_INTS_CH1                         ((uint8_t)0x1 << 1)
#define DMA_SRCTC_INTS_CH0                         ((uint8_t)0x1 << 0)

/*******************  Bit definition for DMA_DSTTC register  *****************/
#define DMA_DSTTC_INTS_CH1                         ((uint8_t)0x1 << 1)
#define DMA_DSTTC_INTS_CH0                         ((uint8_t)0x1 << 0)

/*******************  Bit definition for DMA_ERR register  *****************/
#define DMA_ERR_INTS_CH1                           ((uint8_t)0x1 << 1)
#define DMA_ERR_INTS_CH0                           ((uint8_t)0x1 << 0)

/*******************  Bit definition for DMA_MASKTC register  *****************/
#define DMA_MASKTC_CH1MTC_WE                       ((uint16_t)0x1 << 9)
#define DMA_MASKTC_CH0MTC_WE                       ((uint16_t)0x1 << 8)
#define DMA_MASKTC_CH1MASKTC                       ((uint16_t)0x1 << 1)
#define DMA_MASKTC_CH0MASKTC                       ((uint16_t)0x1 << 0)

/*******************  Bit definition for DMA_MASKBLKTC register  *****************/
#define DMA_MASKBLKTC_CH1MBLKTC_WE                 ((uint16_t)0x1 << 9)
#define DMA_MASKBLKTC_CH0MBLKTC_WE                 ((uint16_t)0x1 << 8)
#define DMA_MASKBLKTC_CH1MASKBLKTC                 ((uint16_t)0x1 << 1)
#define DMA_MASKBLKTC_CH0MASKBLKTC                 ((uint16_t)0x1 << 0)

/*******************  Bit definition for DMA_MASKSRCTC register  *****************/
#define DMA_MASKSRCTC_CH1MSRCTC_WE                 ((uint16_t)0x1 << 9)
#define DMA_MASKSRCTC_CH0MSRCTC_WE                 ((uint16_t)0x1 << 8)
#define DMA_MASKSRCTC_CH1MASKSRCTC                 ((uint16_t)0x1 << 1)
#define DMA_MASKSRCTC_CH0MASKSRCTC                 ((uint16_t)0x1 << 0)


/*******************  Bit definition for DMA_MASKDSTTC register  *****************/
#define DMA_MASKDSTTC_CH1MDSTTC_WE                 ((uint16_t)0x1 << 9)
#define DMA_MASKDSTTC_CH0MDSTTC_WE                 ((uint16_t)0x1 << 8)
#define DMA_MASKDSTTC_CH1MASKDSTTC                 ((uint16_t)0x1 << 1)
#define DMA_MASKDSTTC_CH0MASKDSTTC                 ((uint16_t)0x1 << 0)

/*******************  Bit definition for DMA_MASKERR register  *****************/
#define DMA_MASKERR_CH1MERR_WE                     ((uint16_t)0x1 << 9)
#define DMA_MASKERR_CH0MERR_WE                     ((uint16_t)0x1 << 8)
#define DMA_MASKERR_CH1MASKERR                     ((uint16_t)0x1 << 1)
#define DMA_MASKERR_CH0MASKERR                     ((uint16_t)0x1 << 0)

/*******************  Bit definition for DMA_CLEARTC register  *****************/
#define DMA_CLEARTC_CH1                            ((uint8_t)0x1 << 1)
#define DMA_CLEARTC_CH0                            ((uint8_t)0x1 << 0)

/*******************  Bit definition for DMA_CLEARBLKTC register  *****************/
#define DMA_CLEARBLKTC_CH1                         ((uint8_t)0x1 << 1)
#define DMA_CLEARBLKTC_CH0                         ((uint8_t)0x1 << 0)

/*******************  Bit definition for DMA_CLEARSRCTC register  *****************/
#define DMA_CLEARSRCTC_CH1                         ((uint8_t)0x1 << 1)
#define DMA_CLEARSRCTC_CH0                         ((uint8_t)0x1 << 0)

/*******************  Bit definition for DMA_CLEARDSTTC register  *****************/
#define DMA_CLEARDSTTC_CH1                         ((uint8_t)0x1 << 1)
#define DMA_CLEARDSTTC_CH0                         ((uint8_t)0x1 << 0)

/*******************  Bit definition for DMA_CLEARERR register  *****************/
#define DMA_CLEARERR_CH1                           ((uint8_t)0x1 << 1)
#define DMA_CLEARERR_CH0                           ((uint8_t)0x1 << 0)

/*******************  Bit definition for DMA_COMBINT register  *****************/
#define DMA_COMBINT_ERR                            ((uint8_t)0x1 << 4)
#define DMA_COMBINT_DSTTC                          ((uint8_t)0x1 << 3)
#define DMA_COMBINT_SRCTC                          ((uint8_t)0x1 << 2)
#define DMA_COMBINT_BLKTC                          ((uint8_t)0x1 << 1)
#define DMA_COMBINT_TC                             ((uint8_t)0x1 << 0)

/*******************  Bit definition for DMA_SRCTRANREQ register  *****************/
#define DMA_SRCTRANREQ_CH1SRCREQ_WE                ((uint16_t)0x1 << 9)
#define DMA_SRCTRANREQ_CH0SRCREQ_WE                ((uint16_t)0x1 << 8)
#define DMA_SRCTRANREQ_CH1SRCREQ                   ((uint16_t)0x1 << 1)
#define DMA_SRCTRANREQ_CH0SRCREQ                   ((uint16_t)0x1 << 0)

/*******************  Bit definition for DMA_DSTTRANREQ register  *****************/
#define DMA_DSTTRANREQ_CH1DSTREQ_WE                ((uint16_t)0x1 << 9)
#define DMA_DSTTRANREQ_CH0DSTREQ_WE                ((uint16_t)0x1 << 8)
#define DMA_DSTTRANREQ_CH1DSTREQ                   ((uint16_t)0x1 << 1)
#define DMA_DSTTRANREQ_CH0DSTREQ                   ((uint16_t)0x1 << 0)

/*******************  Bit definition for DMA_SRCSGLTRANREQ register  *****************/
#define DMA_SRCSGLTRANREQ_CH1SRCSGLREQ_WE          ((uint16_t)0x1 << 9)
#define DMA_SRCSGLTRANREQ_CH0SRCSGLREQ_WE          ((uint16_t)0x1 << 8)
#define DMA_SRCSGLTRANREQ_CH1SRCSGLREQ             ((uint16_t)0x1 << 1)
#define DMA_SRCSGLTRANREQ_CH0SRCSGLREQ             ((uint16_t)0x1 << 0)

/*******************  Bit definition for DMA_DSTSGLTRANREQ register  *****************/
#define DMA_DSTSGLTRANREQ_CH1DSTSGLREQ_WE          ((uint16_t)0x1 << 9)
#define DMA_DSTSGLTRANREQ_CH0DSTSGLREQ_WE          ((uint16_t)0x1 << 8)
#define DMA_DSTSGLTRANREQ_CH1DSTSGLREQ             ((uint16_t)0x1 << 1)
#define DMA_DSTSGLTRANREQ_CH0DSTSGLREQ             ((uint16_t)0x1 << 0)

/*******************  Bit definition for DMA_DMAEN register  *****************/
#define DMA_DMAEN                                  ((uint8_t)0x1 << 0)

/*******************  Bit definition for DMA_CHxEN register  *****************/
#define DMA_CHxEN_CH1EN_WE                         ((uint16_t)0x1 << 9)
#define DMA_CHxEN_CH0EN_WE                         ((uint16_t)0x1 << 8)
#define DMA_CHxEN_CH1EN                            ((uint16_t)0x1 << 1)
#define DMA_CHxEN_CH0EN                            ((uint16_t)0x1 << 0)

/*******************  Bit definition for DMA_DMAID register  *****************/
#define DMA_DMAID                                  ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for DMA_DMATEST register  *****************/
#define DMA_DMATEST                                ((uint8_t)0x1 << 0)

/*******************  Bit definition for DMA_HSx_CFG register  *****************/
#define DMA_HSx_CFG                                ((uint8_t)0xFF << 0)

/******************************************************************************/
/*                                                                            */
/*                                SPI                                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for SPI_CTRL0 register  *****************/
#define SPI_CTRL0_CFL                              ((uint16_t)0xF << 12)
#define SPI_CTRL0_LTE                              ((uint16_t)0x1 << 11)
#define SPI_CTRL0_SOE                              ((uint16_t)0x1 << 10)
#define SPI_CTRL0_MODE                             ((uint16_t)0x3 << 8)
#define SPI_CTRL0_SCPOL                            ((uint16_t)0x1 << 7)
#define SPI_CTRL0_SCPH                             ((uint16_t)0x1 << 6)
#define SPI_CTRL0_SPS                              ((uint16_t)0x3 << 4)
#define SPI_CTRL0_DFL                              ((uint16_t)0xF << 0)

/*******************  Bit definition for SPI_CTRL1 register  *****************/
#define SPI_CTRL1_DATANUM                          ((uint16_t)0xFFFF << 0)

/*******************  Bit definition for SPI_EN register  *****************/
#define SPI_EN                                     ((uint8_t)0x1 << 0) 

/*******************  Bit definition for SPI_MW_CTRL register  *****************/
#define SPI_MW_CTRL_MWHS                           ((uint8_t)0x1 << 2)
#define SPI_MW_CTRL_MWDIR                          ((uint8_t)0x1 << 1)
#define SPI_MW_CTRL_MWMOD                          ((uint8_t)0x1 << 0)

/*******************  Bit definition for SPI_SSEL register  *****************/
#define SPI_SSEL                                   ((uint8_t)0x1 << 0)

/*******************  Bit definition for SPI_BAUD register  *****************/
#define SPI_BAUD_DIV                               ((uint16_t)0xFFFF << 0)

/*******************  Bit definition for SPI_TXTHL register  *****************/
#define SPI_TXTHL                                  ((uint8_t)0x7 << 0)

/*******************  Bit definition for SPI_RXTHL register  *****************/
#define SPI_RXTHL                                  ((uint8_t)0x7 << 0)

/*******************  Bit definition for SPI_TXTL register  *****************/
#define SPI_TXTL                                   ((uint8_t)0xF << 0)

/*******************  Bit definition for SPI_RXTL register  *****************/
#define SPI_RXTL                                   ((uint8_t)0xF << 0)

/*******************  Bit definition for SPI_STS register  *****************/
#define SPI_STS_TXERR                              ((uint8_t)0x1 << 5)
#define SPI_STS_RXF                                ((uint8_t)0x1 << 4)
#define SPI_STS_RXNE                               ((uint8_t)0x1 << 3)
#define SPI_STS_TXE                                ((uint8_t)0x1 << 2)
#define SPI_STS_TXNF                               ((uint8_t)0x1 << 1)
#define SPI_STS_BUSY                               ((uint8_t)0x1 << 0)

/*******************  Bit definition for SPI_IM register  *****************/
#define SPI_IM_MMCM                                ((uint8_t)0x1 << 5)
#define SPI_IM_RXFM                                ((uint8_t)0x1 << 4)
#define SPI_IM_RXOVM                               ((uint8_t)0x1 << 3)
#define SPI_IM_RXUDM                               ((uint8_t)0x1 << 2)
#define SPI_IM_TXOVM                               ((uint8_t)0x1 << 1)
#define SPI_IM_TXEM                                ((uint8_t)0x1 << 0)

/*******************  Bit definition for SPI_IS register  *****************/
#define SPI_IS_MMCS                                ((uint8_t)0x1 << 5)
#define SPI_IS_RXFS                                ((uint8_t)0x1 << 4)
#define SPI_IS_RXOVS                               ((uint8_t)0x1 << 3)
#define SPI_IS_RXUDS                               ((uint8_t)0x1 << 2)
#define SPI_IS_TXOVS                               ((uint8_t)0x1 << 1)
#define SPI_IS_TXES                                ((uint8_t)0x1 << 0)

/*******************  Bit definition for SPI_RIS register  *****************/
#define SPI_RIS_RXFR                                ((uint8_t)0x1 << 4)
#define SPI_RIS_RXOVR                               ((uint8_t)0x1 << 3)
#define SPI_RIS_RXUDR                               ((uint8_t)0x1 << 2)
#define SPI_RIS_TXOVR                               ((uint8_t)0x1 << 1)
#define SPI_RIS_TXER                                ((uint8_t)0x1 << 0)

/*******************  Bit definition for SPI_TXOV_CLR register  *****************/
#define SPI_TXOV_CLR                                ((uint8_t)0x1 << 0)

/*******************  Bit definition for SPI_RXOV_CLR register  *****************/
#define SPI_RXOV_CLR                                ((uint8_t)0x1 << 0)

/*******************  Bit definition for SPI_RXUD_CLR register  *****************/
#define SPI_RXUD_CLR                                ((uint8_t)0x1 << 0)

/*******************  Bit definition for SPI_MMC_CLR register  *****************/
#define SPI_MMC_CLR                                 ((uint8_t)0x1 << 0)

/*******************  Bit definition for SPI_INT_CLR register  *****************/
#define SPI_INT_CLR                                 ((uint8_t)0x1 << 0)

/*******************  Bit definition for SPI_DMA_CTRL register  *****************/
#define SPI_DMA_CTRL_TE                             ((uint8_t)0x1 << 1)
#define SPI_DMA_CTRL_RE                             ((uint8_t)0x1 << 0)

/*******************  Bit definition for SPI_DMA_TXL register  *****************/
#define SPI_DMA_TXL                                 ((uint8_t)0x7 << 0)

/*******************  Bit definition for SPI_DMA_RXL register  *****************/
#define SPI_DMA_RXL                                 ((uint8_t)0x7 << 0)

/*******************  Bit definition for SPI_DATABUF register  *****************/
#define SPI_DATABUF                                 ((uint16_t)0xFFFF << 0)

/******************************************************************************/
/*                                                                            */
/*                                TIMER                                       */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for TIMER_TMxLOADCNT0 register  *****************/
#define TIMER_TMxLoadCnt0                           ((uint32_t)0xFFFFFFFF)

/*******************  Bit definition for TIMER_TMxLOADCNT1 register  *****************/
#define TIMER_TMxLoadCnt1                           ((uint32_t)0xFFFFFFFF)

/*******************  Bit definition for TIMER_TMxCURRENTCNT register  *****************/
#define TIMER_TMxCurrentCnt                         ((uint32_t)0xFFFFFFFF)

/*******************  Bit definition for TIMER_TMxCTRL register  *****************/
#define TIMER_TMxCTRL_PWM                           ((uint8_t)0x1 << 3)
#define TIMER_TMxCTRL_INTMASK                       ((uint8_t)0x1 << 2)
#define TIMER_TMxCTRL_MODE                          ((uint8_t)0x1 << 1)
#define TIMER_TMxCTRL_EN                            ((uint8_t)0x1 << 0)

/*******************  Bit definition for TIMER_TMxINTCLR register  *****************/
#define TIMER_TMxINTCLR                             ((uint8_t)0x1 << 0)

/*******************  Bit definition for TIMER_TMxINTSTS register  *****************/
#define TIMER_TMxINTSTS                             ((uint8_t)0x1 << 0)

/*******************  Bit definition for TIMER_TMxsINTSTS register  *****************/
#define TIMER_TMxsINTSTS_TM4IntSts                  ((uint8_t)0x1 << 3)
#define TIMER_TMxsINTSTS_TM3IntSts                  ((uint8_t)0x1 << 2)
#define TIMER_TMxsINTSTS_TM2IntSts                  ((uint8_t)0x1 << 1)
#define TIMER_TMxsINTSTS_TM1IntSts                  ((uint8_t)0x1 << 0)

/*******************  Bit definition for TIMER_TMxsINTCLR register  *****************/
#define TIMER_TMxsINTCLR_TM4IntClr                  ((uint8_t)0x1 << 3)
#define TIMER_TMxsINTCLR_TM3IntClr                  ((uint8_t)0x1 << 2)
#define TIMER_TMxsINTCLR_TM2IntClr                  ((uint8_t)0x1 << 1)
#define TIMER_TMxsINTCLR_TM1IntClr                  ((uint8_t)0x1 << 0)

/*******************  Bit definition for TIMER_TMxsRAWINTSTS register  *****************/
#define TIMER_TMxsRAWINTSTS_TM4IntSts               ((uint8_t)0x1 << 3)
#define TIMER_TMxsRAWINTSTS_TM3IntSts               ((uint8_t)0x1 << 2)
#define TIMER_TMxsRAWINTSTS_TM2IntSts               ((uint8_t)0x1 << 1)
#define TIMER_TMxsRAWINTSTS_TM1IntSts               ((uint8_t)0x1 << 0)

/*******************  Bit definition for TIMER_TMxsGATE register  *****************/
#define TIMER_TMxsGATE_TM4CT                        ((uint8_t)0x1 << 7)
#define TIMER_TMxsGATE_TM4Gate                      ((uint8_t)0x1 << 6)
#define TIMER_TMxsGATE_TM3CT                        ((uint8_t)0x1 << 5)
#define TIMER_TMxsGATE_TM3Gate                      ((uint8_t)0x1 << 4)
#define TIMER_TMxsGATE_TM2CT                        ((uint8_t)0x1 << 3)
#define TIMER_TMxsGATE_TM2Gate                      ((uint8_t)0x1 << 2)
#define TIMER_TMxsGATE_TM1CT                        ((uint8_t)0x1 << 1)
#define TIMER_TMxsGATE_TM1Gate                      ((uint8_t)0x1 << 0)

/******************************************************************************/
/*                                                                            */
/*                                BASETIMER                                   */
/*                                                                            */
/******************************************************************************/\
/*******************  Bit definition for BTIMER_BTMLOADCNT0 register  *****************/
#define BTIMER_BTMLoadCnt0                          ((uint32_t)0xFFFFFFFF)

/*******************  Bit definition for BTIMER_BTMLOADCNT1 register  *****************/
#define BTIMER_BTMLoadCnt1                          ((uint32_t)0xFFFFFFFF)

/*******************  Bit definition for BTIMER_BTMCURRENTCNT register  *****************/
#define BTIMER_BTMCurrentCnt                        ((uint32_t)0xFFFFFFFF)

/*******************  Bit definition for BTIMER_BTMCTRL register  *****************/
#define BTIMER_BTMCTRL_PWM                          ((uint8_t)0x1 << 3)
#define BTIMER_BTMCTRL_INTMASK                      ((uint8_t)0x1 << 2)
#define BTIMER_BTMCTRL_MODE                         ((uint8_t)0x1 << 1)
#define BTIMER_BTMCTRL_EN                           ((uint8_t)0x1 << 0)

/*******************  Bit definition for BTIMER_TMxsGATE register  *****************/
#define BTIMER_BTMGATE_TMCT                         ((uint8_t)0x1 << 1)
#define BTIMER_BTMGATE_TMGate                       ((uint8_t)0x1 << 0)

/******************************************************************************/
/*                                                                            */
/*                                PCA                                         */
/*                                                                            */
/******************************************************************************/\
/*******************  Bit definition for PCA_CCON register  *****************/
#define PCA_CCON_CF                                 ((uint8_t)0x1 << 7)
#define PCA_CCON_CR                                 ((uint8_t)0x1 << 6)
#define PCA_CCON_CCF4                               ((uint8_t)0x1 << 4)
#define PCA_CCON_CCF3                               ((uint8_t)0x1 << 3)
#define PCA_CCON_CCF2                               ((uint8_t)0x1 << 2)
#define PCA_CCON_CCF1                               ((uint8_t)0x1 << 1)
#define PCA_CCON_CCF0                               ((uint8_t)0x1 << 0)

/*******************  Bit definition for PCA_CMOD register  *****************/
#define PCA_CMOD_WDTE                               ((uint8_t)0x1 << 6)
#define PCA_CMOD_CPS                                ((uint8_t)0x7 << 1)
#define PCA_CMOD_ECF                                ((uint8_t)0x1 << 0)

/*******************  Bit definition for PCA_CL register  *****************/
#define PCA_CL                             					((uint8_t)0xFF << 0)

/*******************  Bit definition for PCA_CH register  *****************/
#define PCA_CH                             					((uint8_t)0xFF << 0)

/*******************  Bit definition for PCA_CCAPMx register  *****************/
#define PCA_CCAPMx_ECOM                             ((uint8_t)0x1 << 6)
#define PCA_CCAPMx_CAPP                             ((uint8_t)0x1 << 5)
#define PCA_CCAPMx_CAPN                             ((uint8_t)0x1 << 4)
#define PCA_CCAPMx_MAT                              ((uint8_t)0x1 << 3)
#define PCA_CCAPMx_TOG                              ((uint8_t)0x1 << 2)
#define PCA_CCAPMx_PWM                              ((uint8_t)0x1 << 1)
#define PCA_CCAPMx_ECCF                             ((uint8_t)0x1 << 0)

/*******************  Bit definition for PCA_CCAPxH register  *****************/
#define PCA_CCAPxH                                  ((uint8_t)0xFF << 0)

/*******************  Bit definition for PCA_CCAPxL register  *****************/
#define PCA_CCAPxL                                  ((uint8_t)0xFF << 0)

/*******************  Bit definition for PCA_CCAPO register  *****************/
#define PCA_CCAPO_CCAPO4                            ((uint8_t)0x1 << 4)
#define PCA_CCAPO_CCAPO3                            ((uint8_t)0x1 << 3)
#define PCA_CCAPO_CCAPO2                            ((uint8_t)0x1 << 2)
#define PCA_CCAPO_CCAPO1                            ((uint8_t)0x1 << 2)
#define PCA_CCAPO_CCAPO0                            ((uint8_t)0x1 << 0)

/******************************************************************************/
/*                                                                            */
/*                                RTC                                         */
/*                                                                            */
/******************************************************************************/\
/*******************  Bit definition for RTC_SIXTEENOFSECOND register  *****************/
#define RTC_SIXTEENOFSECOND                         ((uint8_t)0xF << 0)

/*******************  Bit definition for RTC_SECOND register  *****************/
#define RTC_SECOND                         					((uint8_t)0x7F << 0)

/*******************  Bit definition for RTC_MINUTE register  *****************/
#define RTC_MINUTE                         					((uint8_t)0x7F << 0)

/*******************  Bit definition for RTC_HOUR register  *****************/
#define RTC_HOUR                         					  ((uint8_t)0x3F << 0)

/*******************  Bit definition for RTC_DAY register  *****************/
#define RTC_DAY                         					  ((uint8_t)0x3F << 0)

/*******************  Bit definition for RTC_MONTH register  *****************/
#define RTC_MONTH                         					((uint8_t)0x1F << 0)

/*******************  Bit definition for RTC_YEAR_L register  *****************/
#define RTC_YEAR_L                         					((uint8_t)0xFF << 0)

/*******************  Bit definition for RTC_YEAR_H register  *****************/
#define RTC_YEAR_H                         					((uint8_t)0xFF << 0)

/*******************  Bit definition for RTC_SIXTEENOFSEC_DIS register  *****************/
#define RTC_SIXTEENOFSEC_DIS                        ((uint8_t)0xF << 0)

/*******************  Bit definition for RTC_SECOND_DIS register  *****************/
#define RTC_SECOND_DIS                         		  ((uint8_t)0x7F << 0)

/*******************  Bit definition for RTC_MINUTE_DIS register  *****************/
#define RTC_MINUTE_DIS                         			((uint8_t)0x7F << 0)

/*******************  Bit definition for RTC_HOUR_DIS register  *****************/
#define RTC_HOUR_DIS                         				((uint8_t)0x3F << 0)

/*******************  Bit definition for RTC_DAY_DIS register  *****************/
#define RTC_DAY_DIS                         				((uint8_t)0x3F << 0)

/*******************  Bit definition for RTC_MONTH_DIS register  *****************/
#define RTC_MONTH_DIS                         			((uint8_t)0x1F << 0)

/*******************  Bit definition for RTC_YEAR_L_DIS register  *****************/
#define RTC_YEAR_L_DIS                         			((uint8_t)0xFF << 0)

/*******************  Bit definition for RTC_YEAR_H_DIS register  *****************/
#define RTC_YEAR_H_DIS                         		  ((uint8_t)0xFF << 0)

/*******************  Bit definition for RTC_ADJUST_INC register  *****************/
#define RTC_ADJUST_INC_SIXTEEN_INC                  ((uint8_t)0x1 << 6)
#define RTC_ADJUST_INC_SECOND_INC                   ((uint8_t)0x1 << 5)
#define RTC_ADJUST_INC_YEAR_INC                     ((uint8_t)0x1 << 4)
#define RTC_ADJUST_INC_MONTH_INC                    ((uint8_t)0x1 << 3)
#define RTC_ADJUST_INC_DAY_INC                      ((uint8_t)0x1 << 2)
#define RTC_ADJUST_INC_HOUR_INC                     ((uint8_t)0x1 << 1)
#define RTC_ADJUST_INC_MINUTE_INC                   ((uint8_t)0x1 << 0)

/*******************  Bit definition for RTC_ADJUST_DEC register  *****************/
#define RTC_ADJUST_DEC_SIXTEEN_DEC                  ((uint8_t)0x1 << 6)
#define RTC_ADJUST_DEC_SECOND_DEC                   ((uint8_t)0x1 << 5)
#define RTC_ADJUST_DEC_YEAR_DEC                     ((uint8_t)0x1 << 4)
#define RTC_ADJUST_DEC_MONTH_DEC                    ((uint8_t)0x1 << 3)
#define RTC_ADJUST_DEC_DAY_DEC                      ((uint8_t)0x1 << 2)
#define RTC_ADJUST_DEC_HOUR_DEC                     ((uint8_t)0x1 << 1)
#define RTC_ADJUST_DEC_MINUTE_DEC                   ((uint8_t)0x1 << 0)

/*******************  Bit definition for RTC_FORMAT register  *****************/
#define RTC_FORMAT_EN24                             ((uint8_t)0x1 << 0)

/*******************  Bit definition for RTC_INTERVAL register  *****************/
#define RTC_INTERVAL                                ((uint8_t)0xFF << 0)

/*******************  Bit definition for RTC_EIGHTOFONE_0_DIS register  *****************/
#define RTC_EIGHTOFONE_0_DIS                        ((uint8_t)0xFF << 0)

/*******************  Bit definition for RTC_EIGHTOFONE_1_DIS register  *****************/
#define RTC_EIGHTOFONE_1_DIS                        ((uint8_t)0x7 << 0)

/*******************  Bit definition for RTC_CONF0 register  *****************/
#define RTC_CONF0_P0F                               ((uint8_t)0x3 << 2)
#define RTC_CONF0_P0D                               ((uint8_t)0x3 << 0)

/*******************  Bit definition for RTC_CONF1 register  *****************/
#define RTC_CONF1_P1F                               ((uint8_t)0x3 << 2)
#define RTC_CONF1_P1D                               ((uint8_t)0x3 << 0)

/*******************  Bit definition for RTC_PHASE register  *****************/
#define RTC_PHASE                                   ((uint8_t)0x3F << 0)

/*******************  Bit definition for RTC_HOLD register  *****************/
#define RTC_HOLD                                		((uint8_t)0x1 << 0)

/*******************  Bit definition for RTC_RESET register  *****************/
#define RTC_RESET                                		((uint8_t)0x1 << 0)

/*******************  Bit definition for RTC_INT register  *****************/
#define RTC_INT                                		  ((uint8_t)0x1 << 0)

/******************************************************************************/
/*                                                                            */
/*                                WDT                                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for WDT_CTRL register  *****************/
#define WDT_CTRL_RST_LEN                            ((uint8_t)0x7 << 2)
#define WDT_CTRL_RESP_MODE                          ((uint8_t)0x1 << 1)
#define WDT_CTRL_WDT_EN                             ((uint8_t)0x1 << 0)

/*******************  Bit definition for WDT_TIMEOV register  *****************/
#define WDT_TIMEOV                                  ((uint8_t)0xF << 0)

/*******************  Bit definition for WDT_CV register  *****************/
#define WDT_CV                                      ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for WDT_RESTART register  *****************/
#define WDT_RESTART                                 ((uint8_t)0xFF << 0)

/*******************  Bit definition for WDT_INTSTAT register  *****************/
#define WDT_INTSTAT                                 ((uint8_t)0x1 << 0)

/*******************  Bit definition for WDT_INTCLR register  *****************/
#define WDT_INTCLR                                  ((uint8_t)0x1 << 0)

/******************************************************************************/
/*                                                                            */
/*                                ADC                                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for ADC_CTRL0 register  *****************/
#define ADC_CTRL0_INTCLR                            ((uint16_t)0x1 << 15)
#define ADC_CTRL0_SAM                               ((uint16_t)0x3 << 13)
#define ADC_CTRL0_BUFEN                             ((uint16_t)0x1 << 12)
#define ADC_CTRL0_SREF                              ((uint16_t)0x3 << 10)
#define ADC_CTRL0_ISS                               ((uint16_t)0x3 << 8)
#define ADC_CTRL0_SEL                               ((uint16_t)0x7 << 5)
#define ADC_CTRL0_CLKS                              ((uint16_t)0x3 << 3)
#define ADC_CTRL0_TSEN                              ((uint16_t)0x1 << 2)
#define ADC_CTRL0_START                             ((uint16_t)0x1 << 1)
#define ADC_CTRL0_ADCEN                             ((uint16_t)0x1 << 0)

/*******************  Bit definition for ADC_CTRL1 register  *****************/
#define ADC_CTRL1_RACC_CLR                          ((uint16_t)0x1 << 12)
#define ADC_CTRL1_RACC_EN                           ((uint16_t)0x1 << 11)
#define ADC_CTRL1_CT                                ((uint16_t)0x1 << 10)
#define ADC_CTRL1_TRIGS2                            ((uint16_t)0x1F << 5)
#define ADC_CTRL1_TRIGS1                            ((uint16_t)0x1F << 0)

/*******************  Bit definition for ADC_CTRL2 register  *****************/
#define ADC_CTRL2_ADCCNT                          	((uint16_t)0xFF << 8)
#define ADC_CTRL2_CH7EN                           	((uint16_t)0x1 << 7)
#define ADC_CTRL2_CH6EN                             ((uint16_t)0x1 << 6)
#define ADC_CTRL2_CH5EN                             ((uint16_t)0x1 << 5)
#define ADC_CTRL2_CH4EN                             ((uint16_t)0x1 << 4)
#define ADC_CTRL2_CH3EN                             ((uint16_t)0x1 << 3)
#define ADC_CTRL2_CH2EN                             ((uint16_t)0x1 << 2)
#define ADC_CTRL2_CH1EN                             ((uint16_t)0x1 << 1)
#define ADC_CTRL2_CH0EN                             ((uint16_t)0x1 << 0)

/*******************  Bit definition for ADC_RESULT_ACC register  *****************/
#define ADC_RESULT_Acc                         	    ((uint32_t)0xFFFFF << 0)

/*******************  Bit definition for ADC_RESULT0 register  *****************/
#define ADC_RESULT_0                          	    ((uint16_t)0xFFF << 0)

/*******************  Bit definition for ADC_RESULT1 register  *****************/
#define ADC_RESULT_1                          	    ((uint16_t)0xFFF << 0)

/*******************  Bit definition for ADC_RESULT2 register  *****************/
#define ADC_RESULT_2                          	    ((uint16_t)0xFFF << 0)

/*******************  Bit definition for ADC_RESULT3 register  *****************/
#define ADC_RESULT_3                          	    ((uint16_t)0xFFF << 0)

/*******************  Bit definition for ADC_RESULT4 register  *****************/
#define ADC_RESULT_4                          	    ((uint16_t)0xFFF << 0)

/*******************  Bit definition for ADC_RESULT5 register  *****************/
#define ADC_RESULT_5                          	    ((uint16_t)0xFFF << 0)

/*******************  Bit definition for ADC_RESULT6 register  *****************/
#define ADC_RESULT_6                         	      ((uint16_t)0xFFF << 0)

/*******************  Bit definition for ADC_RESULT7 register  *****************/
#define ADC_RESULT_7                          	    ((uint16_t)0xFFF << 0)

/*******************  Bit definition for ADC_BGR_CTRL register  *****************/
#define ADC_BGR_CTRL_EN                          	  ((uint8_t)0x1 << 0)

/******************************************************************************/
/*                                                                            */
/*                                VC                                          */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for VC_CTRL0 register  *****************/
#define VC_CTRL0_TM1GE                              ((uint16_t)0x1 << 15)
#define VC_CTRL0_TM1G                               ((uint16_t)0x1 << 14)
#define VC_CTRL0_TM0GE                              ((uint16_t)0x1 << 13)
#define VC_CTRL0_TM0G                               ((uint16_t)0x1 << 12)
#define VC_CTRL0_VCCDIV2EN                          ((uint16_t)0x1 << 11)
#define VC_CTRL0_INPSEL                             ((uint16_t)0x7 << 8)
#define VC_CTRL0_INNSEL                             ((uint16_t)0xF << 4)
#define VC_CTRL0_BIASCTRL                           ((uint16_t)0x3 << 2)
#define VC_CTRL0_VCO                                ((uint16_t)0x1 << 1)
#define VC_CTRL0_VCEN                               ((uint16_t)0x1 << 0)

/*******************  Bit definition for VC_CTRL1 register  *****************/
#define VC_CTRL1_VCINT                              ((uint16_t)0x1 << 15)
#define VC_CTRL1_INTL                               ((uint16_t)0x1 << 14)
#define VC_CTRL1_INTPOS                             ((uint16_t)0x1 << 13)
#define VC_CTRL1_INTNEG                             ((uint16_t)0x1 << 12)
#define VC_CTRL1_VCCLEVEL                           ((uint16_t)0x3F << 6)
#define VC_CTRL1_SCALEREN                           ((uint16_t)0x1 << 5)
#define VC_CTRL1_V2P5EN                             ((uint16_t)0x1 << 4)
#define VC_CTRL1_FLT                                ((uint16_t)0x7 << 1)
#define VC_CTRL1_FLTEN                              ((uint16_t)0x1 << 0)

/******************************************************************************/
/*                                                                            */
/*                                LVD                                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for LVD_CTRL0 register  *****************/
#define LVD_CTRL0_LVDINT                            ((uint16_t)0x1 << 11)
#define LVD_CTRL0_INTL                              ((uint16_t)0x1 << 10)
#define LVD_CTRL0_INTPOS                            ((uint16_t)0x1 << 9)
#define LVD_CTRL0_INTNEG                            ((uint16_t)0x1 << 8)
#define LVD_CTRL0_WARMUPEN                          ((uint16_t)0x1 << 7)
#define LVD_CTRL0_WARMUPFAST                        ((uint16_t)0x1 << 6)
#define LVD_CTRL0_HYST                              ((uint16_t)0x1 << 5)
#define LVD_CTRL0_VSEL                              ((uint16_t)0x3 << 3)
#define LVD_CTRL0_RST                               ((uint16_t)0x1 << 2)
#define LVD_CTRL0_LVDO                              ((uint16_t)0x1 << 1)
#define LVD_CTRL0_LVDEN                             ((uint16_t)0x1 << 0)

/*******************  Bit definition for LVD_CTRL1 register  *****************/
#define LVD_CTRL1_BIASCTRL                          ((uint16_t)0x3 << 8)
#define LVD_CTRL1_LEVEL                             ((uint16_t)0xF << 4)
#define LVD_CTRL1_FLT                               ((uint16_t)0x7 << 1)
#define LVD_CTRL1_FLTEN                             ((uint16_t)0x1 << 0)

/******************************************************************************/
/*                                                                            */
/*                                FLASH                                       */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for FLASH_TNVS register  *****************/
#define FLASH_TNVS                                  ((uint16_t)0x1FF << 0)

/*******************  Bit definition for FLASH_TPGS register  *****************/
#define FLASH_TPGS                                  ((uint16_t)0x1FF << 0)

/*******************  Bit definition for FLASH_TPROG register  *****************/
#define FLASH_TPROG                                 ((uint16_t)0x3FF << 0)

/*******************  Bit definition for FLASH_TNVH register  *****************/
#define FLASH_TNVH                                  ((uint16_t)0x1FF << 0)

/*******************  Bit definition for FLASH_TRCV register  *****************/
#define FLASH_TRCV                                  ((uint8_t)0xFF << 0)

/*******************  Bit definition for FLASH_TERASE register  *****************/
#define FLASH_TERASE                                ((uint32_t)0xFFFFF << 0)

/*******************  Bit definition for FLASH_TME register  *****************/
#define FLASH_TME                                   ((uint32_t)0xFFFFF << 0)

/*******************  Bit definition for FLASH_TNVH1 register  *****************/
#define FLASH_TNVH1                                 ((uint16_t)0xFFF << 0)

/*******************  Bit definition for FLASH_CTRL register  *****************/
#define FLASH_CTRL_READ_WAIT_CYCLE                  ((uint8_t)0x1 << 2)
#define FLASH_CTRL_MODE                             ((uint8_t)0x3 << 0)

/*******************  Bit definition for FLASH_INTR_FLAG register  *****************/
#define FLASH_INTR_FLAG_1                           ((uint8_t)0x1 << 1)
#define FLASH_INTR_FLAG_0                           ((uint8_t)0x1 << 0)

/*******************  Bit definition for FLASH_PL_SEQ register  *****************/
#define FLASH_PAGE_LOCK_SEQ                         ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for FLASH_PAGE_LOCK register  *****************/
#define FLASH_PAGE_LOCK_OFFSET_0                    ((uint32_t)0x1 << 0)
#define FLASH_PAGE_LOCK_OFFSET_1                    ((uint32_t)0x1 << 1)
#define FLASH_PAGE_LOCK_OFFSET_2                    ((uint32_t)0x1 << 2)
#define FLASH_PAGE_LOCK_OFFSET_3                    ((uint32_t)0x1 << 3)
#define FLASH_PAGE_LOCK_OFFSET_4                    ((uint32_t)0x1 << 4)
#define FLASH_PAGE_LOCK_OFFSET_5                    ((uint32_t)0x1 << 5)
#define FLASH_PAGE_LOCK_OFFSET_6                    ((uint32_t)0x1 << 6)
#define FLASH_PAGE_LOCK_OFFSET_7                    ((uint32_t)0x1 << 7)
#define FLASH_PAGE_LOCK_OFFSET_8                    ((uint32_t)0x1 << 8)
#define FLASH_PAGE_LOCK_OFFSET_9                    ((uint32_t)0x1 << 9)
#define FLASH_PAGE_LOCK_OFFSET_10                   ((uint32_t)0x1 << 10)
#define FLASH_PAGE_LOCK_OFFSET_11                   ((uint32_t)0x1 << 11)
#define FLASH_PAGE_LOCK_OFFSET_12                   ((uint32_t)0x1 << 12)
#define FLASH_PAGE_LOCK_OFFSET_13                   ((uint32_t)0x1 << 13)
#define FLASH_PAGE_LOCK_OFFSET_14                   ((uint32_t)0x1 << 14)
#define FLASH_PAGE_LOCK_OFFSET_15                   ((uint32_t)0x1 << 15)
#define FLASH_PAGE_LOCK_OFFSET_16                   ((uint32_t)0x1 << 16)
#define FLASH_PAGE_LOCK_OFFSET_17                   ((uint32_t)0x1 << 17)
#define FLASH_PAGE_LOCK_OFFSET_18                   ((uint32_t)0x1 << 18)
#define FLASH_PAGE_LOCK_OFFSET_19                   ((uint32_t)0x1 << 19)
#define FLASH_PAGE_LOCK_OFFSET_20                   ((uint32_t)0x1 << 20)
#define FLASH_PAGE_LOCK_OFFSET_21                   ((uint32_t)0x1 << 21)
#define FLASH_PAGE_LOCK_OFFSET_22                   ((uint32_t)0x1 << 22)
#define FLASH_PAGE_LOCK_OFFSET_23                   ((uint32_t)0x1 << 23)
#define FLASH_PAGE_LOCK_OFFSET_24                   ((uint32_t)0x1 << 24)
#define FLASH_PAGE_LOCK_OFFSET_25                   ((uint32_t)0x1 << 25)
#define FLASH_PAGE_LOCK_OFFSET_26                   ((uint32_t)0x1 << 26)
#define FLASH_PAGE_LOCK_OFFSET_27                   ((uint32_t)0x1 << 27)
#define FLASH_PAGE_LOCK_OFFSET_28                   ((uint32_t)0x1 << 28)
#define FLASH_PAGE_LOCK_OFFSET_29                   ((uint32_t)0x1 << 29)
#define FLASH_PAGE_LOCK_OFFSET_30                   ((uint32_t)0x1 << 30)
#define FLASH_PAGE_LOCK_OFFSET_31                   ((uint32_t)0x1 << 31)

/******************************************************************************/
/*                                                                            */
/*                                RAM                                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for RAM_FAULT_INTR register  *****************/
#define RAM_FAULT_INTR_FLAG                         ((uint8_t)0x1 << 0)

/*******************  Bit definition for RAM_FAULT_ADDR register  *****************/
#define RAM_FAULT_ADDR_VALUE                        ((uint16_t)0x7FFF << 0)

/******************************************************************************/
/*                                                                            */
/*                                BUZZER                                      */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for BUZZER_CTRL register  *****************/
#define BUZZER_CTRL_N                               ((uint16_t)0x3FF << 3)
#define BUZZER_CTRL_BUZCLK                          ((uint16_t)0x3 << 1)
#define BUZZER_CTRL_BUZEN                           ((uint16_t)0x1 << 0)

/******************************************************************************/
/*                                                                            */
/*                                CRC                                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for CRC_CTRL register  *****************/
#define CRC_CTRL_XOROUT                             ((uint8_t)0x1 << 4)
#define CRC_CTRL_REFOUT                             ((uint8_t)0x1 << 3)
#define CRC_CTRL_REFIN                              ((uint8_t)0x1 << 2)
#define CRC_CTRL_CRC_SEL                            ((uint8_t)0x1 << 1)

/*******************  Bit definition for CRC_RESULT register  *****************/
#define CRC_RESULT_CRC16FLAG                        ((uint32_t)0x1 << 16)
#define CRC_RESULT_CRC16                            ((uint16_t)0xFFFF << 0)
#define CRC_RESULT_CRC32                            ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for CRC_FLAG register  *****************/
#define CRC_FLAG_CRCFLAG                            ((uint8_t)0x1 << 0)

/*******************  Bit definition for CRC_DATA register  *****************/
#define CRC_DATA_CRC32                              ((uint32_t)0xFFFFFFFF << 0)
#define CRC_DATA_CRC16                              ((uint16_t)0xFFFF << 0)

/******************************************************************************/
/*                                                                            */
/*                                DES                                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for DES_CTRL register  *****************/
#define DES_CTRL_RAND_EN                            ((uint16_t)0x3 << 8)
#define DES_CTRL_OP_MODE                            ((uint16_t)0x3 << 5)
#define DES_CTRL_DES_MODE                           ((uint16_t)0x1 << 4)
#define DES_CTRL_KEY_SEL                            ((uint16_t)0x3 << 2)
#define DES_CTRL_ENCRYPT                            ((uint16_t)0x1 << 1)
#define DES_CTRL_START                              ((uint16_t)0x1 << 0)

/*******************  Bit definition for DES_RAND register  *****************/
#define DES_RAND                                    ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for DES_IV_LOW register  *****************/
#define DES_IV_LOW                                  ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for DES_IV_HIGH register  *****************/
#define DES_IV_HIGH                                 ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for DES_DATA_LOW register  *****************/
#define DES_DATA_LOW                                ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for DES_DATA_HIGH register  *****************/
#define DES_DATA_HIGH                               ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for DES_KEY1_LOW register  *****************/
#define DES_KEY1_LOW                                ((uint32_t)0xFFFFFFFF << 0)
#define DES_KEY_LOW                                 ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for DES_KEY1_HIGH register  *****************/
#define DES_KEY1_HIGH                               ((uint32_t)0xFFFFFFFF << 0)
#define DES_KEY_HIGH                                ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for DES_KEY2_LOW register  *****************/
#define DES_KEY2_LOW                                ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for DES_KEY2_HIGH register  *****************/
#define DES_KEY2_HIGH                               ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for DES_KEY3_LOW register  *****************/
#define DES_KEY3_LOW                                ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for DES_KEY3_HIGH register  *****************/
#define DES_KEY3_HIGH                               ((uint32_t)0xFFFFFFFF << 0)

/******************************************************************************/
/*                                                                            */
/*                                RNG                                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for RNG_CTRL register  *****************/
#define RNG_CTRL_RUN                                ((uint8_t)0x1 << 1)
#define RNG_CTRL_RNGCIR_EN                          ((uint8_t)0x1 << 0)

/*******************  Bit definition for RNG_MODE register  *****************/
#define RNG_MODE_TRNG_CNT                           ((uint8_t)0x7 << 2)
#define RNG_MODE_TRNG_FDBK                          ((uint8_t)0x1 << 1)
#define RNG_MODE_TRNG_LOAD                          ((uint8_t)0x1 << 0)

/*******************  Bit definition for RNG_DATA_LOW register  *****************/
#define RNG_DATA_LOW                                ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for RNG_DATA_HIGH register  *****************/
#define RNG_DATA_HIGH                               ((uint32_t)0xFFFFFFFF << 0)

/******************************************************************************/
/*                                                                            */
/*                                LCD                                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for LCD_RAMxL register  *****************/
#define LCD_RAMxL                                   ((uint32_t)0xFFFFFFFF << 0)

/*******************  Bit definition for LCD_RAM_0_1_2_3H register  *****************/
#define LCD_RAM_0_1_2_3H                            ((uint32_t)0xFFFFFF << 0)

/*******************  Bit definition for LCD_RAM_4_5H register  *****************/
#define LCD_RAM_4_5H                                ((uint32_t)0x3FFFFF << 0)

/*******************  Bit definition for LCD_RAM_6_7H register  *****************/
#define LCD_RAM_6_7H                                ((uint32_t)0xFFFFF << 0)

/*******************  Bit definition for LCD_CTRL register  *****************/
#define LCD_CTRL_LCDINT                             ((uint32_t)0x1 << 18)
#define LCD_CTRL_FC                                 ((uint32_t)0xF << 14)
#define LCD_CTRL_INTEN                              ((uint32_t)0x1 << 13)
#define LCD_CTRL_BLK                                ((uint32_t)0x1 << 12)
#define LCD_CTRL_IRH                                ((uint32_t)0x1 << 11)
#define LCD_CTRL_IRL                                ((uint32_t)0x1 << 10)
#define LCD_CTRL_CPEN                               ((uint32_t)0x1 << 9)
#define LCD_CTRL_MODE                               ((uint32_t)0x7 << 6)
#define LCD_CTRL_BIAS                               ((uint32_t)0x1 << 5)
#define LCD_CTRL_CPCLKSEL                           ((uint32_t)0x3 << 3)
#define LCD_CTRL_FRM                                ((uint32_t)0x3 << 1)
#define LCD_CTRL_LCDEN                              ((uint32_t)0x1 << 0)

/******************************************************************************/
/*                                                                            */
/*                                PMU                                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for PMU_CTRL register  *****************/
#define PMU_CTRL_PDC                                ((uint16_t)0xFFFF << 0)

/******************************************************************************/
/*                                                                            */
/*                                	RMU                                         */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for RMU_RESET_FLAG register  *****************/
#define RMU_RESET_FLAG_WDT_PD                       ((uint16_t)0x1 << 14)
#define RMU_RESET_FLAG_VC_PD                        ((uint16_t)0x1 << 13)
#define RMU_RESET_FLAG_RTC_PD                       ((uint16_t)0x1 << 12)
#define RMU_RESET_FLAG_LVD_PD                       ((uint16_t)0x1 << 11)
#define RMU_RESET_FLAG_PORT_PD                      ((uint16_t)0x1 << 10)
#define RMU_RESET_FLAG_BASETIMER_PD                 ((uint16_t)0x1 << 9)
#define RMU_RESET_FLAG_PD                           ((uint16_t)0x1 << 8)
#define RMU_RESET_FLAG_LVD_RST                      ((uint16_t)0x1 << 7)
#define RMU_RESET_FLAG_SYSREQ_RST                   ((uint16_t)0x1 << 6)
#define RMU_RESET_FLAG_LOOKUP_RST                   ((uint16_t)0x1 << 5)
#define RMU_RESET_FLAG_PCA_RST                      ((uint16_t)0x1 << 4)
#define RMU_RESET_FLAG_WDT_RST                      ((uint16_t)0x1 << 3)
#define RMU_RESET_FLAG_RSTP                         ((uint16_t)0x1 << 2)
#define RMU_RESET_FLAG_CORE_POR                     ((uint16_t)0x1 << 1)
#define RMU_RESET_FLAG_AO_POR                       ((uint16_t)0x1 << 0)

/*******************  Bit definition for RMU_PERI_RESET0 register  *****************/
#define RMU_PERI_RESET0_RNG                         ((uint32_t)0x1 << 29)
#define RMU_PERI_RESET0_DES                         ((uint32_t)0x1 << 27)
#define RMU_PERI_RESET0_ADC                         ((uint32_t)0x1 << 26)
#define RMU_PERI_RESET0_BUZZER                      ((uint32_t)0x1 << 25)
#define RMU_PERI_RESET0_CRC                         ((uint32_t)0x1 << 23)
#define RMU_PERI_RESET0_DMA                         ((uint32_t)0x1 << 22)
#define RMU_PERI_RESET0_FLASH                       ((uint32_t)0x1 << 21)
#define RMU_PERI_RESET0_PCA4                        ((uint32_t)0x1 << 20)
#define RMU_PERI_RESET0_PCA3                        ((uint32_t)0x1 << 19)
#define RMU_PERI_RESET0_PCA2                        ((uint32_t)0x1 << 18)
#define RMU_PERI_RESET0_PCA1                        ((uint32_t)0x1 << 17)
#define RMU_PERI_RESET0_TIMER4                      ((uint32_t)0x1 << 16)
#define RMU_PERI_RESET0_TIMER3                      ((uint32_t)0x1 << 15)
#define RMU_PERI_RESET0_TIMER2                      ((uint32_t)0x1 << 14)
#define RMU_PERI_RESET0_TIMER1                      ((uint32_t)0x1 << 13)
#define RMU_PERI_RESET0_SCI7816                     ((uint32_t)0x1 << 12)
#define RMU_PERI_RESET0_I2C2                        ((uint32_t)0x1 << 11)
#define RMU_PERI_RESET0_I2C1                        ((uint32_t)0x1 << 10)
#define RMU_PERI_RESET0_SPI4                        ((uint32_t)0x1 << 9)
#define RMU_PERI_RESET0_SPI3                        ((uint32_t)0x1 << 8)
#define RMU_PERI_RESET0_SPI2                        ((uint32_t)0x1 << 7)
#define RMU_PERI_RESET0_SPI1                        ((uint32_t)0x1 << 6)
#define RMU_PERI_RESET0_UART6                       ((uint32_t)0x1 << 5)
#define RMU_PERI_RESET0_UART5                       ((uint32_t)0x1 << 4)
#define RMU_PERI_RESET0_UART4                       ((uint32_t)0x1 << 3)
#define RMU_PERI_RESET0_UART3                       ((uint32_t)0x1 << 2)
#define RMU_PERI_RESET0_UART2                       ((uint32_t)0x1 << 1)
#define RMU_PERI_RESET0_UART1                       ((uint32_t)0x1 << 0)

/*******************  Bit definition for RMU_PERI_RESET1 register  *****************/
#define RMU_PERI_RESET1_LCD                         ((uint8_t)0x1 << 5)
#define RMU_PERI_RESET1_WDT                         ((uint8_t)0x1 << 4)
#define RMU_PERI_RESET1_BASETIMER                   ((uint8_t)0x1 << 3)
#define RMU_PERI_RESET1_RTC                         ((uint8_t)0x1 << 2)
#define RMU_PERI_RESET1_PORT                        ((uint8_t)0x1 << 1)
#define RMU_PERI_RESET1_BKRAM                       ((uint8_t)0x1 << 0)

/******************************************************************************/
/*                                                                            */
/*                           SYSTICK TIMER                                    */
/*                                                                            */
/******************************************************************************/
/*******************  Bit definition for SYSTICK_TIMER register  *****************/
#define SYSTICK_TIMER_CLK_SEL                       ((uint32_t)0x3 << 26)                                 
#define SYSTICK_TIMER_NOREF                           ((uint32_t)0x1 << 25) 
#define SYSTICK_TIMER_SKEW                          ((uint32_t)0x1 << 24) 
#define SYSTICK_TIMER_STCALIB                       ((uint32_t)0xFFFFFF << 0) 

/* --------------------  End of section using anonymous unions  ------------------- */
#if   defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif

#ifdef USE_STDPERIPH_DRIVER
  #include "GW32L0xx_conf.h"
#endif

//======================================================
#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))


#ifdef __cplusplus
}
#endif

#endif  /* ARMCM0plus_H */
