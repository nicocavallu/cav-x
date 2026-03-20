/*Simple Code to Set PD8 & PD9 to UART TX and RX Pins and transmit to linux machine*/

#include <stdint.h>
#include "uart.h"

// Initialize uart 
void uart_init(void)
{
    // Enable clocks 
    RCC_AHB4ENR |= (1 << 3);
    RCC_APB1ENR1 |= (1 << 18);

    // Set PD8 and PD9 to altenate function
    GPIOD_MODER &= ~(15 << 16);
    GPIOD_MODER |= (10 << 16);

    // Enable UART tx and rx
    GPIOD_AFRH &= ~(255 << 0);
    GPIOD_AFRH |= (119 << 0);

    // Set Baud Rate 
    USART3_BRR = 556; // 64MHz/115200

    //Enable UART Reciever and Transmitter 
    USART3_CR1 |= (13 << 0);
}

void uart_tx_char(void)
{
    
}