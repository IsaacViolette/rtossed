/*Includes*/
#include "process.h"
#include <string.h>
#include "sh.h"

/*Defines*/
#define PROC_MAX 4

/*Prototypes*/
void proc_start(void);

/*Global Variables*/
/*Init the entire array of structures to zero*/
struct task_struct process_table[PROC_MAX];
struct task_struct task_idle;
struct task_struct *current = &task_idle;

/*Stack Initialization*/
void process_stack_init(struct task_struct *init)
{
	*((uint32_t*)init->r.SP-1) = 0; //FPSCR
	*((uint32_t*)init->r.SP-2) = 0; //S15
	*((uint32_t*)init->r.SP-3) = 0; //S14
	*((uint32_t*)init->r.SP-4) = 0; //S13
	*((uint32_t*)init->r.SP-5) = 0; //S12
	*((uint32_t*)init->r.SP-6) = 0; //S11
	*((uint32_t*)init->r.SP-7) = 0; //S10
	*((uint32_t*)init->r.SP-8) = 0; //S9
	*((uint32_t*)init->r.SP-9) = 0; //S8
	*((uint32_t*)init->r.SP-10) = 0; //S7
	*((uint32_t*)init->r.SP-11) = 0; //S6
	*((uint32_t*)init->r.SP-12) = 0; //S5
	*((uint32_t*)init->r.SP-13) = 0; //S4
	*((uint32_t*)init->r.SP-14) = 0; //S3
	*((uint32_t*)init->r.SP-15) = 0; //S2
	*((uint32_t*)init->r.SP-16) = 0; //S1
	*((uint32_t*)init->r.SP-17) = 0; //S0
	*((uint32_t*)init->r.SP-18) = init->r.xPSR;
	*((uint32_t*)init->r.SP-19) = init->r.PC;
	*((uint32_t*)init->r.SP-20) = init->r.LR;
	*((uint32_t*)init->r.SP-21) = init->r.r12;
	*((uint32_t*)init->r.SP-22) = init->r.r3;
	*((uint32_t*)init->r.SP-23) = init->r.r2;
	*((uint32_t*)init->r.SP-24) = init->r.r1;
	*((uint32_t*)init->r.SP-25) = init->r.r0;

	/*Save the updated SP variable back to the SP that was passed*/
	init->r.SP = 25*4; //move stack pointer down 100 bytes, 25 addresses at 4 bytes a piece
	
}


/*Process Table and Idle Task Init*/
void proc_table_init(void)
{	
	memset(&process_table, 0, sizeof process_table);

	process_table[0].r.SP = (uint32_t) _eustack;
	process_table[0].sp_start = (uint32_t) _eustack;
	process_table[0].r.LR = 0;	
	process_table[0].r.PC = (uint32_t) proc_start;
	process_table[0].r.PSR = 0x01000000;
	process_table[0].state = STATE_RUN;
	process_table[0].cmd = sh; 
	process_table[0].exc_return = EXC_RETURN_THREAD_PSP;	
	process_table[0].pid = 0;
	process_stack_init(&process_table[0]);
	
	//Initialize the idle task structure
	task_idle.state = STATE_STOP;
	task_idle.r.PSR = 0x01000000;
	task_idle.exc_return = EXC_RETURN_THREAD_MSP_FPU;
	task_idle.pid = -2;

}

/*calls function pointed to by cmd within struct task_struct structure*/
void proc_start(void)
{
	(current->cmd)(); 

	current->state = STATE_STOP;
	while(1);
}
