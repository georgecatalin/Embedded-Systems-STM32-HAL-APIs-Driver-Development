/*
 * dma.h
 *
 *  Created on: 13 Apr 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#ifndef DMA_H_
#define DMA_H_

#include "stm32f4xx_hal.h"

void enable_clock_access_to_dma(void);
void dma_config(void);
void initialize_dma(void);
void set_priority_enable_dma_interrupt(void);

#endif /* DMA_H_ */
