/*
This is the startup code for the HAL-based embedded system. 
It is responsible for initializing the system and providing the necessary infrastructure for the application to run.
It contains the reset handler, which is the entry point of the program after a reset
It also contains the default interrupt handlers, which can be overridden by the user
*/

#include <stdint.h>

// Define CPACR Register 
#define CPACR (*(volatile uint32_t *)(0xE000ED88))

// Define the symbols used in the linker script (32 bits is STM preferred word size)
extern uint32_t _estack;
extern uint32_t _sdata;
extern uint32_t _edata;
extern uint32_t _sbss;
extern uint32_t _ebss;
extern uint32_t _sidata;
extern uint32_t __exidx_start;
extern uint32_t __exidx_end;
extern uint32_t __preinit_array_start;
extern uint32_t __preinit_array_end;
extern uint32_t __init_array_start;
extern uint32_t __init_array_end;
extern uint32_t __fini_array_start;
extern uint32_t __fini_array_end;

// GNU Library Func 
extern void __libc_init_array(void);

// Func Prototypes 
void reset_handler(void);
void default_handler(void);
extern int main(void);

// Alias for standard ARM exceptions  (Table 145 NVIC pg. 750)
void NMI_handler(void) __attribute__((weak, alias("default_handler")));
void HardFault_handler(void) __attribute__((weak, alias("default_handler")));
void MemManage_handler(void) __attribute__((weak, alias("default_handler")));
void BusFault_handler(void) __attribute__((weak, alias("default_handler")));
void UsageFault_handler(void) __attribute__((weak, alias("default_handler")));
void SVCall_handler(void) __attribute__((weak, alias("default_handler")));
void DebugMonitor_handler(void) __attribute__((weak, alias("default_handler")));
void PendSV_handler(void) __attribute__((weak, alias("default_handler")));
void SysTick_handler(void) __attribute__((weak, alias("default_handler")));
void WWDG1_handler(void) __attribute__((weak, alias("default_handler")));
void PVD_PVM_handler(void) __attribute__((weak, alias("default_handler")));
void RTC_TAMP_STAMP_CSS_LSE_handler(void) __attribute__((weak, alias("default_handler")));
void RTC_WKUP_handler(void) __attribute__((weak, alias("default_handler")));
void FLASH_handler(void) __attribute__((weak, alias("default_handler")));
void RCC_handler(void) __attribute__((weak, alias("default_handler")));

// External Interrupts 
void EXTI0_handler(void) __attribute__((weak, alias("default_handler")));
void EXTI15_10_handler(void) __attribute__((weak, alias("default_handler")));

// Timers 
void TIM2_IRQHandler(void) __attribute__((weak, alias("default_handler")));
void TIM3_handler(void) __attribute__((weak, alias("default_handler")));

// UART/Serial 
void USART1_handler(void) __attribute__((weak, alias("default_handler")));
void USART3_IRQHandler(void) __attribute__((weak, alias("default_handler")));

// I2C 
void I2C1_EV_handler(void) __attribute__((weak, alias("default_handler")));
void I2C1_ER_handler(void) __attribute__((weak, alias("default_handler")));
void I2C2_EV_handler(void) __attribute__((weak, alias("default_handler")));
void I2C2_ER_handler(void) __attribute__((weak, alias("default_handler")));
void I2C3_EV_handler(void) __attribute__((weak, alias("default_handler")));
void I2C3_ER_handler(void) __attribute__((weak, alias("default_handler")));
void I2C4_EV_handler(void) __attribute__((weak, alias("default_handler")));
void I2C4_ER_handler(void) __attribute__((weak, alias("default_handler")));

// SPI
void SPI1_IRQhandler(void) __attribute__((weak, alias("default_handler")));
void SPI2_handler(void) __attribute__((weak, alias("default_handler")));
void SPI3_handler(void) __attribute__((weak, alias("default_handler")));
void SPI4_handler(void) __attribute__((weak, alias("default_handler")));
void SPI5_handler(void) __attribute__((weak, alias("default_handler")));
void SPI6_handler(void) __attribute__((weak, alias("default_handler")));

// DMA
void DMA_STR1_IRQhandler(void) __attribute__((weak, alias("default_handler")));


// Entry point for the program (Defined in linker script)
void reset_handler(void) 
{   
    // Turn on Coproccessors 1 and 2 
    CPACR |= (0xF << 20);
    __asm volatile("dsb");
    __asm volatile("isb");

    // Pointers to the RAM and FLASH
    uint32_t *src, *dst, *endR;
    src = &_sidata;
    dst = &_sdata;
    endR = &_edata;

    // Loop to move FLASH DATA into RAM
    while (dst < endR)
    {
        *dst = *src;

        src++;
        dst++;
    }

    // Zero memory in BSS
    uint32_t *ptrB, *endB;
    ptrB = &_sbss;
    endB = &_ebss;

    while  (ptrB < endB)
    {
        *ptrB = 0;
        ptrB++;
    }

    // Call library function 
    //_libc_init_array();

    // Call main
    main();

    // If main returns, loop forever
    while (1) {}

}

// Safety net for code
void default_handler(void)
{
    while(1) {}
}

// Vector table using GCC Designated Initializers (Table 142 NVIC)
__attribute__((section(".isr_vector")))
void (* const g_pfnVectors[])(void) = {
    
    [0 ... 165] = default_handler,

    // System Exceptions 
    [0] = (void (*)(void))(&_estack), // Main Stack Pointer
    [1]  = reset_handler,            // Entry point
    [2]  = NMI_handler, 
    [3]  = HardFault_handler,
    [4]  = MemManage_handler,
    [5]  = BusFault_handler,
    [6]  = UsageFault_handler,
    [11] = SVCall_handler,
    [12] = DebugMonitor_handler,
    [14] = PendSV_handler,
    [15] = SysTick_handler,

    // STM32 Specific Handlers (Index = 16 + IRQ_Number)    
    [16 + 0]  = WWDG1_handler,
    [16 + 12] = DMA_STR1_IRQhandler,
    [16 + 28] = TIM2_IRQHandler,
    [16 + 29] = TIM3_handler,
    [16 + 37] = USART1_handler,
    [16 + 39] = USART3_IRQHandler, 
};