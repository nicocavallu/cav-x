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
    // 1. Enable GPIOB Clock for LED
    RCC_AHB4ENR |= (1 << 1); 
    
    // 2. Configure PB0 (Green LED LD1) as Output
    GPIOB_MODER &= ~(3 << 0);
    GPIOB_MODER |=  (1 << 0);

    // 3. Initialize UART & Enable Interrupts
    uart3_init(); 
    
    // 4. Boot Message (Using your custom _write printf!)
    printf("\r\n--- STM32H7 ISR Test Booting ---\r\n");
    printf("Type anything! The main loop is busy blinking...\r\n");

    while(1) 
    {
        // Toggle PB0 (Heartbeat)
        GPIOB_ODR ^= (1 << 0);
        delay(10000000); // Massive delay to prove main loop is "busy"

        // Check if the ISR snuck any characters into our buffer in the background!
        while (rx_head != rx_tail) 
        {
            // Read the character the ISR saved
            char c = rx_buffer[rx_tail];
            
            // Move the tail forward to "consume" the character
            rx_tail = (rx_tail + 1) % RX_BUFFER_SIZE;
            
            // Print it back out to the terminal
            printf("\r\nMain caught ISR char: %c\r\n", c);
        }
    }
}