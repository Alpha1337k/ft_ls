

void	ft_tolowercase(char *s)
{
	int x = 0;
	while (s && s[x])
	{
		if (s[x] >= 'A' && s[x] <= 'Z')
			s[x] += 32;
		x++;
	}
	
}