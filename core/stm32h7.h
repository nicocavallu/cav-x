#ifndef STM32H7_H
#define STM32H7_H

#include <stdint.h>

// GPIOA
#define GPIOA_BASE 0x58020000UL
#define GPIOA_MODER (*(volatile uint32_t *)(GPIOA_BASE + 0x00)) 
#define GPIOA_OSPEEDR (*(volatile uint32_t *)(GPIOA_BASE + 0x08)) 
#define GPIOA_ODR (*(volatile uint32_t*)(GPIOA_BASE + 0x14))
#define GPIOA_AFRL (*(volatile uint32_t *)(GPIOA_BASE + 0x20))

// GPIOB 
#define GPIOB_BASE 0x58020400UL  
#define GPIOB_MODER (*(volatile uint32_t*)(GPIOB_BASE + 0x00))
#define GPIOB_OSPEEDR (*(volatile uint32_t *)(GPIOB_BASE + 0x08)) 
#define GPIOB_ODR (*(volatile uint32_t*)(GPIOB_BASE + 0x14))
#define GPIOB_AFRL (*(volatile uint32_t *)(GPIOB_BASE + 0x20))

// GPIOD
#define GPIOD_BASE 0x58020C00UL
#define GPIOD_MODER (*(volatile uint32_t *)(GPIOD_BASE + 0x00)) 
#define GPIOD_AFRH (*(volatile uint32_t *)(GPIOD_BASE + 0x24)) 

// RCC
#define RCC_BASE 0x58024400UL
#define RCC_CR (*(volatile uint32_t*)(RCC_BASE + 0x00))
#define RCC_D2CCIP1R (*(volatile uint32_t*)(RCC_BASE + 0x050))
#define RCC_C1_AHB1ENR (*(volatile uint32_t*)(RCC_BASE + 0x138))
#define RCC_C1_AHB2ENR (*(volatile uint32_t*)(RCC_BASE + 0x13C))
#define RCC_C1_AHB4ENR (*(volatile uint32_t*)(RCC_BASE + 0x140))
#define RCC_C1_APB1LENR1 (*(volatile uint32_t*)(RCC_BASE + 0x148))
#define RCC_C1_APB2ENR (*(volatile uint32_t*)(RCC_BASE + 0x150))


//ISR
#define NVIC_ISER ((volatile uint32_t*)0xE000E100)
#define NVIC_IPR ((volatile uint8_t*)0xE000E400)

#endif // STM32H7_H