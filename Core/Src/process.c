/*Includes*/
#include "process.h"

/*Defines*/
#define PROC_MAX 4

//extern const uint32_t _eustack[];

/*Global Variables*/
struct task_struct process_table[PROC_MAX];
struct task_struct task_idle;
struct task_struct *current = &task_idle;

void process_stack_init(struct task_struct *init)
{
	*((uint32_t*)init->r.SP-1) = 0;

}
