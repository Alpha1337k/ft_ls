#include <ft_ls.h>

int handle_arg(t_data *data, char *str)
{
	int x = 0;

	while (str[x])
	{
		if (str[x] == 'a')
			data->listall = 1;
		else if (str[x] == 'l')
			data->islist = 1;
		else if (str[x] == 'r')
			data->sorttype = REVERSED;
		else if (str[x] == 't')
			data->sorttype = TIME;
		else if (str[x] == 'R')
			data->isrecusive = 1;
		x++;
	}
	return (0);
}

int	handle_dir(t_direntry **e, char *str)
{
	t_direntry *en = malloc(sizeof(t_direntry));

	en->path = str;

	if (*e == 0)
		*e = en;
	else
	{
		t_direntry *tmp = *e;
		while (tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = en;
	}
	return (0);
}

int	parse(t_data *data, char **argv, t_direntry **e)
{
	int x;

	x = 0;
	while (argv[x])
	{
		if (*argv[x] == '-')
			handle_arg(data, argv[x]);
		else
			handle_dir(e, argv[x]);
		x++;
	}
	return (0);
}