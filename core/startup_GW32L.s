;/**************************************************************************//**
; * @file     startup_GW32L.s
; * @brief    CMSIS Core Device Startup File for
; *           GW32L Device Series
; * @version  V1.0.4
; * @date     10-18-2018
; *
; * @note
; *
; ******************************************************************************/
; * COPYRIGHT 2013-2018; Hangzhou GreenWhale technology co., LTD.
;
;   All rights reserved.
;   Redistribution and use in source and binary forms, with or without
;   modification, are permitted provided that the following conditions are met:
;   - Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
;   - Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
;   - Neither the name of ARM nor the names of its contributors may be used
;     to endorse or promote products derived from this software without
;     specific prior written permission.
;   *
;   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
;   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
;   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
;   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
;   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
;   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;   POSSIBILITY OF SUCH DAMAGE.
;   ---------------------------------------------------------------------------*/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000C00

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     DMAC_IRQHandler           
                DCD     P0_IRQHandler             
                DCD     TIMER1_IRQHandler         
                DCD     UART1_IRQHandler      	  
                DCD     SPI1_IRQHandler           
                DCD     I2C1_IRQHandler           
                DCD     RAM_IRQHandler            
                DCD     ADC_IRQHandler            
                DCD     VC_IRQHandler             
                DCD     LVD_IRQHandler            
                DCD     RTC_IRQHandler            
                DCD     BASETIMER_IRQHandler      
                DCD     P1P2_IRQHandler           
                DCD     P3P4_IRQHandler           
                DCD     P5P6_IRQHandler           
                DCD     TIMER2_IRQHandler         
                DCD     TIMER3_IRQHandler         
                DCD     TIMER4_IRQHandler         
                DCD     UART2_IRQHandler          
                DCD     UART3_IRQHandler          
                DCD     UART4_IRQHandler          
                DCD     UART5_IRQHandler          
                DCD     UART6_IRQHandler          
                DCD     SPI2_IRQHandler           
                DCD     SPI3_IRQHandler           
                DCD     SPI4_IRQHandler           
                DCD     I2C2_IRQHandler           
                DCD     PCA12_IRQHandler          
                DCD     PCA34_IRQHandler          
                DCD     WDT_IRQHandler            
                DCD     LCD_IRQHandler            
                DCD     SCI7816_IRQHandler        
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
				IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  DMAC_IRQHandler             [WEAK]
                EXPORT  P0_IRQHandler               [WEAK]
                EXPORT  TIMER1_IRQHandler           [WEAK]
                EXPORT  UART1_IRQHandler      	    [WEAK]
                EXPORT  SPI1_IRQHandler             [WEAK]
                EXPORT  I2C1_IRQHandler             [WEAK]
                EXPORT  RAM_IRQHandler              [WEAK]
                EXPORT  ADC_IRQHandler              [WEAK]
                EXPORT  VC_IRQHandler               [WEAK]
                EXPORT  LVD_IRQHandler              [WEAK]
                EXPORT  RTC_IRQHandler              [WEAK]
                EXPORT  BASETIMER_IRQHandler        [WEAK]
                EXPORT  P1P2_IRQHandler             [WEAK]
                EXPORT  P3P4_IRQHandler             [WEAK]
                EXPORT  P5P6_IRQHandler             [WEAK]
                EXPORT  TIMER2_IRQHandler           [WEAK]
                EXPORT  TIMER3_IRQHandler           [WEAK]
                EXPORT  TIMER4_IRQHandler           [WEAK]
                EXPORT  UART2_IRQHandler            [WEAK]
                EXPORT  UART3_IRQHandler            [WEAK]
                EXPORT  UART4_IRQHandler            [WEAK]
                EXPORT  UART5_IRQHandler            [WEAK]
                EXPORT  UART6_IRQHandler            [WEAK]
                EXPORT  SPI2_IRQHandler             [WEAK]
                EXPORT  SPI3_IRQHandler             [WEAK]
                EXPORT  SPI4_IRQHandler             [WEAK]
                EXPORT  I2C2_IRQHandler             [WEAK]
                EXPORT  PCA12_IRQHandler            [WEAK]
                EXPORT  PCA34_IRQHandler            [WEAK]
                EXPORT  WDT_IRQHandler              [WEAK]
                EXPORT  LCD_IRQHandler              [WEAK]
                EXPORT  SCI7816_IRQHandler          [WEAK]



DMAC_IRQHandler        
P0_IRQHandler          
TIMER1_IRQHandler      
UART1_IRQHandler      	
SPI1_IRQHandler        
I2C1_IRQHandler        
RAM_IRQHandler         
ADC_IRQHandler         
VC_IRQHandler          
LVD_IRQHandler         
RTC_IRQHandler         
BASETIMER_IRQHandler   
P1P2_IRQHandler        
P3P4_IRQHandler        
P5P6_IRQHandler        
TIMER2_IRQHandler      
TIMER3_IRQHandler      
TIMER4_IRQHandler      
UART2_IRQHandler       
UART3_IRQHandler       
UART4_IRQHandler       
UART5_IRQHandler       
UART6_IRQHandler       
SPI2_IRQHandler        
SPI3_IRQHandler        
SPI4_IRQHandler        
I2C2_IRQHandler        
PCA12_IRQHandler       
PCA34_IRQHandler       
WDT_IRQHandler         
LCD_IRQHandler         
SCI7816_IRQHandler  
                B       .

                ENDP


                ALIGN


; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END
