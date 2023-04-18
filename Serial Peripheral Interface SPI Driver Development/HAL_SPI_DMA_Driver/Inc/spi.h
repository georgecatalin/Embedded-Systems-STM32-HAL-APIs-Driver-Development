/*
 * spi.h
 *
 *  Created on: 18 Apr 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#ifndef SPI_H_
#define SPI_H_

#include "stm32f4xx_hal.h"

void enable_clock_access_to_spi(void);
void enable_clock_access_to_pin_a(void);
void enable_clock_access_to_dma(void);
void spi_init(void);
void configure_spi_module(void);

void configure_dma_rx(void);
void configure_dma_tx(void);

void link_spi_to_dma_rx(void);
void link_spi_to_dma_tx(void);
void set_priority_enable_dma_interrupt_rx(void);
void set_priority_enable_dma_interrupt_tx(void);


#endif /* SPI_H_ */
