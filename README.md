# Register-Level-PIN-Lock-System

A register-level PIN lock system built on the STM32F407VGTx microcontroller, written entirely in bare-metal C with zero HAL dependencies. Implements a 4x4 matrix keypad scanner, a UART driver, and LED feedback by directly configuring memory-mapped peripheral registers from the STM32F4 reference manual. Features a 3-attempt lockout mechanism and serves as a demonstration of low-level embedded systems programming on an ARM Cortex-M4 processor

## Hardware
- STM32F407VGTx development board
- 4x4 matrix keypad
- USB-to-serial adapter

## Peripherals Used
- GPIOD — keypad rows/columns, LEDs
- USART2 — UART TX at 115200 baud
- RCC — peripheral clock configuration

## Roadmap
- [ ] Migrate keypad input from polling to NVIC interrupt-driven using EXTI lines
      — IRQ handlers, exception model, interrupt priorities

## Build
Developed in STM32CubeIDE. Zero HAL dependencies - all peripheral 
configuration done via direct register access from RM0090.
