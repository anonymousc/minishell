#include "minishell.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*str;

	if (size && nmemb > SIZE_MAX / size)
		return (0);
	str = (char *) malloc (nmemb * size);
	if (str == NULL)
		return (NULL);
	ft_bzero(str, nmemb * size);
	return (str);
}