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

void enable_clock_access_to_dma2(void);

void configure_usart1_rx_dma(void);
void configure_usart1_tx_dma(void);

void initialize_usart1_rx_dma(void);
void initialize_usart1_tx_dma(void);

void link_usart1_rx_to_dma(void);
void link_usart1_tx_to_dma(void);

void set_priority_enable_dma_interrupts(void);

#endif /* UART_H_ */
