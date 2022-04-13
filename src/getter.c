#include <ft_ls.h>

char		get_filetype(mode_t s)
{
	if (S_ISREG(s))
		return '-';
	if (S_ISDIR(s))
		return 'd';
	if (S_ISFIFO(s))
		return 'p';
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

char		*get_permissions(struct stat *s)
{
	char	*rval = ft_strdup("---------");
	char	*types = "xwr";
	int x = 0;

	while (x < 9)
	{
		if (getbit(s->st_mode, x) == 1)
		{
			rval[8 - x] = types[x % 3];
		}
		x++;
	}
	if (s->st_mode & S_ISUID)
		rval[2] = 's';
	if (s->st_mode & S_ISGID)
		rval[5] = 's';
	if (s->st_mode & __S_ISVTX)
		rval[8] = 't';
	return rval;
}

char		*get_mdate(struct stat *s)
{
	time_t cur_time = time(0);
	char *rv = malloc(sizeof(char) * 13);

	char *toedit = ctime(&s->st_mtime);

	ft_memcpy(rv, &toedit[4], 7);
	if (s->st_mtim.tv_sec <= (cur_time - 15778476))
		ft_memcpy(&rv[7], &toedit[19], 5);
	else
		ft_memcpy(&rv[7], &toedit[11], 5);

	rv[12] = 0;
	return rv;
}

void		get_stats(t_data *data, t_filentry *n, char *path)
{
	struct stat s;

	char *tofind = ft_strjoinmid(path, n->name, '/');

	lstat(tofind, &s);

	struct passwd *pw = getpwuid(s.st_uid);
	struct group  *gr = getgrgid(s.st_gid);
	n->size = s.st_size;
	n->filetype = get_filetype(s.st_mode);
	n->modtime = get_mdate(&s);
	n->realtime = s.st_mtim;
	n->owner	= ft_strdup(pw->pw_name);
	n->group	= ft_strdup(gr->gr_name);
	n->perms = get_permissions(&s);
	n->links	= s.st_nlink;

	readlink(tofind, n->linkname, 256);

	data->blocksize += s.st_blocks;
	free(tofind);
}

static const void *sorttypes[] = {alphabetical_compare, reverse_compare, time_compare, reverse_time_compare};

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

			memset(n, 0, sizeof(t_filentry));
			n->next = 0;
			n->prev = 0;
			n->name = ft_strdup(drnt->d_name);
			get_stats(data, n, path);
			list_add_back(&rval, n);
		}
	} while (drnt);

	closedir(d);
	rval = sort_list(rval, sorttypes[data->sorttype]);
	return (rval);	
}
