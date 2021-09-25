#include <ft_ls.h>

char		get_filetype(mode_t s)
{
	if (S_ISREG(s))
		return '-';
	if (S_ISDIR(s))
		return 'd';
	if (S_ISFIFO(s))
		return 'f';
	if (S_ISBLK(s))
		return 'b';
	if (S_ISCHR(s))
		return 'c';
	if (S_ISSOCK(s))
		return 's';
	if (S_ISLNK(s))
		return 'l';
	return '?';
}

char		*get_permissions(mode_t s)
{
	char	*rval = strdup("---------");
	char	*types = "xwr";
	int x = 0;

	while (x < 9)
	{
		if (getbit(s, x) == 1)
		{
			rval[8 - x] = types[x % 3];
		}
		x++;
	}
	return rval;
}

void		get_stats(t_data *data, t_filentry *n, char *path)
{
	struct stat s;

	char *tofind = ft_strjoinmid(path, n->name, '/');

	stat(tofind, &s);

	free(tofind);
	struct passwd *pw = getpwuid(s.st_uid);
	struct group  *gr = getgrgid(s.st_gid);
	n->size = s.st_size;
	n->filetype = get_filetype(s.st_mode);
	n->modtime = ft_substr(ctime(&s.st_mtime), 4, 12);
	n->modtime[0] = n->modtime[0] + 32;
	n->owner	= pw->pw_name;
	n->group	= gr->gr_name;
	n->perms = get_permissions(s.st_mode);
	n->links	= s.st_nlink;

	data->blocksize += s.st_blocks / 2;
}

static const void *sorttypes[] = {alphabetical_compare, reverse_compare, time_compare};

t_filentry	*getfiles(t_data *data, char *path)
{
	t_filentry *rval = 0;
	DIR *d = opendir(path);
	if (d == 0)
		return (0);
	struct dirent *drnt;

	do
	{
		drnt = readdir(d);

		if (drnt && (data->listall == 1 || (data->listall == 0 && drnt->d_name[0] != '.')))
		{
			t_filentry *n = malloc(sizeof(t_filentry));

			bzero(n, sizeof(t_filentry));
			n->next = 0;
			n->prev = 0;
			n->name = strdup(drnt->d_name);
			n->searchname = strdup(drnt->d_name);
			ft_tolowercase(n->searchname);
			get_stats(data, n, path);
			list_add_back(&rval, n);
		}
	} while (drnt);

	closedir(d);
	rval = sort_list(rval, sorttypes[data->sorttype]);
	return (rval);	
}
