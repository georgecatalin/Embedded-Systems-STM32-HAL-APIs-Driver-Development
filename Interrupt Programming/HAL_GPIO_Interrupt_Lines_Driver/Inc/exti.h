/*
 * exti.h
 *
 *  Created on: 11 Apr 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#include "stm32f4xx_hal.h"

#define BTN_PORT	GPIOC
#define BTN_PIN		GPIO_PIN_13

#define BLUE_LED_PORT	GPIOB
#define BLUE_LED_PIN	GPIO_PIN_7
#define RED_LED_PORT	GPIOB
#define RED_LED_PIN	GPIO_PIN_14

void gpio_pc13_interrupt_init(void); // deal with the PC13 cause the user button is connected to PC13 on the development board
void gpio_pb7_interrupt_init(void); //  deal with the PB7 cause the user blue led is connected to PB7 on the development board
void gpio_pb14_interrupt_init(void); //  deal with the PB14 cause the user red led is connected to PB14 on the development board

void exti_configure(void);

