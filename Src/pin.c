/*
 * pin.c
 *
 *  Created on: 12 Jun 2026
 *      Author: glenk
 */

#include "pin.h"
#include "stm32f407vgtx.h"
#include "uart.h"
#include <string.h>

static const char stored_pin[] = "1234";
static char entered_pin[4];
static uint8_t input_counter; // counter that keeps track of no. of keypresses / chars entered
static uint8_t attempt_counter;
static uint8_t locked; // lockout flag (true or false)

static void delay(void);

void pin_init(void) {
	// Enable clock to GPIOD
	RCC->AHB1ENR |= (1 << 3);

	// Configuring PD12 (green led -> access granted) & PD14 (red led -> access denied) as output pins
	GPIOD->MODER &= ~((3 << 24) | (3 << 28));
	GPIOD->MODER |= (1 << 24) | (1 << 28);
}

void pin_enter_key(char key) {
	if (locked) return;

	entered_pin[input_counter] = key;
	input_counter++;

	if (input_counter == 4) {
		if (memcmp(entered_pin, stored_pin, 4) == 0) {
			uart_send_string("ACCESS GRANTED.\n");
			GPIOD->ODR |= (1 << 12);
			delay();
			GPIOD->ODR &= ~(1 << 12);
		} else {
			attempt_counter++;
			if (attempt_counter >= 3) {
				locked = 1;
				uart_send_string("LOCKED OUT.\n");

				for (uint8_t i = 0; i < 6; i++) {
				    GPIOD->ODR |= (1 << 12) | (1 << 14);   // both on
				    delay();
				    GPIOD->ODR &= ~((1 << 12) | (1 << 14)); // both off
				    delay();
				}
			} else {
				uart_send_string("ACCESS DENIED.\n");
				GPIOD->ODR |= (1 << 14);
				delay();
				GPIOD->ODR &= ~(1 << 14);
			}
		}
		input_counter = 0;
		return;
	}

}

static void delay(void) {
	for (uint32_t i=0; i<4000000; i++);
}
