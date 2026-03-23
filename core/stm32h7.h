#ifndef STM32H7_H
#define STM32HY_H

#include <stdint.h>

// GPIOD
#define GPIOD_BASE 0x58020C00UL
#define GPIOD_MODER (*(volatile uint32_t *)(GPIOD_BASE + 0x00)) 
#define GPIOD_AFRH (*(volatile uint32_t *)(GPIOD_BASE + 0x24)) 

// RCC
#define RCC_BASE 0x58024400UL
#define RCC_C1_AHB1ENR (*(volatile uint32_t*)(RCC_BASE + 0x138))
#define RCC_C1_AHB4ENR (*(volatile uint32_t*)(RCC_BASE + 0x140))
#define RCC_C1_APB1LENR1 (*(volatile uint32_t*)(RCC_BASE + 0x148))

//ISR
#define NVIC_ISER ((volatile uint32_t*)0xE000E100)
#define NVIC_IPR ((volatile uint8_t*)0xE000E400)

#endif // STM32HY_H