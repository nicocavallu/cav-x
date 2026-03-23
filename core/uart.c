/*Driver to Set PD8 & PD9 to UART TX and RX Pins and transmit to linux machine*/

#include <stdint.h>
#include <sys/stat.h>
#include <errno.h>
#include "uart.h"

volatile char rx_buffer[RX_BUFFER_SIZE]__attribute__((section(".dma_buffer")));
volatile uint16_t rx_head = 0;
volatile uint16_t rx_tail = 0;

// Initialize uart 
void uart3_init(void)
{
    // Enable clocks 
    RCC_AHB1ENR |= (1 << 0);
    RCC_AHB4ENR |= (1 << 3);
    RCC_APB1ENR1 |= (1 << 18);

    // Set PD8 and PD9 to altenate function
    GPIOD_MODER &= ~(15 << 16);
    GPIOD_MODER |= (10 << 16);

    // Set DMAMUX
    DMAMUX1_C0CR = DMAMUX_REQ_USART3_RX;

    // Configure DMA 
    DMA1_S0CR &= ~(1 << 0);
    while(DMA1_S0CR & (1 << 0));;
    DMA1_S0PAR = (uint32_t)&USART3_RDR;
    DMA1_S0M0AR = (uint32_t)rx_buffer;
    DMA1_S0NDTR = RX_BUFFER_SIZE;
    DMA1_S0CR &= ~(3 << 6);
    DMA1_S0CR |= (5 << 8);
    DMA1_S0CR |= (1 << 0);

    // Enable UART tx and rx
    GPIOD_AFRH &= ~(255 << 0);
    GPIOD_AFRH |= (119 << 0);

    // Set Baud Rate 
    USART3_BRR = 556; // 64MHz/115200

    //Initialize UART interrupt 
    USART3_CR1 &= ~(1 << 0);
    USART3_CR1 |=  (1 << 2) | (1 << 3) | (1 << 4);
    USART3_CR1 &=  ~(1 << 5);
    USART3_CR3 |= (1 << 6);
    USART3_CR1 |= (1 << 0);

    // Configure NVIC 
    // Enable USART3 Interrupt 
    NVIC_ISER[USART3_IRQ/32] |= (1 << (USART3_IRQ % 32));

    // Set IP 
    NVIC_IPR[USART3_IRQ] |= 0x50;

    // Enable global interrupts
    __asm volatile ("cpsie i" : : : "memory");
}

void uart3_tx_char(char c)
{
    // Poll TXE bit 
    while (!(USART3_ISR & (1 << 7)))
    {
        // Wait for hardware
    } 

    // Set TDR to char 
    USART3_TDR = c;

}

void uart3_print(char *str)
{
    while(*str)
    {
        uart3_tx_char(*str++);
    }
}

char uart3_rx_char(void)
{
    // Poll RXNE bit 
    while (rx_head == rx_tail)
    {
        // Wait for hardware
    } 

    // Read RDR register
    char c = rx_buffer[rx_tail];
    rx_tail = (rx_tail + 1) % RX_BUFFER_SIZE; 
    return c;

}

void uart3_rx_string(char *buffer, uint32_t maxLen)
{
    // Initialize buffer 
    uint32_t i = 0;
    char c;

    
    while (i < (maxLen - 1))
    {
        c = uart3_rx_char();

        // Check for null terminator 
        if (c == '\r' || c == '\n' || c == '\0')
        {
            break;
        }

        // echo back char 
        uart3_tx_char(c);

        // Add to buffer
        buffer[i] = c;
        i++;
    }

    // Add null terminator 
    buffer[i] = '\0';

}

/*
    Reformat printf via the _write function
    * _write is the "system call" used by printf to output data.
    * file: The file descriptor (1 is stdout, 2 is stderr)
    * ptr:  The buffer of characters created by printf
    * len:  The number of characters in the buffer
*/

int _write(int file, char *ptr, int len)
{
    // Check if stdout or stderr
    if (file == 1 || file == 2)
    {
        // Increment through string 
        for (int i = 0; i < len; i++)
        {
            // Make sure to row align for each new line 
            if (ptr[i] == '\n')
            {
                uart3_tx_char('\r');
            }

            uart3_tx_char(ptr[i]);
        }

        return len;
    }

    errno = EBADF;
    return -1;
}

// UART interupt handler 
void USART3_IRQHandler(void)
{
    // Clear ORE 
    if (USART3_ISR & (1 << 3))
    {
        USART3_ICR |= (1 << 3); 
    }

    // Check if IDLE is set 
    if (USART3_ISR & (1 << 4))
    {
        // Write to hardware 
        USART3_ICR |= (1 << 4);

        // Incremenet buffer 
        uint16_t dma_index = RX_BUFFER_SIZE - DMA1_S0NDTR;

        rx_head = dma_index % RX_BUFFER_SIZE;
    }

}