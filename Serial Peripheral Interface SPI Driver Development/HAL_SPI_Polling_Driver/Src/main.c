/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */

#include <stdio.h>
#include <stdint.h>
#include "spi.h"

uint8_t tx_buffer[10]={10,20,30,40,50,60,70,80,90,100};
uint8_t rx_buffer[10];

extern SPI_HandleTypeDef hspi1;

/* Test this in Debug as, by connecting PA6 -> SPI1_MISO  to PA7 -> SPI1_MOSI  and displaying the two array values in Live Expressions section. One will notice the values are transferred into rx_buffer */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	HAL_Init();
	enable_clock_access_to_pin_a();
	enable_clock_access_to_spi();
	spi_init();
	configure_spi_module();

	HAL_SPI_TransmitReceive(&hspi1,tx_buffer,rx_buffer,10,100);

    /* Loop forever */
	for(;;)
	{

	}
}


void  SysTick_Handler(void)
{
	HAL_IncTick();
}