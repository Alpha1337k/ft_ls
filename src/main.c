#include <ft_ls.h>

void	recurse_traverse(t_data data, char *path)
{
	t_filentry *files = getfiles(&data, path);
	printer(data, files, path);

	while (data.isrecusive && files)
	{
		if (files->filetype == 'd')
		{
			printf("\n");
			char *p = ft_strjoinmid(path, files->name, '/');
			recurse_traverse(data, p);
			data.blocksize = 0;
		}
		files = files->next;
	}
	free(files);
	
}

int main(int argc, char **argv)
{
	t_data data;
	t_direntry *entries = 0;

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
	}
	//printf("data: [%s] %d %d %d %d\n",data.dir->path, data.islist, data.isrecusive, data.listall, data.sorttype);
	while (entries)
	{
		recurse_traverse(data, entries->path);
		entries = entries->next;
	}
	
	//t_filentry *files = getfiles(&data);

	//printer(data, files);
	//freelist(files);
}