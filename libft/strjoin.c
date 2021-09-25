#include <stdlib.h>
#include <string.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = strlen(s1);
	len2 = strlen(s2);
	str = (char *)malloc((len1 + len2) * sizeof(char) + 1);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len1 + len2)
	{
		if (i < len1)
			str[i] = s1[i];
		else
			str[i] = s2[i - len1];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_strjoinmid(char const *s1, char const *s2, char const mid)
{
	char	*str;
	size_t	i;
	size_t	len1;
	size_t	len2;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len1 = strlen(s1);
	len2 = strlen(s2);
	str = (char *)malloc((len1 + len2) * sizeof(char) + 2);
	if (str == NULL)
		return (NULL);
	i = 0;
	while (i < len1 + len2 + 1)
	{
		if (i < len1)
			str[i] = s1[i];
		else if (i == len1)
			str[i] = mid;
		else
			str[i] = s2[i - len1 - 1];
		i++;
	}
	str[i] = '\0';
	return (str);
}