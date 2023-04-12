/*
 * adc.h
 *
 *  Created on: Apr 10, 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#ifndef ADC_H_
#define ADC_H_

#include "stm32f4xx_hal.h"
#include <stdint.h>

void adc_pa1pa2_dma_init(void);
void set_priority_enable_interrupt_for_dma(void);
void configure_dma(void);
void link_adc_TO_DMA(void);

#endif /* ADC_H_ */
