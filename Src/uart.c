/*
 * uart.c
 *
 *  Created on: 11 Jun 2026
 *      Author: glenk
 */

#include "uart.h"
#include "stm32f407vgtx.h"

void uart_init(void) {
	// Enabling clock to GPIOD
	RCC->AHB1ENR |= (1 << 3);

	// Enabling clock to USART2 (17th bit in RCC_APB1ENR register)
	RCC->APB1ENR |= (1 << 17);

	// Setting PD5 to alternate function mode
	GPIOD->MODER &= ~(3 << 4); // clear
	GPIOD->MODER |= (2 << 4); // set to 10

	// Setting AF7 (USART2_TX) to PD5
	GPIOD->AFR[0] &= ~(0xF << 20); // clear
	GPIOD->AFR[0] |= (0x7 << 20);  // set

	// Configuting BRR (Baud Rate Divisor = clock feed USART2 (frequency at which APB1 is running) / baud rate)
	// = 16MHz / 115200 = 139
	USART2->BRR = 139;

	// Configuring CR1 to enable USART2 (bit 13)
	USART2->CR1 |= (1 << 13);

	// Configuring CR1 to enable transmission (bit 3)
	USART2->CR1 |= (1 << 3);
}

void uart_send_char(char data) {
	// Check TXE on SR. If set to 1, write char to DR. If 0 keep checking
	// Transmission of data from shift registers to laptop is handled internally by USART
	while (!(USART2->SR & (1 << 7)));
	USART2->DR = data;
}

void uart_send_string(const char* str) {
	// for sending fixed string messages
	while (*str != '\0') {
		uart_send_char(*str);
		str++;
	}
}
