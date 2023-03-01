#include "process.h"



void microsleep(uint32_t sleep_amount)
{
	current->w_time = wTick + (sleep_amount/1000);
	current->state |= STATE_TIME_SLEEP;

	yield();


}
