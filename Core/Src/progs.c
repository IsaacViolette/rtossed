/*Includes*/
#include "progs.h"

void process1()
{
	while(1) {
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
		HAL_Delay(500);
	}
}

void process2()
{
	while(1) {
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_1);
		HAL_Delay(1000);
	}

}
