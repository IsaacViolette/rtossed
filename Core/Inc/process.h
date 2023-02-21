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


#endif /*__PROCESS_H*/
