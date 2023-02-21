/*Includes*/
#include "process.h"

/*Defines*/
#define PROC_MAX 4

/*Global Variables*/
struct task_struct process_table[PROC_MAX];
struct task_struct task_idle;
struct task_struct *current = &task_idle;
