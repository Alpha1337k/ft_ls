#include <ft_ls.h>

void	print_padding(int n)
{
	int x = 0;
	while (x < n)
	{
		write(1, " ", 1);
		x++;
	}
}

void	print_row(t_filentry *f, int *w)
{
	write(1, &f->filetype, 1);
	write(1, f->perms, ft_strlen(f->perms));


	print_padding(w[3] + 1 - longlen(f->links));
	ft_putnbr(f->links);
	print_padding(1);

	write(1, f->owner, ft_strlen(f->owner));
	print_padding(w[0] + 1 - ft_strlen(f->owner));

	write(1, f->group, ft_strlen(f->group));

	print_padding(w[2] + 1 - longlen(f->size));
	ft_putnbr(f->size);
	print_padding(1);

	write(1, f->modtime, ft_strlen(f->modtime));
	print_padding(1);

	if (f->filetype == 'l')
	{
		write(1, f->name, ft_strlen(f->name));
		write(1, " -> ", 4);
		ft_puts(f->linkname);
	}
	else
		ft_puts(f->name);
}

void	set_wideboys(int *wb, t_filentry *f)
{
	while (f)
	{
		if ((int)ft_strlen(f->owner) > wb[0])
			wb[0] = ft_strlen(f->owner);
		if ((int)ft_strlen(f->group) > wb[1])
			wb[1] = ft_strlen(f->group);
		if (longlen(f->size) > wb[2])
			wb[2] = longlen(f->size);
		if (longlen(f->links) > wb[3])
			wb[3] = longlen(f->links);
		f = f->next;
	}
}

void	printer(t_data data, t_filentry *f, char *path)
{
	int widest[4] = {0};

	set_wideboys(widest, f);
	if (data.isrecusive)
	{
		write(1, path, ft_strlen(path));
		ft_puts(":");
	}
	if (data.islist)
	{
		write(1, "total ", 6);
		ft_putnbr(data.blocksize / 2);
		ft_puts("");
	}
	while (f)
	{
		if (data.islist)
			print_row(f, widest);
		else 
			ft_puts(f->name);
		f = f->next;
	}
}