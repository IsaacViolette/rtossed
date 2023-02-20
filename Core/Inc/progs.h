/*Includes*/
#include "stm32h7xx_hal.h"

/*Define to prevent recursive inclusion*/
#ifndef __PROGS_H
#define __PROGS_H

/*Indicated that the system is initialized and user spece process may start*/
extern int kready;

void process1(void);

void process2(void);

#endif /*__MAIN_H*/
