/*Includes*/
#include <stdio.h>
#include "progs.h"
#include "user_syscalls.h"
#include "process.h"

HAL_StatusTypeDef i = 0; //project 2 increment

/*Blink the onboard green LED*/
int process1(void)
{
	while (1) {
		microsleep(1000);
		HAL_GPIO_TogglePin(GPIOB, GPIO_PIN_0);

		i++;
		
		/*Block if no lock is availible*/
		while (HAL_HSEM_Take(9,current->pid) != HAL_OK) {
			yield();
		}

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
