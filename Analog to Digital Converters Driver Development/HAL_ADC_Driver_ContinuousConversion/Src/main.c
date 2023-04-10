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
#include "stm32f4xx_hal.h"
#include "adc.h"
#include "uart.h"

uint32_t sensor_value;

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	HAL_Init();
	uart_init();
	adc_init_start();


    /* Loop forever */
	for(;;)
	{
		sensor_value=pa1_adc_read();

	    printf("The sensor value : %d   \n\r",(int)sensor_value);
	}
}


void  SysTick_Handler(void)
{
	HAL_IncTick();
}