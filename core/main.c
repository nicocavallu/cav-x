/* Main -- Curently for testing functions */
#include <stdint.h>
#include <string.h> 
#include <stdio.h>

#include "uart.h"
#include "timer.h"


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
    tim2_init();

    // Initialize LED on PB0 (Optional)
    RCC_C1_AHB4ENR |= (1 << 1); 
    GPIOB_MODER &= ~(3 << 0);
    GPIOB_MODER |=  (1 << 0);

    uint32_t last_print_time = 0;

    while(1)
    {
        uint32_t current_time = get_sys_tick();
        if (current_time - last_print_time >= 1000) 
        { // Has exactly 1000ms passed?
            uart3_print("1 Second has passed!\r\n");
            last_print_time = current_time;
        }
    }
}