/*
 * dma.c
 *
 *  Created on: 13 Apr 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#include "dma.h"

#define DMA_STREAM  DMA2_Stream0
#define DMA_CHANNEL DMA_CHANNEL_0
#define DMA_STREAM_IRQ  DMA2_Stream0_IRQn

DMA_HandleTypeDef     DmaHandle;


void enable_clock_access_to_dma(void)
{
	__HAL_RCC_DMA2_CLK_ENABLE();
}

void dma_config(void)
{
	DmaHandle.Instance = DMA_STREAM;
	DmaHandle.Init.Channel = DMA_CHANNEL;
	DmaHandle.Init.Direction = DMA_MEMORY_TO_MEMORY;
	DmaHandle.Init.PeriphDataAlignment = DMA_PDATAALIGN_WORD;
	DmaHandle.Init.MemDataAlignment = DMA_MDATAALIGN_WORD;
	DmaHandle.Init.PeriphInc = DMA_PINC_ENABLE;
	DmaHandle.Init.MemInc = DMA_MINC_ENABLE;
	DmaHandle.Init.Mode = DMA_NORMAL;
	DmaHandle.Init.Priority = DMA_PRIORITY_HIGH;
	DmaHandle.Init.FIFOMode = DMA_FIFOMODE_ENABLE;
	DmaHandle.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_1QUARTERFULL;
	DmaHandle.Init.MemBurst = DMA_MBURST_SINGLE;
	DmaHandle.Init.PeriphBurst = DMA_PBURST_SINGLE;
}


void initialize_dma(void)
{
	HAL_DMA_Init(&DmaHandle);
}


void set_priority_enable_dma_interrupt(void)
{
     HAL_NVIC_SetPriority(DMA_STREAM_IRQ, 0, 0);
	 HAL_NVIC_EnableIRQ(DMA_STREAM_IRQ);
}
