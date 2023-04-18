/**
 ******************************************************************************************************************************************************************
 * @file           : main.c
 * @author         : George Calin
 * @brief          : Main program body
 ******************************************************************************************************************************************************************
 * Code Story: From the Datasheet section Table 12. STM32F427xx and STM32F429xx alternate function mapping (continued) we observe:
 * 		I2C1_SCL->PB6 (AF4); I2C1_SDA ->PB7 (AF4) ; I2C1_SCL -> PB8 (AF4); I2C1_SDA -> PB9 (AF4). We can choose either combination of I2C1_SCL and I2C1_SDA
 * 		hence I am going with
 * 			 I2C1_SCL->PB6 (AF4); I2C1_SDA ->PB7 (AF4)
 *******************************************************************************************************************************************************************
 */

#include <stdio.h>
#include <stdint.h>
#include "uart.h"
#include "i2c.h"
#include "slave.h"


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

extern I2C_HandleTypeDef hi2c1;

#define FOUR_G_SCALE_FACTOR	0.0078  // From ADXL345 Datasheet Specifications>> SENSITIVITY >> ±4 g, 10-bit resolution >> Typ1

extern uint8_t data_received[6];
int16_t x,y,z;
float xg,yg,zg;


int main(void)
{
	HAL_Init();
	uart_init();

	enable_clock_access_to_port_b();
	configure_port_6_7_to_alternate_function();

	enable_clock_access_to_i2c1();
	configure_i2c1();

	adxl_init();

    /* Loop forever */
	for(;;)
	{
		adxl_read_values(DATA_START_ADDRESS);

		x = ((data_received[1]<<8)|data_received[0]);
		y = ((data_received[3]<<8)|data_received[2]);
		z = ((data_received[5]<<8)|data_received[4]);

		xg = x * FOUR_G_SCALE_FACTOR;
		yg = y * FOUR_G_SCALE_FACTOR;
		zg = z * FOUR_G_SCALE_FACTOR;

		 HAL_Delay(10);
	}
}


void  SysTick_Handler(void)
{
	HAL_IncTick();
}
