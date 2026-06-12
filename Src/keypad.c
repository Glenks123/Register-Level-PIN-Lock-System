/*
 * keypad.c
 *
 *  Created on: 11 Jun 2026
 *      Author: glenk
 */

#include "keypad.h"
#include "stm32f407vgtx.h"

// Pin arrays and keymap
static const uint8_t rows[] = {0, 1, 2, 3};
static const uint8_t cols[] = {8, 9, 10, 11};

static const char keymap[4][4] = {
		{'1', '2', '3', 'A'},
		{'4', '5', '6', 'B'},
		{'7', '8', '9', 'C'},
		{'*', '0', '#', 'D'}
};

void keypad_init(void) {
	// Enabling the peripheral clock of the GPIOD peripheral
	RCC->AHB1ENR |= (1 << 3);

	// Configuring the output pins (ROWS) - PD0, PD1, PD2, PD3
	GPIOD->MODER &= ~(0xFF); // clear
	GPIOD->MODER |= (0x55); // set

	// Configuring the input pins (COLS) - PD8, PD9, PD10, PD11
	GPIOD->MODER &= ~(0xFF << 16);

	// Enabling the internal pull-up resistors for the input pins
	GPIOD->PUPDR &= ~(0xFF << 16); // clear
	GPIOD->PUPDR |= (0x55 << 16); // set

	// Configure the ROWS to HIGH
	GPIOD->ODR |= 0x0F;
}

char keypad_scan(void){
	for (uint8_t r=0; r<4; r++) {
		// Configuring all rows to HIGH
		GPIOD->ODR |= 0x0F;
		// Clearing r'th row to set to LOW
		GPIOD->ODR &= ~(1 << (uint8_t) rows[r]);
		for (uint8_t c=0; c<4; c++) {
			// Checking if the c'th bit in the IDR is LOW. LOW --> button pressed
			if (!(GPIOD->IDR & (1 << (uint8_t) cols[c]))) {
				// Debouncing delay
				for (uint32_t i=0; i<300000; i++);
				// Release wait, to ensure no continuous presses
				while (!(GPIOD->IDR & (1 << (uint8_t) cols[c])));

				return keymap[r][c];
			}
		}
	}
	return 0;
}

