#include "minishell.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned char	a;
	size_t			i;

	str = s;
	a = c;
	i = 0;
	while (i < n)
		str[i++] = a;
	return (str);
}