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
extern struct task_struct *current;
extern struct task_struct task_idle;

/*Defines*/
#define STATE_UNUSED 0
#define STATE_TIME_SLEEP 1
#define STATE_IO_SLEEP 2
#define STATE_RUN 4
#define STATE_STOP 8
#define STATE_ZOMBIE 16

/*Prototypes*/
void proc_table_init(void);
struct task_struct *scheduler(void);


static inline void yield(void)
{
	/*Set PendSV bit to 1 in the ICSR register within SCB*/
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk;
	/*Execute a Data synchronization barrier and a instruction synchronization barrier*/
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
	uint32_t r10;
	uint32_t r11;
	uint32_t r12;
	uint32_t SP;
	uint32_t LR;
	uint32_t PC;
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
	int (*cmd)(void); //pointer to a function
	struct registers r; //Structure that contains saved registers

};

/*Context register save*/
static inline void reg_push(void)
{
	/*push r4-r11 onto the stack*/
	__asm__ __volatile__ (
		"PUSH {r4-r11}"
	);
}

/*Context Restore Registers*/
static inline void restore_reg(struct task_struct *next)
{
	//Load r4-r11 from the passed structure
	__asm__ __volatile__(
		"LDMIA %0, {r4-r11}"
		:
		: "r" (&(next->r.r4))
	);
}

/*Contesxt Switch Return*/
static inline void context_return(struct task_struct *next)
{	
	//loads the PC from exc_return within the passed struct
	__asm__ __volatile__(
		"LDR pc, %0"		
		: 
		: "m" (next->exc_return)
	);
}


#endif /*__PROCESS_H*/
