/*
 * i2c.h
 *
 *  Created on: 18 Apr 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#ifndef I2C_H_
#define I2C_H_

#include "stm32f4xx_hal.h"

void enable_clock_access_to_port_b(void);
void configure_port_6_7_to_alternate_function(void);

void enable_clock_access_to_i2c1(void);
void configure_i2c1(void);

#endif /* I2C_H_ */
