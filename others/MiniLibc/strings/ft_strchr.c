/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aessadik <aessadik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 00:38:06 by aessadik          #+#    #+#             */
/*   Updated: 2024/12/12 23:41:53 by aessadik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (NULL);
}

char	*ft_strchr_for_export(const char *s, int c)
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
	return ("");
}

char	*ft_strchr_for_space(char *tmp)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(tmp);
	while (tmp && i <= len)
	{
		if (tmp[i] == is_space_delta(tmp[i]))
			return ((char *)(tmp + i));
		else
			i++;
	}
	return (NULL);
}
