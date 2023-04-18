/*
 * slave.c
 *
 *  Created on: 18 Apr 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#include "slave.h"

extern I2C_HandleTypeDef hi2c1;

uint8_t data_received[6]; // x0,x1,y0,y1,z0,z1 that is why 6
uint8_t this_device_id;

void adxl_write (uint8_t reg, uint8_t value)
{
	uint8_t data[2];
	data[0] = reg;
	data[1] = value;

	HAL_I2C_Master_Transmit(&hi2c1, DEVICE_ADDRESS_ADXL, data, 2, 100);
}

void adxl_read_values (uint8_t reg)
{
	HAL_I2C_Mem_Read(&hi2c1, DEVICE_ADDRESS_ADXL, reg, 1,(uint8_t *) data_received, 6, 100);
}

void adxl_read_address (uint8_t reg)
{
	HAL_I2C_Mem_Read(&hi2c1, DEVICE_ADDRESS_ADXL, reg, 1, &this_device_id, 1, 100);
}

void adxl_init(void)
{
	//1. Read device ID
	adxl_read_address(DEVID_R_ADXL);

	//2. Set data format to +/- 4g
	adxl_write(DATA_FORMAT_ADXL, FOUR_G);

	//3.Reset all bits in POWER_CTL
	adxl_write(POWER_CTL_ADXL, RESET_POWER_CTL);

	//4. Set the measure of the POWER_CTL Registry
	adxl_write(POWER_CTL_ADXL, SET_MEASURE_POWER_CTL);
}
