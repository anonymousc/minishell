#include "minishell.h"

char	*ft_strjoin(char *s, char *s1)
{
	char	*p;
	char	*str;
	int		i;

	i = 0;
	if (!s && !s1)
		return (NULL);
	p = (char *)malloc(ft_strlen(s) + ft_strlen(s1) + 1);
	if (!p)
		return (NULL);
	p[ft_strlen(s) + ft_strlen(s1)] = '\0';
	str = p;
	if (s)
	{
		while (s[i])
			*(p++) = s[i++];
	}
	i = 0;
	if (s1)
		while (s1[i])
			*(p++) = s1[i++];
	return (str);
}

char	*ft_strjoin2(char *s, char *s1)
{
	char	*p;
	char	*str;
	int		i;

	i = 0;
	if (!s && s1)
		return (ft_strdup(s1));
	else if (!s1 && s)
		return (ft_strdup(s));
	if (!s && !s1)
		return (NULL);
	p = (char *)malloc(ft_strlen(s) + ft_strlen(s1) + 1);
	if (!p)
		return (NULL);
	p[ft_strlen(s) + ft_strlen(s1)] = '\0';
	str = p;
	if (s)
		while (s[i])
			*(p++) = s[i++];
	i = 0;
	if (s1)
		while (s1[i])
			*(p++) = s1[i++];
	return (str);
}
