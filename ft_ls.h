#ifndef FT_LS
#define  FT_LS

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

#define togglebit(nb, x)	(nb |= 1UL << x)
#define getbit(nb, x) 		((nb >> x) & 1U)

typedef enum e_sort
{
	UNKNOWN = -1,
	ALPHANUM,
	REVERSED,
	TIME,
	REVERSED_TIME,
	LENGTH
}			e_sort;

typedef struct	s_direntry
{
	char *path;
	void	*next;
}				t_direntry;

typedef struct	s_filentry
{
	char	filetype;
	char	*perms;
	char	*name;
	char	*searchname;
	char	*modtime;
	char	*owner;
	char	*group;
	long	size;
	long	links;
	long	realtime;

	void	*next;
	void	*prev;
}				t_filentry;



typedef struct s_data
{
	e_sort		sorttype;
	long		blocksize;

	int			isrecusive;
	int			islist;
	int			listall;

}				t_data;

int	parse(t_data *data, char **argv, t_direntry **e);
t_filentry	*getfiles(t_data *data, char *path);

int	alphabetical_compare(t_filentry f1, t_filentry f2);
int	reverse_compare(t_filentry f1, t_filentry f2);
int	time_compare(t_filentry f1, t_filentry f2);
int	reverse_time_compare(t_filentry f1, t_filentry f2);


t_filentry	*sort_list(t_filentry *files, int (f(t_filentry , t_filentry)));


void	freelist(t_filentry *lst);
void	list_add_back(t_filentry **lst, t_filentry *n);

void	printer(t_data data, t_filentry *f, char *path);


/*
	idc broertje
*/

char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoinmid(char const *s1, char const *s2, char const mid);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s1);
void	ft_tolowercase(char *s);
int		longlen(long l);

#endif