/*
This is the startup code for the HAL-based embedded system. 
It is responsible for initializing the system and providing the necessary infrastructure for the application to run.
It contains the reset handler, which is the entry point of the program after a reset
It also contains the default interrupt handlers, which can be overridden by the user
*/

#include <stdint.h>

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


// Entry point for the program (Defined in linker script)
void reset_handler(void) 
{   
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
    __libc_init_array();

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
