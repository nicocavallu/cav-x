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

uint8_t tx_data[4] = {0xDE, 0xAD, 0xBE, 0xEF};
uint8_t rx_data[4] = {0};

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

   

    __asm volatile ("cpsie i" : : : "memory");
    spi1_dma_transfer(tx_data, rx_data, 4);

    while(1)
    {
        if (spi1_dma_complete == 1)
        {
            // Reset the flag
            spi1_dma_complete = 0;

            // Do something with rx_data here!
            printf("Got data: %02X %02X\r\n", rx_data[0], rx_data[1]);

            // Maybe trigger the next transfer, or do it based on a timer
            delay_ms(100);
            spi1_dma_transfer(tx_data, rx_data, 4);
            GPIOB_ODR |= (1 << 0);
        }

        delay_ms(1000);          // Wait ~0.5 seconds
        GPIOB_ODR &= ~(1 << 0);    // LED OFF 
    }
}