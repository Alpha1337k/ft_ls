#include <ft_ls.h>

void	cleanup_dir(t_direntry *ent)
{
	t_direntry *tmp;
	while (ent)
	{
		tmp = ent;
		ent = ent->next;
		free(tmp);
	}	
}

void	cleanup_file(t_filentry *ent)
{
	t_filentry *tmp;
	while (ent)
	{
		tmp = ent;
		ent = ent->next;
		free(tmp->modtime);
		free(tmp->perms);
		free(tmp->name);
		free(tmp->owner);
		free(tmp->group);
		free(tmp);
	}	
}

void	recurse_traverse(t_data data, char *path)
{
	t_filentry *files = getfiles(&data, path);
	t_filentry *base = files;
	printer(data, files, path);

	while (data.isrecusive && files)
	{
		if (files->filetype == 'd' && !((files->name[0] == '.' && data.listall == 0) || strcmp("..", files->name) == 0 || strcmp(".", files->name) == 0))
		{
			data.blocksize = 0;
			write(1, "\n", 1);
			char *p;
			if (path[ft_strlen(path) - 1] != '/')
				p = ft_strjoinmid(path, files->name, '/');
			else
				p = ft_strjoin(path, files->name);
			recurse_traverse(data, p);
			free(p);
		}
		files = files->next;
	}
	cleanup_file(base);
}

int main(int argc, char **argv)
{
	t_data data;
	t_direntry *entries = 0;
	t_direntry *baseptr;

	(void)argc;

	ft_memset(&data, 0, sizeof(t_data));
	if (parse(&data, &argv[1], &entries))
	{
		write(2, "Error: parse fail\n", 19);
		return (-1);
	}
	if (entries == 0)
	{
		entries = malloc(sizeof(t_direntry));
		entries->path = ".";
		entries->next = 0;
	}
	baseptr = entries;
	while (entries)
	{
		recurse_traverse(data, entries->path);
		entries = entries->next;
	}
	cleanup_dir(baseptr);
}