/*Includes*/
#include "progs.h"

/*Blink the onboard green LED*/
int process1(void)
{
	while (1) {
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);
		HAL_Delay(500);
	}

	return 0;
}

/*Blink the onboard amber LED*/
void process2(void)
{
	while (1) {
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_1);
		HAL_Delay(1000);
	}

}
