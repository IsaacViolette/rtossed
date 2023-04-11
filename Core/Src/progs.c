/*Includes*/
#include <stdio.h>
#include "progs.h"
#include "user_syscalls.h"
#include "process.h"

/*Blink the onboard green LED*/
int process1(void)
{
	static uint8_t i; //project 2 increment
	while (1) {
		microsleep(0000);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);

		i++;

		printf("Current: %d | The current calue of i is: %u\r\n",current->pid,i);
	}

	return 0;
}

/*Blink the onboard amber LED*/
void process2(void)
{
	while (1) {
		HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_1);
		microsleep(1000);
	}

}
