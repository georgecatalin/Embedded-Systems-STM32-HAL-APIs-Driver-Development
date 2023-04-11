/*
 * uart.h
 *
 *  Created on: 7 Apr 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#ifndef UART_H_
#define UART_H_

#include "stm32f4xx_hal.h"

void uart1_init(void);
void configure_set_priority_irq(void);

#endif /* UART_H_ */
