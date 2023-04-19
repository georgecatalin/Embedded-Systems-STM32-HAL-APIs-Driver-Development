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

void uart_init(void);
int __io_putchar(int ch);


#endif /* UART_H_ */
