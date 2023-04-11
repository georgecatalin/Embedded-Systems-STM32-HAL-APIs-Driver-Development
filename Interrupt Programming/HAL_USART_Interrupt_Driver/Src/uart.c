/*
 * uart.c
 *
 *  Created on: 7 Apr 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

//from "STM32F427xx and STM32F429xx alternate function mapping" in the STM32F429ZI Datasheet: PA9 ->USART1_TX ; PA10 -> USART1_RX

#include "uart.h"
UART_HandleTypeDef h_uart_1;

void uart1_init(void)
{


	GPIO_InitTypeDef GPIO_InitStruct = {0};

	//Enable UART pins clock access
	__HAL_RCC_GPIOA_CLK_ENABLE();

	//Enable UART module clock access
	__HAL_RCC_USART1_CLK_ENABLE();

	//Configure pins to act as alternate function pins (UART)
	GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_10;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	//We can also use HAL_UART_MspInit (UART_HandleTypeDef * huart) to config the pins automatically
	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

	//Configure UART TX module
	h_uart_1.Instance = USART1;
	h_uart_1.Init.BaudRate = 115200;
	h_uart_1.Init.WordLength = UART_WORDLENGTH_8B;
	h_uart_1.Init.StopBits = UART_STOPBITS_1;
	h_uart_1.Init.Parity = UART_PARITY_NONE;
	h_uart_1.Init.Mode = UART_MODE_TX_RX;
	h_uart_1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	h_uart_1.Init.OverSampling = UART_OVERSAMPLING_16;

	HAL_UART_Init(&h_uart_1);
}

void configure_set_priority_irq(void)
{
	NVIC_SetPriority(USART1_IRQn,0);
	NVIC_EnableIRQ(USART1_IRQn);
}
