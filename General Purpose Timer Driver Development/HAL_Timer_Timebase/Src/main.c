#include <stdio.h>
#include "uart.h"
#include "timer.h"
#include "led.h"


int main()
{

  HAL_Init();
  tim_timebase_init();
  uart3_init();
  pb7_led_init();
  pb14_led_init();

  while(1)
  {

  }
}


void HAL_TIM_PeriodElapsedCallback( TIM_HandleTypeDef *htim)
{
	//Do something
	printf("A second just elapsed ! \n\r");
	HAL_GPIO_TogglePin(GPIOB, LED_PIN_BLUE);
	HAL_GPIO_TogglePin(GPIOB, LED_PIN_RED);
}


void  SysTick_Handler(void)
{
	HAL_IncTick();
}




