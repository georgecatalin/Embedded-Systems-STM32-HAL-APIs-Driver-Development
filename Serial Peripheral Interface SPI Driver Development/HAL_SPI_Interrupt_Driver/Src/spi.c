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
 * ***************************************************************************************************************************************************************************************************************************** */


#include "spi.h"

SPI_HandleTypeDef hspi1;

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


void set_priority_enable_interrupt(void)
{
	NVIC_SetPriority(SPI1_IRQn,0);
	NVIC_EnableIRQ(SPI1_IRQn);
}
