/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 STM32 Nucleo-144 boards (MB1137)

 The information about the Pins associated to USART1 is derived from "STM32F427xx and STM32F429xx alternate function mapping" in the STM32F429ZI Datasheet: PA9 ->USART1_TX ; PA10 -> USART1_RX

 For verification connect a jumper wire with an end to PA9 and the other end to PA10, and you should observe in debug mode that the global variable counters increase, and the buffers(arrays) get filled at the rx end.

 ******************************************************************************
 */
#include "stm32f4xx_hal.h"
#include <stdint.h>
#include "uart.h"

extern UART_HandleTypeDef h_uart_1;

void uart1_init(void);


uint8_t tx_buffer[]={10,20,30,40,50,60,70,80,90,100}; //this is the data to be sent
uint8_t rx_buffer[10]={}; //this is the data to be received


uint32_t rx_counter, tx_counter;

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	HAL_Init();
	uart1_init();
	configure_set_priority_irq();

	HAL_UART_Transmit_IT(&h_uart_1, tx_buffer,10);
	HAL_UART_Receive_IT(&h_uart_1,rx_buffer,10);

    /* Loop forever */
	for(;;)
	{
	}
}

void SysTick_Handler(void)
{
	HAL_IncTick();
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *h_uart)
{
	tx_counter++;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *h_uart)
{
	rx_counter++;
}

void USART1_IRQHandler(void)
{
	HAL_UART_IRQHandler(&h_uart_1);
}