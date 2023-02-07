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

_ssize_t _read_r(struct _reent *ptr, int fd, void *buf, size_t cnt)
{

}
