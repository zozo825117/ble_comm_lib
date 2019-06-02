#include "uart.h"
#include "debug.h"

#define LOG

// u8 uart_tx_buf[20];
// u8 uart_rx_buf[20];
// u8 uart_rx_index;
// u8 uart_rx_ok;

// extern u8 rf_tx_len;


// void uart_init(void)
// {
// 	UART_InitTypeDef UART_InitStruct;
	
// 	PORT_InitTypeDef PORT_InitStruct;
	
// 	CMU_APBPeriph1ClockCmd(CMU_APBPeriph1_PORT, ENABLE);
// 	//PORT_DeInit();
// 	PORT_InitStruct.PORT_Pin = USER_UART_PINR; // RX = P6.0
// 	PORT_InitStruct.PORT_Properity = PORT_Properity_Digital;
// 	PORT_InitStruct.PORT_Mode = PORT_Mode_IN;
// 	PORT_InitStruct.PORT_PullHigh = PORT_PH_PullHigh;
// 	PORT_Init(USER_UART_PORT, &PORT_InitStruct);
    
// 	PORT_InitStruct.PORT_Pin = USER_UART_PINT; // TX = P6.1
// 	PORT_InitStruct.PORT_Properity = PORT_Properity_Digital;
// 	PORT_InitStruct.PORT_Mode = PORT_Mode_OUT;
// 	PORT_InitStruct.PORT_OutType = PORT_OutType_PP;
// 	PORT_InitStruct.PORT_PullHigh = PORT_PH_NoPullHigh;
// 	PORT_InitStruct.PORT_DriveSink = PORT_DS_DriveSinkNormal;
// 	PORT_Init(USER_UART_PORT, &PORT_InitStruct);
	
// 	PORT_WriteBit(USER_UART_PORT, USER_UART_PINR, Bit_SET);
// 	PORT_WriteBit(USER_UART_PORT, USER_UART_PINT, Bit_SET);

// 	PORT_PinAFConfig(USER_UART_PORT, PORT_PinSource0, PORT_AF_1); // Port alternative function
// 	PORT_PinAFConfig(USER_UART_PORT, PORT_PinSource1, PORT_AF_1);		
	
// 	CMU_APBPeriph0ClockCmd(USER_UART_PERIPH_CLOCK, ENABLE);
// 	UART_DeInit(USER_UARTx);
// 	UART_StructInit(&UART_InitStruct);
// 	UART_InitStruct.UART_BaudRate = 115200;
// 	UART_InitStruct.UART_DataLength = UART_DataLength_8Bits;
// 	UART_InitStruct.UART_StopBits = UART_StopBits_1Bit;
// 	UART_InitStruct.UART_Parity = UART_Parity_None;
// 	UART_InitStruct.UART_HardwareFlowControl = UART_HardwareFlowControl_None; 	
// 	UART_Init(USER_UARTx, &UART_InitStruct);
	
// 	UART_ITConfig(USER_UARTx, UART_IT_ReceiveData_RXFIFOTimeOutIE, ENABLE);	
// 	UART_ITConfig(USER_UARTx, UART_IT_TXREmptyIE, DISABLE);

// 		__disable_irq();
// 	NVIC_DisableIRQ(USER_UART_IRQ);
// 	NVIC_ClearPendingIRQ(USER_UART_IRQ);
// 	NVIC_SetPriority(USER_UART_IRQ, 0x0);
// 	NVIC_EnableIRQ(USER_UART_IRQ);
// 	__enable_irq();




// }


// void send_byte(u8 d)
// {
// //#if defined(LOG)
//   USER_UARTx->TXR = (d & UART_TXR);
// //#endif
// }

// void send_str(u8 *buf,u8 len)
// {
// //#if defined(LOG)
// 	u8 i;
	
// 	for(i=0;i<len;i++){
//         send_byte(*buf++);
//         while (UART_GetLineStatus(USER_UARTx, UART_LSFLAG_TXEmpty) != SET);
// 	}
// //#endif
// }

// void send_num(u8 num)
// {
// //#if defined(LOG)
// 	u8 num_arry[3];
	
// 	num_arry[0] = num/100 + 0x30;
// 	num_arry[1] = num%100/10 +0x30;
// 	num_arry[2] = num%10 + 0x30;
// 	send_str(num_arry,3);
// //#endif
// }
//u16 uart_time;
//void UART1_Rpt(void) //interrupt UART1_VECTOR
//{
////	if(SCON & 0x01)						//判断接收中断标志位
////	{

//		uart_rx_buf[uart_rx_index++] = SBUF;
//		
//		if(uart_rx_index >= 3 && uart_rx_buf[uart_rx_index-1] == '\n' && uart_rx_buf[uart_rx_index-2] == '\r'){
//			uart_rx_ok = 1;
//			rf_tx_len = uart_rx_index-3;
//		}
//		
//		if(uart_rx_index>18){
//			uart_rx_index = 0;
//		}
////		
////		SCON &=~ 0x01;
////	}									
//}

// void USER_UART_IRQ_HEADER(void)
// {
// 	if (UART_GetITStatus(USER_UARTx, UART_IntID_TXREmpty) == SET)
// 	{
		
// 	}

// 	if (UART_GetITStatus(USER_UARTx, UART_IntID_ReceiveData) == SET)
// 	{
// 		uart_rx_buf[uart_rx_index++] = UART_ReceiveData(USER_UARTx);
		
// 		if(uart_rx_index >= 3 && uart_rx_buf[uart_rx_index-1] == '\n' && uart_rx_buf[uart_rx_index-2] == '\r'){
// 			uart_rx_ok = 1;
// 			rf_tx_len = uart_rx_index-3;
// 			Debug_Print(DEBUG_MESSAGE_LEVEL_4,"uart_rx_ok len = %d\r\n", rf_tx_len);
// 		}
		
// 		if(uart_rx_index>18){
// 			uart_rx_index = 0;
// 		}
// 	}
// }


