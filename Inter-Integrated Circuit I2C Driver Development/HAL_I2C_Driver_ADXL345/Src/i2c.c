/*
 * i2c.c
 *
 *  Created on: 18 Apr 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 *
 *
 * 	I2C1_SCL->PB6 (AF4); I2C1_SDA ->PB7 (AF4)
 */

#include "i2c.h"

I2C_HandleTypeDef hi2c1;

void enable_clock_access_to_port_b(void)
{
	__HAL_RCC_GPIOB_CLK_ENABLE();
}


void configure_port_6_7_to_alternate_function(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;

	 GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_7;
	 GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;  // in all other cases before we had here  GPIO_MODE_AF_PP
	 GPIO_InitStruct.Pull = GPIO_PULLUP; // in all other cases before we had here GPIO_NOPULL
	 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
	 GPIO_InitStruct.Alternate = GPIO_AF4_I2C1;

	 HAL_GPIO_Init(GPIOB, &GPIO_InitStruct); // Initialize this GPIO in alternate function
}


void enable_clock_access_to_i2c1(void)
{
	__HAL_RCC_I2C1_CLK_ENABLE();
}


void configure_i2c1(void)
{
	 hi2c1.Instance = I2C1;
	 hi2c1.Init.ClockSpeed = 400000;
	 hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
	 hi2c1.Init.OwnAddress1 = 0;
	 hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
	 hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
	 hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
	 hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

	 HAL_I2C_Init(&hi2c1); // Initialize I2C1
}

