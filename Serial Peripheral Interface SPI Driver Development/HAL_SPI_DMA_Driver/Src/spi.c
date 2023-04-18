/*
 * spi.c
 *
 *  Created on: 18 Apr 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

/* *****************************************************************************************************************************************************************************************************************************
 * Story line: from the datasheet section Figure 4. STM32F427xx and STM32F429xx block diagram we observe the SPI1 is connected to APB2 Bus
 * Again, from the datasheet section  Table 12. STM32F427xx and STM32F429xx alternate function mapping we observer PA5->SPI1_SCK; PA6 -> SPI1_MISO; PA7 -> SPI1_MOSI and for each of these pins the alterate function mode is AF5
 *
 * In the reference manual RM0090 section Table 43. DMA2 request mapping we observe both DMA are associated with the DMA2 module as this
 * 		SPI1_TX(Stream 3, Channel 3);
 * 		SPI1_RX(Stream 0, Channel 3)
 * ***************************************************************************************************************************************************************************************************************************** */


#include "spi.h"

SPI_HandleTypeDef hspi1;

DMA_HandleTypeDef hdma_spi1_rx;
DMA_HandleTypeDef hdma_spi1_tx;

void enable_clock_access_to_spi(void)
{
	__HAL_RCC_SPI1_CLK_ENABLE();
}

void enable_clock_access_to_pin_a(void)
{
	 __HAL_RCC_GPIOA_CLK_ENABLE();
}


void spi_init(void)
{
	 GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin  = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Alternate = GPIO_AF5_SPI1;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

	HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}


void configure_spi_module(void)
{
	 hspi1.Instance =  SPI1;
	 hspi1.Init.Mode = SPI_MODE_MASTER;
	 hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	 hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	 hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	 hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	 hspi1.Init.NSS = SPI_NSS_SOFT;
	 hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	 hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	 hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	 hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;

	 HAL_SPI_Init(&hspi1);
}

void enable_clock_access_to_dma(void)
{
	__HAL_RCC_DMA2_CLK_ENABLE();
}


void set_priority_enable_dma_interrupt_rx(void)
{
	NVIC_SetPriority(DMA2_Stream0_IRQn,0);
	NVIC_EnableIRQ(DMA2_Stream0_IRQn);
}


void set_priority_enable_dma_interrupt_tx(void)
{
	NVIC_SetPriority(DMA2_Stream3_IRQn,0);
	NVIC_EnableIRQ(DMA2_Stream3_IRQn);
}


void configure_dma_rx(void)
{
	 hdma_spi1_rx.Instance = DMA2_Stream0;
	 hdma_spi1_rx.Init.Channel = DMA_CHANNEL_3;
	 hdma_spi1_rx.Init.Direction = DMA_PERIPH_TO_MEMORY; // it is MISO Master in slave out (rx)
	 hdma_spi1_rx.Init.PeriphInc = DMA_PINC_DISABLE;
	 hdma_spi1_rx.Init.MemInc = DMA_MINC_ENABLE; // memory has an array and it must be incremented automatically to get the next value
	 hdma_spi1_rx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	 hdma_spi1_rx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	 hdma_spi1_rx.Init.Mode = DMA_NORMAL;
	 hdma_spi1_rx.Init.Priority = DMA_PRIORITY_LOW;
	 hdma_spi1_rx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

	 HAL_DMA_Init(&hdma_spi1_rx); // initialize DMA rx
}

void link_spi_to_dma_rx(void)
{
	hspi1.hdmarx = &hdma_spi1_rx;
}

void configure_dma_tx(void)
{
	hdma_spi1_tx.Instance = DMA2_Stream3;
	hdma_spi1_tx.Init.Channel = DMA_CHANNEL_3;
	hdma_spi1_tx.Init.Direction = DMA_MEMORY_TO_PERIPH;
	hdma_spi1_tx.Init.PeriphInc = DMA_PINC_DISABLE;
	hdma_spi1_tx.Init.MemInc = DMA_MINC_ENABLE;
	hdma_spi1_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
	hdma_spi1_tx.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
	hdma_spi1_tx.Init.Mode = DMA_NORMAL;
	hdma_spi1_tx.Init.Priority = DMA_PRIORITY_LOW;
	hdma_spi1_tx.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

	HAL_DMA_Init(&hdma_spi1_tx); //initialize DMA Tx
}

void link_spi_to_dma_tx(void)
{
	hspi1.hdmatx=&hdma_spi1_tx;
}
