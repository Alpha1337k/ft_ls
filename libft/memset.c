
void *ft_memset(void *d, char c, int n)
{
	char *data = (char *)d;
	int x = 0;
	while (x < n)
	{
		data[x] = c;
		x++;
	}
	return data;
}