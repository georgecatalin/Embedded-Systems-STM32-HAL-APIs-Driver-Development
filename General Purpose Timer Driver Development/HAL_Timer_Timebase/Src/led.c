/*
 * led.c
 *
 *  Created on: Apr 10, 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#include "led.h"


void pb7_led_init(void)
{
	GPIO_InitTypeDef 	GPIO_InitStruct ={0};
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStruct.Pin   = LED_PIN_BLUE;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  =  GPIO_NOPULL;
	GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init (LED_PORT, &GPIO_InitStruct);
}

void pb14_led_init(void)
{
	GPIO_InitTypeDef 	GPIO_InitStruct ={0};
	__HAL_RCC_GPIOB_CLK_ENABLE();

	GPIO_InitStruct.Pin   = LED_PIN_RED;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull  =  GPIO_NOPULL;
	GPIO_InitStruct.Speed =  GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init (LED_PORT, &GPIO_InitStruct);
}
