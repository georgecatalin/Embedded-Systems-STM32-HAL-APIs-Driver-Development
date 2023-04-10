/*
 * adc.c
 *
 *  Created on: Apr 10, 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#include "adc.h"

ADC_HandleTypeDef hadc1;

uint32_t pa1_adc_read(void)
{
	return HAL_ADC_GetValue(&hadc1);
}


void adc_init_start(void)
{
	adc_pa1_single_conversion_init();
	HAL_ADC_Start(&hadc1);
}


void adc_pa1_single_conversion_init(void)
{
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
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    hadc1.Init.DMAContinuousRequests = DISABLE;
    hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;

    HAL_ADC_Init(&hadc1);

    sConfig.Channel =  ADC_CHANNEL_1; // ADC123_IN1 means either ADC1 CHANNEL 1, OR ADC2 CHANNEL 1, OR ADC3 CHANNEL 1
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_480CYCLES;

    HAL_ADC_ConfigChannel(&hadc1, &sConfig);
}
