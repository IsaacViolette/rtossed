/*Define to prevent recursive inclusion*/
#ifndef PROCESS_H
#define PROCESS_H

/*Includes*/
#include "stm32h7xx_hal.h"
#include "main.h"
#include <stdint.h>
#include <unistd.h>

/*Defines*/
#define STATE_UNUSED 0
#define STATE_TIME_SLEEP 1
#define STATE_IO_SLEEP 2
#define STATE_RUN 4
#define STATE_STOP 8
#define STATE_ZOMBIE 16

static inline void yield(void)
{
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
	__DSB();
	__ISB();
}

struct __attribute__ ((__packed__)) task_struct {
	uint32_t state;
	pid_t pid; //unique integer
	uint32_t exc_return; //Special program counter value that indicates how an exception handler returns
	uint32_t sp_start; //starting stack pointer address
	uint32_t (*cmd)(void); //pointer to a function
	struct r; //Structure that contains saved registers

};


#endif /*__PROCESS_H*/
