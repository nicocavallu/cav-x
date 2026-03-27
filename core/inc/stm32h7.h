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

// DMA1 
#define DMA1_BASE 0x40020000UL
#define DMA1_LISR  (*(volatile uint32_t*)(DMA1_BASE + 0x00))
#define DMA1_LIFCR (*(volatile uint32_t*)(DMA1_BASE + 0x08))
#define DMA1_S0CR  (*(volatile uint32_t*)(DMA1_BASE + 0x10))
#define DMA1_S0NDTR (*(volatile uint32_t*)(DMA1_BASE + 0x14))
#define DMA1_S0PAR (*(volatile uint32_t*)(DMA1_BASE + 0x18))
#define DMA1_S0M0AR (*(volatile uint32_t*)(DMA1_BASE + 0x1C))
#define DMA1_S1CR  (*(volatile uint32_t*)(DMA1_BASE + 0x10 + 0x18 * 1))
#define DMA1_S1NDTR (*(volatile uint32_t*)(DMA1_BASE + 0x14 + 0x18 * 1))
#define DMA1_S1PAR (*(volatile uint32_t*)(DMA1_BASE + 0x18 + 0x18 * 1))
#define DMA1_S1M0AR (*(volatile uint32_t*)(DMA1_BASE + 0x1C + 0x18 * 1))
#define DMA1_S2CR  (*(volatile uint32_t*)(DMA1_BASE + 0x10 + 0x18 * 2))
#define DMA1_S2NDTR (*(volatile uint32_t*)(DMA1_BASE + 0x14 + 0x18 * 2))
#define DMA1_S2PAR (*(volatile uint32_t*)(DMA1_BASE + 0x18 + 0x18 * 2))
#define DMA1_S2M0AR (*(volatile uint32_t*)(DMA1_BASE + 0x1C + 0x18 * 2))


// DMAMUX1
#define DMAMUX1_BASE 0x40020800UL
#define DMAMUX1_C0CR (*(volatile uint32_t*)(DMAMUX1_BASE + 0x00))
#define DMAMUX1_C1CR (*(volatile uint32_t*)(DMAMUX1_BASE + 0x00 + 0x04 * 1))
#define DMAMUX1_C2CR (*(volatile uint32_t*)(DMAMUX1_BASE + 0x00 + 0x04 * 2))
#define DMAMUX_REQ_SPI1_RX 37
#define DMAMUX_REQ_SPI1_TX 38
#define DMAMUX_REQ_USART3_RX 45

// IRQ
#define DMA1_STR1_IRQ 12
#define SPI1_IRQ 35
#define USART3_IRQ 39


//ISR
#define NVIC_ISER ((volatile uint32_t*)0xE000E100)
#define NVIC_IPR ((volatile uint8_t*)0xE000E400)

#endif // STM32H7_H