#ifndef __UART_H__
#define __UART_H__

#include "GW32L.h"

#define USER_UART_PERIPH_CLOCK	CMU_APBPeriph0_UART5
#define USER_UARTx							UART_5
#define USER_UART_PORT					PORT_6
#define USER_UART_PINT					PORT_Pin_1
#define USER_UART_PINR					PORT_Pin_0
#define USER_UART_IRQ						UART5_IRQn
#define USER_UART_IRQ_HEADER		UART5_IRQHandler
// void uart_init(void);
// void send_byte(u8 d);
// void send_str(u8 *buf,u8 len);
// void send_num(u8 num);

#endif



