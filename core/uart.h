#ifndef UART_H
#define UART_H

#include <stdint.h>

// GPIOD
#define GPIOD_BASE 0x58020C00UL
#define GPIOD_MODER (*(volatile uint32_t *)(GPIOD_BASE + 0x00)) 
#define GPIOD_AFRH (*(volatile uint32_t *)(GPIOD_BASE + 0x24)) 

// RCC
#define RCC_BASE 0x58024400UL
#define RCC_AHB4ENR (*(volatile uint32_t*)(RCC_BASE + 0x140))
#define RCC_APB1ENR1 (*(volatile uint32_t*)(RCC_BASE + 0x148))

// USART3
#define USART3_BASE 0x40004800UL
#define USART3_CR1 (*(volatile uint32_t*)(USART3_BASE + 0x00))
#define USART3_BRR (*(volatile uint32_t*)(USART3_BASE + 0x0C))
#define USART3_ISR (*(volatile uint32_t*)(USART3_BASE + 0x1C))
#define USART3_RDR (*(volatile uint32_t*)(USART3_BASE + 0x24))
#define USART3_TDR (*(volatile uint32_t*)(USART3_BASE + 0x28))

// Function Prototypes
void uart3_init(void);
void uart3_tx_char(char c);

#endif // UART_H