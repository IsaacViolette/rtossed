/*Define to prevent recursive inclusion*/
#ifndef PROCESS_H
#define PROCESS_H

/*Includes*/
#include "stm32h7xx_hal.h"
#include "main.h"

static inline void yield(void)
{
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
	__DSB();
	__ISB();
}

struct task_struct {
	//state
	int pid;
	int exc_return;
	int sp_start;


}


#endif /*__PROCESS_H*/
