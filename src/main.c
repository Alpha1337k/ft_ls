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
		free(tmp->searchname);
		free(tmp->name);
		free(tmp);
	}	
}

void	recurse_traverse(t_data data, char *path)
{
	t_filentry *files = getfiles(&data, path);
	printer(data, files, path);

	while (data.isrecusive && files)
	{
		if (files->filetype == 'd' && files->name[0] != '.')
		{
			printf("\n");
			char *p = ft_strjoinmid(path, files->name, '/');
			recurse_traverse(data, p);
			data.blocksize = 0;
		}
		files = files->next;
	}
	cleanup_file(files);
}

int main(int argc, char **argv)
{
	t_data data;
	t_direntry *entries = 0;
	t_direntry *baseptr;

	(void)argc;

	bzero(&data, sizeof(t_data));
	if (parse(&data, &argv[1], &entries))
	{
		printf("exit: parse error");
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