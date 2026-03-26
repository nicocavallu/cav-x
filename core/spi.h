#ifndef SPI_H
#define SPI_H

#include <stdint.h>
#include "stm32h7.h"

// SPI1
#define SPI1_BASE 0x40013000UL
#define SPI1_CR1 (*(volatile uint32_t *)(SPI1_BASE + 0x00))
#define SPI1_CR2 (*(volatile uint32_t *)(SPI1_BASE + 0x04))
#define SPI1_CFG1 (*(volatile uint32_t *)(SPI1_BASE + 0x08))
#define SPI1_CFG2 (*(volatile uint32_t *)(SPI1_BASE + 0x0C))
#define SPI1_SR (*(volatile uint32_t *)(SPI1_BASE + 0x14))
#define SPI1_IFCR (*(volatile uint32_t *)(SPI1_BASE + 0x18))
#define SPI1_TXDR (*(volatile uint32_t *)(SPI1_BASE + 0x20))
#define SPI1_RXDR (*(volatile uint32_t *)(SPI1_BASE + 0x30))

// Function Prototypes 
void spi1_init(void);
void spi1_transmit(uint8_t data);
uint8_t spi1_transfer(uint8_t tx_data);

#endif // SPI_H