/*Define to prevent recursive inclusion*/
#ifndef PROCESS_H
#define PROCESS_H

/*Includes*/
#include "stm32h7xx_hal.h"
#include "main.h"
#include <stdint.h> 
#include <unistd.h> //for pid type

/*Global Variables*/
extern const uint32_t _eustack[];

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

/*Structure of core STM32M7 registers to save */
struct __attribute__ ((__packed__)) registers {
	uint32_t r0;
	uint32_t r1;
	uint32_t r2;
	uint32_t r3;
	uint32_t r4;
	uint32_t r5;
	uint32_t r6;
	uint32_t r7;
	uint32_t r8;
	uint32_t r9;
	uint32_t r11;
	uint32_t r12;
	uint32_t SP;
	uint32_t LR;
	uint32_t PC;
	uint32_t PSR;
	uint32_t PRIMASK;
	uint32_t FAULTMASK;
	uint32_t BASEPRI;
	uint32_t CONTROL;
	uint32_t xPSR;
};

struct __attribute__ ((__packed__)) task_struct {
	uint32_t state;
	pid_t pid; //unique integer
	uint32_t exc_return; //Special program counter value that indicates how an exception handler returns
	uint32_t sp_start; //starting stack pointer address
	uint32_t (*cmd)(void); //pointer to a function
	struct registers r; //Structure that contains saved registers

};



#endif /*__PROCESS_H*/
