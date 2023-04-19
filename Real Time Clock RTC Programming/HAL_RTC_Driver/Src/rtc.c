/*
 * rtc.c
 *
 *  Created on: 19 Apr 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#include "rtc.h"


#define RTC_ASYNCH_PRESCALE_DIVIDER  0x7F  // 127
#define RTC_SYNCH_PRESCALE_DIVIDER   0xF9  // 249

RCC_OscInitTypeDef        RCC_OscInitStruct;
RCC_PeriphCLKInitTypeDef  PeriphClkInitStruct;

RTC_HandleTypeDef RtcHandle;

void reset_handle_state(void)
{
   __HAL_RTC_RESET_HANDLE_STATE(&RtcHandle);
}

void turn_off_LSE_turn_on_LSI(void)
{
	RCC_OscInitStruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI | RCC_OSCILLATORTYPE_LSE;
	RCC_OscInitStruct.LSEState = RCC_LSE_OFF;
	RCC_OscInitStruct.LSIState = RCC_LSI_ON;

	HAL_RCC_OscConfig(&RCC_OscInitStruct);
}

void set_clock_source_to_LSI(void)
{
	PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_RTC;
	PeriphClkInitStruct.RTCClockSelection =  RCC_RTCCLKSOURCE_LSI;

	HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct);

}

void enable_RTC_clock(void)
{
	__HAL_RCC_RTC_ENABLE();
}

void configure_calendar(void)
{
	RtcHandle.Instance = RTC;
    RtcHandle.Init.HourFormat = RTC_HOURFORMAT_24;
    RtcHandle.Init.AsynchPrediv = RTC_ASYNCH_PRESCALE_DIVIDER;
    RtcHandle.Init.SynchPrediv = RTC_SYNCH_PRESCALE_DIVIDER;
    RtcHandle.Init.OutPut = RTC_OUTPUT_DISABLE;

    HAL_RTC_Init(&RtcHandle);
}

void set_calendar(void)
{
	 RTC_DateTypeDef sdatestructure;
	 RTC_TimeTypeDef stimestructure;

	 //Set Date: Sunday Oct 21st 1978
	 sdatestructure.Year =0x78;
	 sdatestructure.Month = RTC_MONTH_OCTOBER;
	 sdatestructure.Date =0x21;
	 sdatestructure.WeekDay = RTC_WEEKDAY_FRIDAY;

	HAL_RTC_SetDate(&RtcHandle,&sdatestructure,RTC_FORMAT_BCD) ;

	//Set Time: 05:30:00
	stimestructure.Hours =  0x05;
	stimestructure.Minutes = 0x30;
	stimestructure.Seconds = 0x00;
	stimestructure.TimeFormat = RTC_HOURFORMAT12_AM;
	stimestructure.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
	stimestructure.StoreOperation = RTC_STOREOPERATION_RESET;
	HAL_RTC_SetTime(&RtcHandle,&stimestructure,RTC_FORMAT_BCD);

	write_to_backup_register();
}

void write_to_backup_register(void)
{
	 HAL_RTCEx_BKUPWrite(&RtcHandle,RTC_BKP_DR0,WRITE_FLAG_BACKUP_REGISTRY);
}

void show_calendar(uint8_t *showtime, uint8_t *showdate)
{
	RTC_DateTypeDef sdatestructureget;
	RTC_TimeTypeDef stimestructureget;

	HAL_RTC_GetTime(&RtcHandle, &stimestructureget, RTC_FORMAT_BIN);

	HAL_RTC_GetDate(&RtcHandle, &sdatestructureget, RTC_FORMAT_BIN);

	/* Display time Format: hh:mm:ss */
	sprintf((char*)showtime,"%02d:%02d:%02d",stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds);

	/* Display date Format: mm-dd-yy */
	sprintf((char*)showdate,"%02d-%02d-%02d",sdatestructureget.Month, sdatestructureget.Date, 1900 + sdatestructureget.Year);


	printf(" Time : %02d:%02d:%02d\n\r",stimestructureget.Hours, stimestructureget.Minutes, stimestructureget.Seconds);
	printf(" Date : %02d-%02d-%02d\n\r",sdatestructureget.Month, sdatestructureget.Date, 1900 + sdatestructureget.Year);

}
