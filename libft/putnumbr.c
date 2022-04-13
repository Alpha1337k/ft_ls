#include <unistd.h>

void	ft_putnbr(long n)
{
	char printval;

	if ((int)n == -2147483648)
	{
		write(1, "-2147483648", 11);
	}
	else if (n < 0)
	{
		write(1, "-", 1);
		n /= -1;
		if (n / 10 != 0)
			ft_putnbr(n / 10);
		printval = (n % 10) + 48;
		write(1, &printval, 1);
	}
	else
	{
		if (n / 10 != 0)
			ft_putnbr(n / 10);
		printval = (n % 10) + 48;
		write(1, &printval, 1);
	}
}