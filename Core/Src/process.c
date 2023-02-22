/*Includes*/
#include "process.h"

/*Defines*/
#define PROC_MAX 4

//extern const uint32_t _eustack[];

/*Global Variables*/
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
	*((uint32_t*)init->r.SP-18) = init->r.PC;
	*((uint32_t*)init->r.SP-18) = init->r.LR;
	*((uint32_t*)init->r.SP-18) = init->r.r12;
	*((uint32_t*)init->r.SP-18) = init->r.r3;
	*((uint32_t*)init->r.SP-18) = init->r.r2;
	*((uint32_t*)init->r.SP-18) = init->r.r1;
	*((uint32_t*)init->r.SP-18) = init->r.r0;







}
