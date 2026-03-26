#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include "stm32h7.h"

// NVIC 
extern volatile uint32_t sys_tick;

// TIM2
#define TIM2_BASE 0x40000000UL
#define TIM2_CR1 (*(volatile uint32_t *)(TIM2_BASE + 0x00))
#define TIM2_DIER (*(volatile uint32_t *)(TIM2_BASE + 0x0C))
#define TIM2_SR (*(volatile uint32_t *)(TIM2_BASE + 0x10))
#define TIM2_EGR (*(volatile uint32_t *)(TIM2_BASE + 0x14))
#define TIM2_CNT (*(volatile uint32_t *)(TIM2_BASE + 0x24))
#define TIM2_PSC (*(volatile uint32_t *)(TIM2_BASE + 0x28))
#define TIM2_ARR (*(volatile uint32_t *)(TIM2_BASE + 0x2C))

// IRQ
#define TIM2_IRQ 28

// Function Prototypes
void tim2_init(void);
uint32_t get_sys_tick(void);
void TIM2_IRQHandler(void);
void delay_ms(uint32_t ms);

// 
#endif //TIMER_H