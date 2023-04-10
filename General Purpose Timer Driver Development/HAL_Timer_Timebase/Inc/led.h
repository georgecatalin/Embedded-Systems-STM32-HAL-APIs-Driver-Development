/*
 * led.h
 *
 *  Created on: Apr 10, 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#ifndef LED_H_
#define LED_H_

#include "stm32f4xx_hal.h"

#define LED_PORT	GPIOB
#define LED_PIN_BLUE	GPIO_PIN_7
#define LED_PIN_RED	 GPIO_PIN_14


void pb7_led_init(void);
void pb14_led_init(void);



#endif /* LED_H_ */
