#include <ft_ls.h>

void	list_add_back(t_filentry **lst, t_filentry *n)
{
	if (*lst == 0)
	{
		*lst = n;
	}
	else
	{
		t_filentry *tmp = *lst;
		while (tmp && tmp->next)
		{
			tmp = tmp->next;
		}
		tmp->next = n;
		n->prev = tmp;
	}
}

void	freelist(t_filentry *lst)
{
	t_filentry *tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->name);
		free(tmp->perms);
		free(tmp->modtime);
		free(tmp);
	}
	
}