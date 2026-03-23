/* Main -- Curently for testing functions */
#include <stdint.h>
#include <string.h> 
#include <stdio.h>
#include "uart.h"


// Define Register Addresses 
#define GPIOB_BASE 0x58020400UL  
#define GPIOB_MODER (*(volatile uint32_t*)(GPIOB_BASE + 0x00))
#define GPIOB_ODR (*(volatile uint32_t*)(GPIOB_BASE + 0x14))

#define RCC_BASE 0x58024400UL
#define RCC_AHB4ENR (*(volatile uint32_t*)(RCC_BASE + 0x140))


//Initialize user functions 
int main(void);
void delay(volatile uint32_t count);

// Delay Function 
void delay(volatile uint32_t count)
{
    while(count--);
}

//Blink GPIOB Pin 0 - Green LD1 
int main(void)
{
    // 1. Initialize the UART (This now fires up the DMA and DMAMUX!)
    uart3_init();

    // Initialize LED on PB0 (Optional)
    RCC_AHB4ENR |= (1 << 1); 
    GPIOB_MODER &= ~(3 << 0);
    GPIOB_MODER |=  (1 << 0);

    // 2. Test standard TX
    uart3_print("\r\n=================================\r\n");
    uart3_print("STM32H7 DMA UART is ONLINE.\r\n");
    uart3_print("Type a message and stop typing to trigger IDLE interrupt...\r\n");
    uart3_print("=================================\r\n");

    // Create a local buffer for processing the string
    char input_buffer[64];

    while(1) 
    {
        // 3. Wait for the string
        // The CPU will wait here doing nothing. 
        // As you type, the DMA secretly fills rx_buffer in the background.
        // When you stop typing, the IDLE interrupt fires, updates rx_head, and this function unblocks!
        uart3_rx_string(input_buffer, sizeof(input_buffer));

        // 4. Prove we got it!
        uart3_print("\r\n[CPU Processed]: ");
        uart3_print(input_buffer);
        uart3_print("\r\n\n");

        // Toggle LED to show we processed a full string
        GPIOB_ODR ^= (1 << 0);
    }
}