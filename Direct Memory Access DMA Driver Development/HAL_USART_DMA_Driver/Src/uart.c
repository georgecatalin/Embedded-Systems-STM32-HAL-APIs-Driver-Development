/*
 * uart.c
 *
 *  Created on: 7 Apr 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

/* *********************************************************************************************************************************************************************************
Specific(Alternate) Purpose Input/Output Pins:
from "STM32F427xx and STM32F429xx alternate function mapping" in the STM32F429ZI Datasheet: PA9 ->USART1_TX ; PA10 -> USART1_RX

DMA Stream and Channel Selection:
from RM0090 Table 43. DMA2 request mapping we observe USART1_RX (Stream 5; Channel 4) and USART1_TX (Stream 7, Channel 4)
********************************************************************************************************************************************************************************** */

#include "uart.h"

UART_HandleTypeDef h_uart_1;
DMA_HandleTypeDef hdma_usart1_rx;
DMA_HandleTypeDef hdma_usart1_tx;

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


void enable_clock_access_to_dma2(void)
{
	__HAL_RCC_DMA2_CLK_ENABLE();

}

void configure_usart1_rx_dma(void)
{
	 hdma_usart1_rx.Instance = DMA2_Stream5;
	 hdma_usart1_rx.Init.Channel = DMA_CHANNEL_4;
	 hdma_usart1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY;
	 hdma_usart1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	 hdma_usart1_rx.Init.MemInc = DMA_MINC_ENABLE; //in this case the direction of the transfer is from peripheral to memory (array) hence the array address has to be autoincremented to receive new data
	 hdma_usart1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	 hdma_usart1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	 hdma_usart1_rx.Init.Mode = DMA_NORMAL;
	 hdma_usart1_rx.Init.Priority = DMA_PRIORITY_LOW;
	 hdma_usart1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
}


void configure_usart1_tx_dma(void)
{
	 hdma_usart1_tx.Instance = DMA2_Stream7;
	 hdma_usart1_tx.Init.Channel = DMA_CHANNEL_4;
	 hdma_usart1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	 hdma_usart1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	 hdma_usart1_tx.Init.MemInc = DMA_MINC_ENABLE;
	 hdma_usart1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	 hdma_usart1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	 hdma_usart1_tx.Init.Mode = DMA_NORMAL;
	 hdma_usart1_tx.Init.Priority = DMA_PRIORITY_LOW;
	 hdma_usart1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;
}


void initialize_usart1_rx_dma(void)
{
	  HAL_DMA_Init(&hdma_usart1_rx);
}


void initialize_usart1_tx_dma(void)
{
	 HAL_DMA_Init(&hdma_usart1_tx);
}


void link_usart1_rx_to_dma(void)
{
	h_uart_1.hdmarx = &hdma_usart1_rx;
}

void link_usart1_tx_to_dma(void)
{
	h_uart_1.hdmatx = &hdma_usart1_tx;
}


void set_priority_enable_dma_interrupts(void)
{
	/* DMA2_Stream2_IRQn interrupt configuration */
	 HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, 0, 0);
	 HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

	/* DMA2_Stream7_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
}
