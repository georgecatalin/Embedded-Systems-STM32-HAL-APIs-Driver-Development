/*
 * adc.c
 *
 *  Created on: Apr 10, 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#include "adc.h"

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;

void adc_pa1_dma_init(void)
{
	/* ********************************************************************************************************************************************************************************************
	from the RM0090 Reference Manual we observe that in we can map ADC1 to Stream0 and Channel0 in the DMA2 module of the microcontroller  if we want to use DMA  (Table 43. DMA2 request mapping)
    ******************************************************************************************************************************************************************************************** */


	//Configure pa1 as analog pin

	 GPIO_InitTypeDef GPIO_InitStruct = {0};
	 ADC_ChannelConfTypeDef sConfig = {0};


    __HAL_RCC_GPIOA_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_1;
    GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


	//Configure adc module for continuous conversion

    __HAL_RCC_ADC1_CLK_ENABLE();

    hadc1.Instance = ADC1;
    hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV8;
    hadc1.Init.Resolution = ADC_RESOLUTION_12B;
    hadc1.Init.ContinuousConvMode = ENABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = ENABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

    HAL_ADC_Init(&hadc1);

    sConfig.Channel =  ADC_CHANNEL_0; // ADC123_IN1 means either ADC1 CHANNEL 1, OR ADC2 CHANNEL 1, OR ADC3 CHANNEL 1
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;

    HAL_ADC_ConfigChannel(&hadc1, &sConfig);

    // Enable clock access to DMA2
    __HAL_RCC_DMA2_CLK_ENABLE();

}

void set_priority_enable_interrupt_for_dma(void)
{
	HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);
}

void configure_dma(void)
{
	 hdma_adc1.Instance  = DMA2_Stream0;
	 hdma_adc1.Init.Channel = DMA_CHANNEL_0;
	 hdma_adc1.Init.Direction = DMA_PERIPH_TO_MEMORY;
	 hdma_adc1.Init.PeriphInc = DMA_PINC_DISABLE;
	 hdma_adc1.Init.MemInc = DMA_MINC_ENABLE;
	 hdma_adc1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
	 hdma_adc1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
	 hdma_adc1.Init.Mode = DMA_CIRCULAR;
	 hdma_adc1.Init.Priority = DMA_PRIORITY_LOW;
	 hdma_adc1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

	 HAL_DMA_Init(&hdma_adc1);
}

void link_adc_TO_DMA(void)
{
	hadc1.DMA_Handle = &hdma_adc1;
}
