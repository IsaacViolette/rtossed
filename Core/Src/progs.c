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
		microsleep(1000);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);

		i++;
		
		/*Block if no lock is availible*/
		while(HAL_HSEEM_Take(9,current->pid) != 0);

		printf("Current: %d | The current value of i is: %u\r\n",current->pid,i);

		HAL_HSEM_Release(9, current->pid);
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
