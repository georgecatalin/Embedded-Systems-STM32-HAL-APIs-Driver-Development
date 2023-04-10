/*
 * timer.c
 *
 *  Created on: Apr 10, 2023
 *  Author: George Calin
 * 	Target Development Board: STM32 Nucleo F429ZI
 */

#include "timer.h"


//Configure timer to timeout every second
// Meaning 1hz

//System default freq  = 16 000 000
//Default PCLK1 freq   = 16 000 000
//Default PCLK2 freq   = 16 000 000
//Timer prescaler : 1600 =>   16 000 000 / 1600 = 10,000 (10kH)
//Timer period (Auto reload value) =  10,000

TIM_HandleTypeDef TimHandle;


void tim_timebase_init(void)
{

  _TIMx_CLK_ENABLE;

  TimHandle.Instance       = TIMx;
  TimHandle.Init.Prescaler = 1600 - 1;  // 16 000 000 / 1600 =  10000
  TimHandle.Init.Period    = 10000 -1;  // 10,000 / 10,000 = 1hz
  TimHandle.Init.ClockDivision = 0;
  TimHandle.Init.CounterMode = TIM_COUNTERMODE_UP;
  TimHandle.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;

  HAL_TIM_Base_Init(&TimHandle);

  HAL_NVIC_SetPriority(TIMx_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(TIMx_IRQn);

  /*Start the TIM Base generation in interrupt mode*/
  HAL_TIM_Base_Start_IT(&TimHandle);
}



void TIMx_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&TimHandle);
}

