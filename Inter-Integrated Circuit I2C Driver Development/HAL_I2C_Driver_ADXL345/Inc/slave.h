/*
 * slave.h
 *
 *  Created on: 18 Apr 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */


//define macros for data to be used from the datasheet of ADXL345
//ADXL345 uses itself registries to store information, hence to need to record some addresses of its registries we can appeal to later

#include <stdint.h>
#include "i2c.h"

#define DEVID_R_ADXL 	(0x00)
#define THRESH_TAP_ADXL (0x1D)
#define POWER_CTL_ADXL	(0x2D)
#define DATA_FORMAT_ADXL (0x31)

#define DEVICE_ADDRESS_ADXL	(0x53<<1)

/* *****************************************************************************************
 from ADLX345 Datasheet Register 0x31—DATA_FORMAT (Read/Write)
 	 D7			 D6 	D5 		     D4		 D3 	    D2 			D1 D0
	SELF_TEST	 SPI	 INT_INVERT	 0 		FULL_RES 	Justify      Range

Range Bits
D1 D0 g Range
0 0 ±2 g
0 1 ±4 g
1 0 ±8 g
1 1 ±16 g

********************************************************************************************** */
#define FOUR_G	(0x01)

/* **********************************************************************************************
 * From ADXL345 Datasheet in  Register 0x2D—POWER_CTL (Read/Write)
 *
 * **********************************************************************************************
 */
#define RESET_POWER_CTL 	(0x0)
#define SET_MEASURE_POWER_CTL (1<<3)   // 0x8

/* **********************************************************************************************************************
 * From ADXL345 Datasheet :  Register 0x32 to Register 0x37—DATAX0, DATAX1, DATAY0, DATAY1, DATAZ0, DATAZ1 (Read Only)
	These six bytes (Register 0x32 to Register 0x37) are eight bits each and hold the output data for each axis.
   *********************************************************************************************************************
 */
#define DATA_START_ADDRESS (0x32)

void adxl_write (uint8_t reg, uint8_t value);
void adxl_read_values (uint8_t reg);
void adxl_read_address (uint8_t reg);
void adxl_init(void);
