/*
 * uart.h
 *
 *  Created on: 11 Jun 2026
 *      Author: glenk
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>

void uart_init(void);
void uart_send_char(char data);
void uart_send_string(const char* str);

#endif /* UART_H_ */
