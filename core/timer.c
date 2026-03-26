/*Initialize timer 2 as hardware timer for system*/

#include <stdint.h>
#include "timer.h"

// Set system clock to 0
volatile uint32_t sys_tick = 0;

// Initialize timer 
void tim2_init(void)
{
    // Enable clock 
    RCC_C1_APB1LENR1 |= (1 << 0);
    volatile uint32_t dummy = RCC_C1_APB1LENR1;
    (void)dummy;

    // Configure clock
    TIM2_PSC = 64 - 1;
    TIM2_ARR = 1000 - 1;
    TIM2_DIER |= (1 << 0);
    TIM2_EGR |= (1 << 0);

    // Configure NVIC
    NVIC_ISER[TIM2_IRQ/32] |= (1 << (TIM2_IRQ % 32));
    NVIC_IPR[TIM2_IRQ] |= 0x10;

    // Enable interrupt 
    TIM2_CR1 |= (1 << 0);
 }

 // Timer interrupt  
void TIM2_IRQHandler(void)
{
    // Check if timer flag was triggered 
    if (TIM2_SR & (1 << 0))
    {
        TIM2_SR &= ~(1 << 0);
        sys_tick++;
    }
}

uint32_t get_sys_tick(void)
{
    return sys_tick;
}

// Millisecond delay using the hardware timer
void delay_ms(uint32_t ms)
{
    uint32_t start = get_sys_tick();
    
    while ((get_sys_tick() - start) < ms)
    {
        // Wait here
    }
}
