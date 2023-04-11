/**
 ******************************************************************************
 * @file           : main.c
 * @author         : George Calin
 * @brief          : Main program body
 ******************************************************************************
 * @date	: 2023-04-11
 ******************************************************************************
 */

#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "exti.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	HAL_Init();

	uart_init();

    gpio_pc13_interrupt_init();
    gpio_pa0_interrupt_init();

    gpio_pb7_interrupt_init();
    gpio_pb14_interrupt_init();

    exti_configure();

    /* Loop forever */
	for(;;)
	{

	}
}


void  SysTick_Handler(void)
{
	HAL_IncTick();
}

void HAL_GPIO_EXTI_Callback(uint16_t myPin)
{
	if(myPin==USER_BTN_PIN)
	{
		printf("The user button PC13 has been pressed! \n\r");
		HAL_GPIO_TogglePin(BLUE_LED_PORT, BLUE_LED_PIN);
	}

	if(myPin==EXTERNAL_BTN_PIN)
	{
		printf("The external button PA0 has been pressed! \n\r");
		HAL_GPIO_TogglePin(RED_LED_PORT, RED_LED_PIN);
	}




}



void EXTI15_10_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(USER_BTN_PIN);
}

void EXTI0_IRQHandler(void)
{
	HAL_GPIO_EXTI_IRQHandler(EXTERNAL_BTN_PIN);
}
