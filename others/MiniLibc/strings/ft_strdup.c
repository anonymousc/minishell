#include "minishell.h"

char	*ft_strdup(char *src)
{
	size_t	i;
	char	*duplicate;

	if (!src)
		return (NULL);
	duplicate = (char *) malloc ((ft_strlen(src) + 1) * sizeof(char));
	if (!duplicate)
		return (NULL);
	i = 0;
	while (src[i])
	{
		duplicate[i] = src[i];
		i++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}
char *ft_strndup(char *str, size_t n)
{
	char *res;
	size_t len = 0;

	while (len < n && str[len] != '\0')
		len++;
	res = malloc(len + 1);
	if (!res)
		return NULL;
	size_t i = 0;
	while (i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return res;
}