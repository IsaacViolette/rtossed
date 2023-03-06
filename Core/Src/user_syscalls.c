#include "process.h"



void microsleep(uint32_t sleep_amount)
{
	current->w_time = uwTick + (sleep_amount/1000); //Set the time to wake up
	current->state = STATE_TIME_SLEEP; //Make sure the process is in the sleep state

	yield();


}
