/*
 * exti.c
 *
 *  Created on: 11 Apr 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#include "exti.h"

void gpio_pc13_interrupt_init(void)
{

	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOC_CLK_ENABLE();

	//Configure PC13
	GPIO_InitStruct.Pin  = USER_BTN_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(USER_BTN_PORT,&GPIO_InitStruct);
}

void gpio_pa0_interrupt_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOA_CLK_ENABLE();

	//Configure PA0
	GPIO_InitStruct.Pin  = EXTERNAL_BTN_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(EXTERNAL_BTN_PORT,&GPIO_InitStruct);
}

void gpio_pb7_interrupt_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	__HAL_RCC_GPIOB_CLK_ENABLE(); //this function will be called first, no need to set clock access to the same GPIOB again in the function for the PB14 USER LED

	 GPIO_InitStruct.Pin = BLUE_LED_PIN;
	 GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	 GPIO_InitStruct.Pull = GPIO_NOPULL;
	 GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	 HAL_GPIO_Init(BLUE_LED_PORT,&GPIO_InitStruct);
}


void gpio_pb14_interrupt_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct = {0};

	GPIO_InitStruct.Pin = RED_LED_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(RED_LED_PORT,&GPIO_InitStruct);
}

void exti_configure(void)
{
	//Configure the External Interrupt Line for input on PA0
	HAL_NVIC_SetPriority(EXTI0_IRQn, 1, 0); // The 2nd argument of the function is the priority. The lower the number, the higher priority
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);

	//Configure the External Interrupt Line for input on PC13
    HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0); // EXTI15_10_IRQn because all interrupts from 10..15 go through a single Interrupt
    HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
}
