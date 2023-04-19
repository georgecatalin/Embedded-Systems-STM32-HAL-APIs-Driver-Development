/*
 * rtc.h
 *
 *  Created on: 19 Apr 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#ifndef RTC_H_
#define RTC_H_

#include "stm32f4xx_hal.h"
#include <stdio.h>

#define WRITE_FLAG_BACKUP_REGISTRY	(0x1978)

void reset_handle_state(void);
void turn_off_LSE_turn_on_LSI(void);
void set_clock_source_to_LSI(void);
void enable_RTC_clock(void);
void configure_calendar(void);

void set_calendar(void);
void write_to_backup_register(void);
void show_calendar(uint8_t *showtime, uint8_t *showdate);

#endif /* RTC_H_ */
