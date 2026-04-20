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

// PWM Initialization
void tim2pwm_init(void)
{
    // Enable clocks 
    RCC_C1_APB1LENR1 |= (1 << 0);
    RCC_C1_AHB4ENR |= (1 <<0);

    // Set A0 to alternate function 
    GPIOA_MODER &= ~(3 << 0);
    GPIOA_MODER |= (2 << 0);
    GPIOA_AFRL &= ~(0xF << 0);
    GPIOA_AFRL |= (1 << 0);

    // Set Prescaler and ARR 
    TIM2_PSC &= 0;
    TIM2_ARR = 255;

    // Configure and enable pwm 
    TIM2_CCMR1 &= ~((1 << 13) | (1 << 4));
    TIM2_CCMR1 |= (3 << 5) | (1 << 3);
    TIM2_CCER |= (1 << 0);
    TIM2_CR1 |= (1 << 0);
}

void tim2_set_duty(uint8_t duty)
{
    // Set PWM1 to Duty
    TIM2_CCR1 = duty;
}
