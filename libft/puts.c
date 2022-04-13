#include <ft_ls.h>

void ft_puts(char *s)
{
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
}