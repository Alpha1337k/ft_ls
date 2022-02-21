#include <ft_ls.h>

void	print_row(t_filentry *f, int *w)
{
	printf("%c%s %*ld %*s %*s %*ld %s %s\n",	\
	f->filetype, f->perms,
	w[3], f->links,							\
	w[0], f->owner,							\
	w[1], f->group,							\
	w[2], f->size,							\
	f->modtime, f->name);
}

void	set_wideboys(int *wb, t_filentry *f)
{
	while (f)
	{
		if ((int)strlen(f->owner) > wb[0])
			wb[0] = strlen(f->owner);
		if ((int)strlen(f->group) > wb[1])
			wb[1] = strlen(f->group);
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
		printf("%s:\n", path);
	if (data.islist)
		printf("total %ld\n", data.blocksize);
	while (f)
	{
		if (data.islist)
			print_row(f, widest);
		else
			printf("%s\n", f->name);
		f = f->next;
	}
	// if (data.islist == 0)
	// 	printf("\n");	
}