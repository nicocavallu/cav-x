/* Main -- Curently for testing functions */
#include <stdint.h>
#include <string.h> 
#include <stdio.h>

#include "uart.h"
#include "timer.h"
#include "spi.h"

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
    tim2_init();
    spi1_init();

    // Initialize LED on PB0 (Optional)
    RCC_C1_AHB4ENR |= (1 << 1); 
    GPIOB_MODER &= ~(3 << 0);
    GPIOB_MODER |=  (1 << 0);

    uint8_t tx_byte = 0x00;
    uint8_t rx_byte;
    __asm volatile ("cpsie i" : : : "memory");

    while(1)
    {
        rx_byte = spi1_transfer(tx_byte);
        printf("TX: 0x%02X | RX: 0x%02X\r\n", tx_byte, rx_byte);

        if (rx_byte == tx_byte)
        {
            GPIOB_ODR |= (1 << 0);     // LED ON
            delay_ms(1000);          // Wait ~0.5 seconds
            GPIOB_ODR &= ~(1 << 0);    // LED OFF
            delay_ms(1000); 
        }
        else 
        {
            GPIOB_ODR &= ~(1 << 0);    // Keep OFF if wire is unplugged
        }

        tx_byte++;
        
        //delay(10000000); // Wait ~0.5 seconds before next transfer
    }
}