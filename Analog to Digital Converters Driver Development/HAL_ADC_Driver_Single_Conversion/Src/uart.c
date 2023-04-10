/*
 * uart.c
 *
 *  Created on: Apr 10, 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#include "uart.h"

#include "stm32f4xx_hal.h"


UART_HandleTypeDef huart3;


int __io_putchar(int ch)
{
	HAL_UART_Transmit(&huart3,(uint8_t*)&ch,1,10);
	return ch;
}



void uart_init(void)
{

	 GPIO_InitTypeDef GPIO_InitStruct = {0};

    //Enable UART pins clock access
	__HAL_RCC_GPIOD_CLK_ENABLE();

	//Enable UART module clock access
    __HAL_RCC_USART3_CLK_ENABLE();


	//Configure pins to act as alternate func pins(UART)

     GPIO_InitStruct.Pin  = GPIO_PIN_8 | GPIO_PIN_9;
     GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
     GPIO_InitStruct.Alternate = GPIO_AF7_USART3;
     GPIO_InitStruct.Pull =  GPIO_NOPULL;
     GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;

     HAL_GPIO_Init(GPIOD,&GPIO_InitStruct);

     //Configure UART module
     huart3.Instance = USART3;
     huart3.Init.BaudRate = 115200;
     huart3.Init.WordLength = UART_WORDLENGTH_8B;
     huart3.Init.StopBits = UART_STOPBITS_1;
     huart3.Init.Parity = UART_PARITY_NONE;
     huart3.Init.Mode = UART_MODE_TX;
     huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
     huart3.Init.OverSampling = UART_OVERSAMPLING_16;

     HAL_UART_Init(&huart3);


}

