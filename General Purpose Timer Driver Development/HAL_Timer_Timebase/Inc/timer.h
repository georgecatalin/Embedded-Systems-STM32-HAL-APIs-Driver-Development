
#ifndef TIM_H_
#define TIM_H_

#define TIMx					TIM3
#define _TIMx_CLK_ENABLE 		__HAL_RCC_TIM3_CLK_ENABLE()
#define TIMx_IRQn				TIM3_IRQn
#define TIMx_IRQHandler         TIM3_IRQHandler

#include "stm32f4xx_hal.h"

void tim_timebase_init(void);

#endif


