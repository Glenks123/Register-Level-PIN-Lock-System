/*
 * stm32f407vgtx.h
 *
 *  Created on: 11 Jun 2026
 *      Author: glenk
 */

#ifndef STM32F407VGTX_H_
#define STM32F407VGTX_H_

#include <stdint.h>

typedef struct {
	volatile uint32_t MODER;    // offset 0x00
	volatile uint32_t OTYPER;   // offsets to 0x04
	volatile uint32_t OSPEEDR;  // offset 0x08
	volatile uint32_t PUPDR;    // offset 0x0C
	volatile uint32_t IDR;      // offset 0x10
	volatile uint32_t ODR;      // offset 0x14
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFR[2];
} GPIO_t;

typedef struct {
	volatile uint32_t CR;
	volatile uint32_t PLLCFGR;
	volatile uint32_t CFGR;
	volatile uint32_t CIR;
	volatile uint32_t AHB1RSTR;
	volatile uint32_t AHB2RSTR;
	volatile uint32_t AHB3RSTR;
	uint32_t RESERVED0;
	volatile uint32_t APB1RSTR;
	volatile uint32_t APB2RSTR;
	uint32_t RESERVED1[2];
	volatile uint32_t AHB1ENR;
	volatile uint32_t AHB2ENR;
	volatile uint32_t AHB3ENR;
	uint32_t RESERVED2;
	volatile uint32_t APB1ENR;
	volatile uint32_t APB2ENR;
} RCC_t;

typedef struct {
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
} USART_t;

#define GPIOD ((GPIO_t*) 0x40020C00)
#define RCC ((RCC_t*) 0x40023800)
#define USART2 ((USART_t*) 0x40004400)

#endif /* STM32F407VGTX_H_ */
