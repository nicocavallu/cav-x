#ifndef UART_H
#define UART_H

#include <stdint.h>
#include "stm32h7.h"

// USART3
#define USART3_BASE 0x40004800UL
#define USART3_CR1 (*(volatile uint32_t*)(USART3_BASE + 0x00))
#define USART3_CR3 (*(volatile uint32_t*)(USART3_BASE + 0x08))
#define USART3_BRR (*(volatile uint32_t*)(USART3_BASE + 0x0C))
#define USART3_ISR (*(volatile uint32_t*)(USART3_BASE + 0x1C))
#define USART3_ICR (*(volatile uint32_t*)(USART3_BASE + 0x20))
#define USART3_RDR (*(volatile uint32_t*)(USART3_BASE + 0x24))
#define USART3_TDR (*(volatile uint32_t*)(USART3_BASE + 0x28))

// Function Prototypes
void uart3_init(void);
void uart3_tx_char(char c);
char uart3_rx_char(void);
void uart3_print(char *str);
void uart3_rx_string(char *buffer, uint32_t maxLen);
void USART3_IRQHandler(void);

// Global variables 
#define RX_BUFFER_SIZE 128
extern volatile char rx_buffer[RX_BUFFER_SIZE];
extern volatile uint16_t rx_head;
extern volatile uint16_t rx_tail;

#endif // UART_H