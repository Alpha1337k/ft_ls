#include <ft_ls.h>


int	alphabetical_compare(t_filentry f1, t_filentry f2)
{
	return ft_strcmp(f1.name, f2.name);
}

int	reverse_compare(t_filentry f1, t_filentry f2)
{
	return ft_strcmp(f2.name, f1.name);
}

int	time_compare(t_filentry f1, t_filentry f2)
{
	if (f1.realtime.tv_sec == f2.realtime.tv_sec)
	{
		if (f1.realtime.tv_nsec == f2.realtime.tv_nsec)
			return ft_strcmp(f1.name, f2.name);
		else
			return f1.realtime.tv_nsec < f2.realtime.tv_nsec; 
	}
	return f1.realtime.tv_sec < f2.realtime.tv_sec;
}

int	reverse_time_compare(t_filentry f1, t_filentry f2)
{
	if (f1.realtime.tv_sec == f2.realtime.tv_sec)
	{
		if (f1.realtime.tv_nsec == f2.realtime.tv_nsec)
			return ft_strcmp(f2.name, f1.name);
		else
			return f1.realtime.tv_nsec > f2.realtime.tv_nsec; 
	}
	return f1.realtime.tv_sec > f2.realtime.tv_sec;
}

void	swap(t_filentry *f1, t_filentry *f2, t_filentry **base)
{
	t_filentry *tmp;

	f1->next = f2->next;
	f2->prev = f1->prev;
	f1->prev = f2;
	f2->next = f1;

	if (f1->next)
	{
		tmp = f1->next;
		tmp->prev = f1;
	}
	if (f2->prev)
	{
		tmp = f2->prev;
		tmp->next = f2;
	}
	else
	{
		*base = f2;
	}
}

t_filentry	*sort_list(t_filentry *files, int (f(t_filentry , t_filentry)))
{
	t_filentry *base = files;
	t_filentry *tmp;
	int changes = 1;

	while (changes != 0)
	{
		tmp = base;
		changes = 0;
		while (tmp && tmp->next)
		{
			if (f(*tmp, *(t_filentry *)(tmp->next)) > 0)
			{
				swap(tmp, (t_filentry *)(tmp->next), &base);
				changes++;
			}
			else
				tmp = tmp->next;
		}
	}
	return base;
}