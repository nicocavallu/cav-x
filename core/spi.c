/* Implements SPI1 on PA4-PA7 */

#include <stdint.h>
#include <stdio.h>
#include "spi.h"

// Initialize SPI
void spi1_init(void)
{
    // Enable Clocks 
    RCC_C1_AHB4ENR |= (1 << 0);
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

    // Configure role
    SPI1_CR1 |= (1 << 12);
    SPI1_CFG2 |= (1 << 22) | (1 << 26);

    // Enable 
    SPI1_CR1 |= (1 << 0);
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
