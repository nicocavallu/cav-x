/* Simple blink script for a GPIO pin to test vector table*/

#include <stdint.h>
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
    //Enable clock for GPIOB 
    RCC_AHB4ENR |= (1 << 1);

    // Force clock to wait before setting pins for stability 
    for(volatile int i = 0; i<10000; i++);

    // Set moder to output mode 
    GPIOB_MODER &= ~(3 << 0);
    GPIOB_MODER |= (1 << 0);

    // Turn ODR[0] high and low 
    while(1)
    {
        GPIOB_ODR |= (1 << 0);
        delay(10000000);
        GPIOB_ODR &= ~(1 << 0);
        delay(10000000);
    } 
}