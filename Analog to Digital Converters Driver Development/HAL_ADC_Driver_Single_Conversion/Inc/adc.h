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

uint32_t pa1_adc_read(void);
void adc_init_start(void);
void adc_pa1_single_conversion_init(void);

#endif /* ADC_H_ */
