#include <stddef.h>
#include <stdint.h>
#include "usart.h"
#include "process.h"

static struct task_struct *io_wait = NULL; 


int _write(int file, void *ptr, size_t len)
{
 	// Transmit printf string to USART - blocking call
	HAL_UART_Transmit(&huart3, (uint8_t *) ptr, len, 10000);
	return len;
}

_ssize_t _write_r (struct _reent *ptr, int fd, const void *buf, size_t cnt)
{
	return _write(fd, (char *)buf, cnt);
}

/*Read 1 byte of data from user input*/
_ssize_t _read_r(struct _reent *ptr, int fd, void *buf, size_t cnt)
{
	if (cnt == 0)
		return 0;
	HAL_UART_Receive_IT(&huart3, (uint8_t *)buf, 1);
	current->state &= ~(STATE_RUN);
	current->state |= STATE_IO_SLEEP;
	io_wait = current;
	yield();

}

