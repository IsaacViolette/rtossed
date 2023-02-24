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
	uint32_t *sp = (uint32_t *) (init->r.SP);
	*(sp-1) = 0; //FPSCR
	*(sp-2) = 0; //S15
	*(sp-3) = 0; //S14
	*(sp-4) = 0; //S13
	*(sp-5) = 0; //S12
	*(sp-6) = 0; //S11
	*(sp-7) = 0; //S10
	*(sp-8) = 0; //S9
	*(sp-9) = 0; //S8
	*(sp-10) = 0; //S7
	*(sp-11) = 0; //S6
	*(sp-12) = 0; //S5
	*(sp-13) = 0; //S4
	*(sp-14) = 0; //S3
	*(sp-15) = 0; //S2
	*(sp-16) = 0; //S1
	*(sp-17) = 0; //S0
	*(sp-18) = init->r.xPSR;
	*(sp-19) = init->r.PC;
	*(sp-20) = init->r.LR;
	*(sp-21) = init->r.r12;
	*(sp-22) = init->r.r3;
	*(sp-23) = init->r.r2;
	*(sp-24) = init->r.r1;
	*(sp-25) = init->r.r0;

	/*Save the updated SP variable back to the SP that was passed*/
	init->r.SP -= 25*4; //move stack pointer down 100 bytes, 25 addresses at 4 bytes a piece
	
}


/*Process Table and Idle Task Init*/
void proc_table_init(void)
{	
	//initialize all process tables to zero	
	memset(&process_table, 0, sizeof process_table);
	
	//Set up process table at index 0
	process_table[0].r.SP = (uint32_t) _eustack;
	process_table[0].sp_start = (uint32_t) _eustack;
	process_table[0].r.LR = 0;	
	process_table[0].r.PC = (uint32_t) proc_start;
	process_table[0].r.xPSR = 0x01000000;
	process_table[0].state = STATE_RUN;
	process_table[0].cmd = sh; 
	process_table[0].exc_return = EXC_RETURN_THREAD_PSP;	
	process_table[0].pid = 0;
	process_stack_init(&process_table[0]);
	
	//Initialize the idle task structure
	task_idle.state = STATE_STOP;
	task_idle.r.xPSR = 0x01000000;
	task_idle.exc_return = EXC_RETURN_THREAD_MSP_FPU;
	task_idle.pid = -2;

}

/*calls function pointed to by cmd within struct task_struct structure*/
void proc_start(void)
{
	//Call the function called by cmd
	(current->cmd)(); 
	
	//to stop a hard fault from happening, change the state to stop
	current->state = STATE_STOP;
	while (1);
}

/*This function decides which process to run next*/
struct task_struct *scheduler(void)
{
	/*If the current task is the idle task, the return a pointer to the first process table entry*/
	if (current == &task_idle)
		return &process_table[0];
	/*Otherwise return a pointer to the idle task*/
	return &task_idle;
}
