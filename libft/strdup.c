#include <stdlib.h>
#include <string.h>

char	*ft_strdup(const char *s1)
{
	char	*s_copy;
	int		i;

	if (s1 == 0)
		return (0);
	s_copy = (char *)malloc((strlen(s1) + 1) * sizeof(char));
	if (s_copy == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s_copy[i] = s1[i];
		i++;
	}
	s_copy[i] = '\0';
	return (s_copy);
}