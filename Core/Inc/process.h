/*Includes*/
#include "stm32h7xx_hal.h"
#include "main.h"

/*Define to prevent recursive inclusion*/
#ifndef __PROCESS_H
#define __PROCESS_H

static inline void yield(void)
{
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
	_DSB();
	_ISB();
}


#endif /*__PROCESS_H*/
