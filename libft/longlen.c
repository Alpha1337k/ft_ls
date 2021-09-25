

int	longlen(long l)
{
	int len = 0;
	if (l == 0)
		return 0;
	if (l < 0)
		len = 1;
	while (l != 0)
	{
		l /= 10;
		len++;
	}
	return len;
}