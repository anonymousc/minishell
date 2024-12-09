#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	size_t			len;
	unsigned char	chr;

	chr = c;
	i = 0;
	len = ft_strlen(s);
	while (s && i <= len)
	{
		if (s[i] == chr)
			return ((char *)(s + i));
		else
			i++;
	}
	return (0);
}