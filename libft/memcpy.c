
void *ft_memcpy(char *dest, char *src, int n)
{
	int x = 0;
	while (x < n)
	{
		dest[x] = src[x];
		x++;
	}
	return dest;
}