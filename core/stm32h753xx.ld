/*
Linker file for STM32H753xx series of microcontrollers. 
This file defines the memory layout and sections for the linker to use when building the firmware. 
It specifies the flash memory, RAM, and other memory regions, as well as the placement of code and data sections.

Reference:
https://sourceware.org/binutils/docs/ld/index.html#SEC_Contents

*/

/* Define Entry Point */
ENTRY(reset_handler)

/* Define Memory Regions */
MEMORY
{
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 2M

  DTCM (rwx) : ORIGIN = 0X20000000, LENGTH = 128k

  ITCM (rwx) : ORIGIN = 0x00000000, LENGTH = 64k

  AXISRAM (rwx) : ORIGIN = 0x24000000, LENGTH = 512k

}

/* Define Sections */
SECTIONS
{
    /* All sections are aligned to 4 bytes  because the STM Processor likes it that way*/

    /* Define Stack */
    _estack = ORIGIN(DTCM) + LENGTH(DTCM); 

    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);

    } > FLASH

    .text :
    {
        . = ALIGN(4);
        *(.text)
        *(.text*)
        *(.rodata)
        *(.rodata*)
        . = ALIGN(4);
    } > FLASH

    /* ARM Exception and other stuff for using libraries*/
    .ARM.extab :
    {
        *(.ARM.extab* .gnu.linkonce.armextab.*)
    } > FLASH

    .ARM :
    {
        __exidx_start = .;
        *(.ARM.exidx*)
        __exidx_end = .;
    }

    .preinit_array :
    {
        PROVIDE_HIDDEN (__preinit_array_start = .);
        KEEP(*(.preinit_array*))
        PROVIDE_HIDDEN (__preinit_array_end = .);
    } > FLASH

    .init_array :
    {
        PROVIDE_HIDDEN (__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array*))
        PROVIDE_HIDDEN (__init_array_end = .);
    } > FLASH

    .fini_array :
    {
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array*))
        PROVIDE_HIDDEN (__fini_array_end = .);
    } > FLASH

    .data :
    {
        . = ALIGN(4);
        _sdata = .; 
        *(.data)
        *(.data*)
        . = ALIGN(4);
        _edata = .;
    } > AXISRAM AT > FLASH /* AT is telling the linker to execute the code in data (VMA) and to place the code in flash (LMA) */

    _sidata = LOADADDR(.data); /* location of data section in stack */

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _ebss = .;
    } > AXISRAM

    /* Check for stack overflow */
    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE (end = .);
        PROVIDE ( _end = .);
         . = . + 0x200; /* 512 bytes for heap */
         . = . + 0x400; /* 1KB for stack */
         . = ALIGN(8);
    } > DTCM
}