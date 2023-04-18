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
void spi_init(void);
void configure_spi_module(void);
void set_priority_enable_interrupt(void);


#endif /* SPI_H_ */
