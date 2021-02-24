
#ifndef USART_H
#define	USART_H
#define _XTAL_FREQ 8000000
#define Baud_rate 9600

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdio.h>
#include <stdint.h>

void UART_config();
void UART_send_char(char bt);
void UART_send_string(char* st_pt);
char UART_get_char();

#endif	/* XC_HEADER_TEMPLATE_H */

