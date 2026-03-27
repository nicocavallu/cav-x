/* Implements SPI1 on PA4-PA7 */

#include <stdint.h>
#include <stdio.h>
#include "spi.h"

volatile uint8_t spi1_dma_complete = 0;

// Initialize SPI
void spi1_init(void)
{
    // Enable Clocks 
    RCC_C1_AHB1ENR |= (1 << 0);
    RCC_C1_AHB4ENR |= (1 << 0) | (1<< 1);
    RCC_C1_APB2ENR |= (1 << 12);
    volatile uint32_t dummy = RCC_C1_APB2ENR;
    (void)dummy;

    RCC_CR |= (1 << 1);

    // Route HSI to the SPI kernal clock 
    RCC_D2CCIP1R &= ~(7 << 12);
    RCC_D2CCIP1R |=  (4 << 12);

    // Enable alternate function
    GPIOA_MODER &= ~(0xFF << 8);
    GPIOA_MODER |= (2 << 8) | (2 << 10) | (2 << 12);
    GPIOB_MODER &= ~(3 << 10);
    GPIOB_MODER |=  (2 << 10);

    // Set pins to very high speed 
    GPIOA_OSPEEDR |= (0xFF << 8);
    GPIOB_OSPEEDR |= (3 << 10);

    // Set DMAMUX
    DMAMUX1_C1CR = DMAMUX_REQ_SPI1_RX;
    DMAMUX1_C2CR = DMAMUX_REQ_SPI1_TX;

    // Configure DMA Stream 1
    DMA1_S1CR &= ~(1 << 0);
    while(DMA1_S1CR & (1 << 0));;
    DMA1_S1CR &= ~(3 << 6);
    DMA1_S1CR |= (1 << 10); 
    DMA1_S1CR |= (1 << 4);

    // Configure DMA Stream 2
    DMA1_S2CR &= ~(1 << 0);
    while(DMA1_S2CR & (1 << 0));;
    DMA1_S2CR &= ~(3 << 6);
    DMA1_S2CR |= (1 << 6);
    DMA1_S2CR |= (1 << 10);

    // Set PIns to AF5 
    GPIOA_AFRL &= ~(0xFFFF << 16);
    GPIOA_AFRL |= (5 << 16) | (5 << 20) | (5 << 24);
    GPIOB_AFRL &= ~(0xF << 20);
    GPIOB_AFRL |=  (5 << 20);

    // Disable peripheral to configure
    SPI1_CR1 &= ~(1 << 0);

    // Configure data size and baud rate 
    SPI1_CFG1 &= ~(31 << 0);
    SPI1_CFG1 |= (7 << 0);
    SPI1_CFG1 &= ~(7 << 28);
    SPI1_CFG1 |= (3 << 28);

    // Tell SPI1 to use DMA
    SPI1_CFG1 |= (1 << 14) | (1 << 15);

    // Configure role
    SPI1_CR1 |= (1 << 12);
    SPI1_CFG2 |= (1 << 22) | (1 << 26);

    // Enable 
    SPI1_CR1 |= (1 << 0);

    // Configure NVIC
    NVIC_ISER[SPI1_IRQ/32] |= (1 << (SPI1_IRQ % 32));
    NVIC_ISER[DMA1_STR1_IRQ / 32] |= (1 << (DMA1_STR1_IRQ % 32));

    // Set IP 
    NVIC_IPR[SPI1_IRQ] |= 0x40;
    NVIC_IPR[DMA1_STR1_IRQ] |= 0x40;

    // Enable global interrupts
    __asm volatile ("cpsie i" : : : "memory");
}

// Transmit Data via SPI1
void spi1_transmit(uint8_t data)
{
    // Check if ready to transmit
    while (!(SPI1_SR & (1 << 1)))
    {
        // Wait 
    }
    
    // Transmit data 
    *((volatile uint8_t *)&SPI1_TXDR) = data;   

    // Check if transmit is complete 
    while (!(SPI1_SR & (1 << 2)))
    {
        // Wait
    }

}

// Recieve data 
uint8_t spi1_transfer(uint8_t tx_data)
{
    // Set tsize to one byte 
    SPI1_CR2 = 1;

    // Start clock pulse 
    SPI1_CR1 |= (1 << 9);

    while(!(SPI1_SR & (1 << 1)));

    // Once ready transmit send out dummy 
    *((volatile uint8_t *)&SPI1_TXDR) = tx_data;

     // Wait until TXP has room
    while(!(SPI1_SR & (1 << 0)))
    {
        // wait
    }

    // Read data 
    uint8_t rx_data = *((volatile uint8_t *)&SPI1_RXDR);

    // 6. Wait for the hardware to fully complete the transfer
    while (!(SPI1_SR & (1 << 3))); 
    while (!(SPI1_SR & (1 << 12))); 

    // Clear registers 
    SPI1_IFCR = (1 << 3) | (1 << 4);

    return rx_data;
}

void spi1_dma_transfer(uint8_t *tx_buf, uint8_t *rx_buf, uint16_t length)
{
    // DMA Stream 1
    DMA1_S1CR &= ~(1 << 0);         
    while(DMA1_S1CR & (1 << 0));

    // Set Memory Adress and Length
    DMA1_S1PAR = (uint32_t)&SPI1_RXDR;
    DMA1_S1M0AR = (uint32_t)rx_buf;
    DMA1_S1NDTR = length;

    // DMA Stream 2
    DMA1_S2CR &= ~(1 << 0);           
    while(DMA1_S2CR & (1 << 0));

    // Set Memory Adress and Length
    DMA1_S2PAR = (uint32_t)&SPI1_TXDR;
    DMA1_S2M0AR = (uint32_t)tx_buf;
    DMA1_S2NDTR = length;

    // Enable DMA
    SPI1_CR2 = length;

    // Clear DMA interrupt flags for Stream 1 and Stream 2
    DMA1_LIFCR = (0x3F << 6) | (0x3F << 16); 

    // Enable DMA Streams 
    DMA1_S1CR |= (1 << 0); 
    DMA1_S2CR |= (1 << 0); 

    // Fire the SPI Master Clock 
    SPI1_CR1 |= (1 << 9);
}

void DMA_STR1_IRQhandler(void)
{
    // Transfer Complete
    spi1_dma_complete = 1;

    // Clear Transfer Complete Flag
    DMA1_LIFCR |= (1 << 11);

}
